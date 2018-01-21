using System;
using System.IO;

namespace Pix.Managed.Common.NetworkMessages
{
    public class ChunkCompletedMessage : Message
    {
        public const int Id = 1;

        public ChunkCompletedMessage(int sceneId, int chunkId, byte[] colorData)
        {
            SceneId = sceneId;
            ChunkId = chunkId;
            ColorData = colorData ?? throw new ArgumentNullException(nameof(colorData));
        }

        public int SceneId { get; }
        public int ChunkId { get; }
        public byte[] ColorData { get; }

        public static ChunkCompletedMessage Parse(byte[] data)
        {
            if (data == null)
            {
                throw new ArgumentNullException(nameof(data));
            }

            using (var memory = new MemoryStream(data))
            using (var reader = new BinaryReader(memory))
            {
                var sceneId = reader.ReadInt32();
                var chunkId = reader.ReadInt32();
                var colorData = reader.ReadBytes(data.Length - 8);

                return new ChunkCompletedMessage(sceneId, chunkId, colorData);
            }
        }

        public override byte[] ToBytes()
        {
            using (var memory = new MemoryStream())
            using (var writer = new BinaryWriter(memory))
            {
                writer.Write(Id);
                writer.Write(8 + ColorData.Length);
                writer.Write(SceneId);
                writer.Write(ChunkId);
                writer.Write(ColorData);

                return memory.ToArray();
            }
        }
    }
}