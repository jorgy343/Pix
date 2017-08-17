using System;
using System.Linq;

namespace Pix.Server.Messages
{
    public class ChunkCompletedMessage : ReceiveMessage
    {
        public ChunkCompletedMessage(ReceiveMessageType messageType, int messageSize, byte[] messageData)
            : base(messageType, messageSize, messageData)
        {
            SceneId = BitConverter.ToInt32(messageData, 0);
            ChunkId = BitConverter.ToInt32(messageData, 4);

            ColorData = messageData.Skip(8).ToArray();
        }

        public long SceneId { get; }
        public long ChunkId { get; }
        public byte[] ColorData { get; }
    }
}