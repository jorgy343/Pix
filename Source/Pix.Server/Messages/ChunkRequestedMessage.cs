namespace Pix.Server.Messages
{
    public class ChunkRequestedMessage : ReceiveMessage
    {
        public ChunkRequestedMessage(ReceiveMessageType messageType, int messageSize, byte[] messageData)
            : base(messageType, messageSize, messageData)
        {

        }
    }
}