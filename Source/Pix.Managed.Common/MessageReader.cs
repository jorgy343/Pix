using Pix.Managed.Common.NetworkMessages;
using System;
using System.Net.Sockets;
using System.Threading.Tasks;

namespace Pix.Managed.Common
{
    public class MessageReader
    {
        public MessageReader(TcpClient client)
        {
            if (client == null)
            {
                throw new ArgumentNullException(nameof(client));
            }

            Stream = client.GetStream();
        }

        protected NetworkStream Stream { get; }

        public virtual async Task<Message> GetMessage()
        {
            // Message Type
            var messageTypeBuffer = new byte[4];
            var messageTypeBufferBytesRead = 0;

            while (messageTypeBufferBytesRead < 4)
            {
                var bytesRead = await Stream.ReadAsync(messageTypeBuffer, messageTypeBufferBytesRead, 4 - messageTypeBufferBytesRead);

                if (bytesRead == 0)
                {
                    return null;
                }

                messageTypeBufferBytesRead += bytesRead;
            }

            var messageType = BitConverter.ToInt32(messageTypeBuffer, 0);

            // Message Size
            var messageSizeBuffer = new byte[4];
            var messageSizeBufferBytesRead = 0;

            while (messageSizeBufferBytesRead < 4)
            {
                var bytesRead = await Stream.ReadAsync(messageSizeBuffer, messageSizeBufferBytesRead, 4 - messageSizeBufferBytesRead);

                if (bytesRead == 0)
                {
                    return null;
                }

                messageSizeBufferBytesRead += bytesRead;
            }

            var messageSize = BitConverter.ToInt32(messageSizeBuffer, 0);

            // Message Data
            var messageData = new byte[messageSize];
            var messageDataBytesRead = 0;

            while ((messageDataBytesRead < messageSize) && (messageSize > 0))
            {
                var bytesRead = await Stream.ReadAsync(messageData, messageDataBytesRead, messageSize - messageDataBytesRead);

                if (bytesRead == 0)
                {
                    return null;
                }

                messageDataBytesRead += bytesRead;
            }

            return BuildMessage(messageType, messageData);
        }

        protected virtual Message BuildMessage(int messageType, byte[] messageData)
        {
            switch (messageType)
            {
                case RequestChunkMessage.Id:

                    return RequestChunkMessage.Parse(messageData);

                case ChunkToProcessMessage.Id:

                    return ChunkToProcessMessage.Parse(messageData);

                case ChunkCompletedMessage.Id:

                    return ChunkCompletedMessage.Parse(messageData);

                default:

                    return null;
            }
        }
    }
}