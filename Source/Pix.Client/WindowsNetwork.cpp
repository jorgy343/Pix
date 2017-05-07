#include "WindowsNetwork.h"

using namespace Pix::Client;

WindowsNetwork::WindowsNetwork(const char* ip, const char* port)
    : _state(NetworkState::Initialize)
{
    int result = WSAStartup(MAKEWORD(2, 2), &_wsaData);
    if (result != 0)
    {
        //printf("WSAStartup failed: %d\n", result);
        return;
    }

    result = getaddrinfo(ip, port, nullptr, &_addressInfoResult);
    if (result != 0)
    {
        //printf("getaddrinfo failed: %d\n", result);
        WSACleanup();

        return;
    }

    _connectedSocket = socket(_addressInfoResult->ai_family, _addressInfoResult->ai_socktype, _addressInfoResult->ai_protocol);
    if (_connectedSocket == INVALID_SOCKET)
    {
        //printf("Error at socket(): %ld\n", WSAGetLastError());

        freeaddrinfo(_addressInfoResult);
        WSACleanup();

        return;
    }

    result = connect(_connectedSocket, _addressInfoResult->ai_addr, (int)_addressInfoResult->ai_addrlen);
    if (result == SOCKET_ERROR)
    {
        //printf("Error at connect(): %ld\n", WSAGetLastError());

        closesocket(_connectedSocket);
        _connectedSocket = INVALID_SOCKET;
    }

    u_long mode = 1;
    ioctlsocket(_connectedSocket, FIONBIO, &mode);

    freeaddrinfo(_addressInfoResult);
    if (_connectedSocket == INVALID_SOCKET)
    {
        //printf("Error at socket(): %ld\n", WSAGetLastError());

        //printf("Unable to connect to server!\n");
        WSACleanup();

        return;
    }
}

WindowsNetwork::~WindowsNetwork()
{
    closesocket(_connectedSocket);
    WSACleanup();
}

bool WindowsNetwork::IsMessageReady() const
{
    return _state == NetworkState::MessageReady;
}

void WindowsNetwork::Read()
{
    int read;
    switch (_state)
    {
    case NetworkState::Initialize:
    case NetworkState::MessageReady:
        _messageTypeRead = 0;
        _messageSizeRead = 0;
        _messageRead = 0;

        _state = NetworkState::ReadingMessageType;

        break;

    case NetworkState::ReadingMessageType:
        read = recv(_connectedSocket, ((char*)&_messageType) + _messageTypeRead, 4 - _messageTypeRead, 0);
        if (read <= 0)
            return;

        _messageTypeRead += read;
        if (_messageTypeRead == 4)
            _state = NetworkState::ReadingMessageSize;

        break;

    case NetworkState::ReadingMessageSize:
        read = recv(_connectedSocket, ((char*)&_messageSize) + _messageSizeRead, 4 - _messageSizeRead, 0);
        if (read <= 0)
            return;

        _messageSizeRead += read;
        if (_messageSizeRead == 4)
        {
            _state = NetworkState::ReadingMessage;
            _message = std::make_unique<const char[]>(_messageSize);
        }

        break;

    case NetworkState::ReadingMessage:
        read = recv(_connectedSocket, ((char*)_message.get()) + _messageRead, _messageSize - _messageRead, 0);
        if (read <= 0)
            return;

        _messageRead += read;
        if (_messageRead == _messageSize)
            _state = NetworkState::MessageReady;

        break;
    }
}

int WindowsNetwork::Send(const char* buffer, int bufferSizeInBytes) const
{
    return send(_connectedSocket, buffer, bufferSizeInBytes, 0);
}

void WindowsNetwork::SendChunkRequestedMessage() const
{
    int buffer[2];

    buffer[0] = 1; // Message Type
    buffer[1] = 0; // Message Size

    send(_connectedSocket, (const char*)buffer, 8, 0);
}

std::unique_ptr<const char[]> WindowsNetwork::GetMessage()
{
    while (!IsMessageReady())
        Read();

    _state = NetworkState::ReadingMessageType;
    return std::move(_message);
}