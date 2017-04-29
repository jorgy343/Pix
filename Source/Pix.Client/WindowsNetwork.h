#pragma once

#include <winsock2.h>
#include <ws2tcpip.h>
#include <memory>
#include <iostream>

#include <functional>

#include "NetworkState.h"
#include "INetwork.h"

#pragma warning(push)
#pragma warning(disable: 4005)
#define GetMessage GetMessage // The Windows headers define "GetMessage" as "GetMessageW". Undo that.
#pragma warning(pop)

namespace Pix::Client
{
    class WindowsNetwork final : public INetwork
    {
    private:
        WSADATA _wsaData;
        addrinfo* _addressInfoResult;
        SOCKET _connectedSocket;

        NetworkState _state;

        int _messageType;
        int _messageTypeRead;

        int _messageSize;
        int _messageSizeRead;

        std::unique_ptr<const char[]> _message;
        int _messageRead;

        void Read();
        bool IsMessageReady() const;

    public:
        WindowsNetwork(const char* ip, const char* port);
        ~WindowsNetwork();

        int Send(const char* buffer, int bufferSizeInBytes) const override;
        void SendChunkRequestedMessage() const override;

        std::unique_ptr<const char[]> GetMessage() override;
    };
}