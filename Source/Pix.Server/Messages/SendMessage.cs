namespace Pix.Server.Messages
{
    public abstract class SendMessage
    {
        public SendMessage(SendMessageType messageType)
        {
            MessageType = messageType;
        }

        public abstract byte[] ToBytes();

        public SendMessageType MessageType { get; }
    }
}