using System;
using System.Net.Sockets;
using System.Threading.Tasks;

namespace Pix.Server.Messages
{
    public class MessageReader
    {
        public MessageReader(TcpClient client)
        {
            Client = client;
        }

        public virtual async Task<ReceiveMessage> GetMessage()
        {
            var networkStream = Client.GetStream();

            // Message Type
            ReceiveMessageType messageType = ReceiveMessageType.None;
            var messageTypeBuffer = new byte[4];
            var messageTypeBufferBytesRead = 0;

            while (messageTypeBufferBytesRead < 4)
            {
                var bytesRead = await networkStream.ReadAsync(messageTypeBuffer, messageTypeBufferBytesRead, 4 - messageTypeBufferBytesRead);
                if (bytesRead == 0)
                    return null;

                messageTypeBufferBytesRead += bytesRead;
            }

            messageType = (ReceiveMessageType)BitConverter.ToInt32(messageTypeBuffer, 0);

            // Message Size
            int messageSize = 0;
            var messageSizeBuffer = new byte[4];
            var messageSizeBufferBytesRead = 0;

            while (messageSizeBufferBytesRead < 4)
            {
                var bytesRead = await networkStream.ReadAsync(messageSizeBuffer, messageSizeBufferBytesRead, 4 - messageSizeBufferBytesRead);
                if (bytesRead == 0)
                    return null;

                messageSizeBufferBytesRead += bytesRead;
            }

            messageSize = BitConverter.ToInt32(messageSizeBuffer, 0);

            // Message Data
            var messageData = new byte[messageSize];
            var messageDataBytesRead = 0;

            while (messageDataBytesRead < messageSize && messageSize > 0)
            {
                var bytesRead = await networkStream.ReadAsync(messageData, messageDataBytesRead, messageSize - messageDataBytesRead);
                if (bytesRead == 0)
                    return null;

                messageDataBytesRead += bytesRead;
            }

            return BuildMessage(messageType, messageSize, messageData);
        }

        protected virtual ReceiveMessage BuildMessage(ReceiveMessageType messageType, int messageSize, byte[] messageData)
        {
            switch (messageType)
            {
                case ReceiveMessageType.ChunkRequested:
                    return new ChunkRequestedMessage(messageType, messageSize, messageData);

                case ReceiveMessageType.ChunkCompleted:
                    return new ChunkCompletedMessage(messageType, messageSize, messageData);

                default:
                    return null;
            }
        }

        protected TcpClient Client { get; }
    }
}