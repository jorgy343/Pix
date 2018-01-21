using System;
using System.IO;

namespace Pix.Managed.Common.NetworkMessages
{
    public class RequestChunkMessage : Message
    {
        public const int Id = 2;

        public static RequestChunkMessage Parse(byte[] data)
        {
            if (data == null)
            {
                throw new ArgumentNullException(nameof(data));
            }

            return new RequestChunkMessage();
        }

        public override byte[] ToBytes()
        {
            using (var memory = new MemoryStream())
            using (var writer = new BinaryWriter(memory))
            {
                writer.Write(Id);
                writer.Write(0);

                return memory.ToArray();
            }
        }
    }
}