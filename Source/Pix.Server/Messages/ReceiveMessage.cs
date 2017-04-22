namespace Pix.Server.Messages
{
    public abstract class ReceiveMessage
    {
        public ReceiveMessage(ReceiveMessageType messageType, int messageSize, byte[] messageData)
        {
            MessageType = messageType;
            MessageSize = messageSize;
            MessageData = messageData;
        }

        public ReceiveMessageType MessageType { get; }
        public int MessageSize { get; }

        public byte[] MessageData { get; }
    }
}