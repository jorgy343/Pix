using System;
using System.IO;
using System.Text;

namespace Pix.Managed.Common.NetworkMessages
{
    public class ChunkToProcessMessage : Message
    {
        public const int Id = 3;

        public ChunkToProcessMessage(
            int sceneId,
            int chunkId,
            int width,
            int height,
            int chunkHeight,
            int startY,
            int maxSubPixelX,
            int maxSubPixelY,
            int subPixelStartX,
            int subPixelStartY,
            int subPixelEndX,
            int subPixelEndY,
            string sceneXml)
        {
            SceneId = sceneId;
            ChunkId = chunkId;
            Width = width;
            Height = height;
            ChunkHeight = chunkHeight;
            StartY = startY;
            MaxSubPixelX = maxSubPixelX;
            MaxSubPixelY = maxSubPixelY;
            SubPixelStartX = subPixelStartX;
            SubPixelStartY = subPixelStartY;
            SubPixelEndX = subPixelEndX;
            SubPixelEndY = subPixelEndY;
            SceneXml = sceneXml;
        }

        public int SceneId { get; }
        public int ChunkId { get; }
        public int Width { get; }
        public int Height { get; }
        public int ChunkHeight { get; }
        public int StartY { get; }
        public int MaxSubPixelX { get; }
        public int MaxSubPixelY { get; }
        public int SubPixelStartX { get; }
        public int SubPixelStartY { get; }
        public int SubPixelEndX { get; }
        public int SubPixelEndY { get; }
        public string SceneXml { get; }

        public static ChunkToProcessMessage Parse(byte[] data)
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
                var width = reader.ReadInt32();
                var height = reader.ReadInt32();
                var chunkHeight = reader.ReadInt32();
                var startY = reader.ReadInt32();
                var maxSubPixelX = reader.ReadInt32();
                var maxSubPixelY = reader.ReadInt32();
                var subPixelStartX = reader.ReadInt32();
                var subPixelStartY = reader.ReadInt32();
                var subPixelEndX = reader.ReadInt32();
                var subPixelEndY = reader.ReadInt32();
                var sceneXml = Encoding.ASCII.GetString(reader.ReadBytes(data.Length - 56));

                return new ChunkToProcessMessage(
                    sceneId,
                    chunkId,
                    width,
                    height,
                    chunkHeight,
                    startY,
                    maxSubPixelX,
                    maxSubPixelY,
                    subPixelStartX,
                    subPixelStartY,
                    subPixelEndX,
                    subPixelEndY,
                    sceneXml);
            }
        }

        public override byte[] ToBytes()
        {
            using (var memory = new MemoryStream())
            using (var writer = new BinaryWriter(memory))
            {
                writer.Write(Id);
                writer.Write(48 + SceneXml.Length + 1); // The scene is sent as ASCII so each character is a single byte.

                writer.Write(SceneId);
                writer.Write(ChunkId);
                writer.Write(Width);
                writer.Write(Height);
                writer.Write(ChunkHeight);
                writer.Write(StartY);
                writer.Write(MaxSubPixelX);
                writer.Write(MaxSubPixelY);
                writer.Write(SubPixelStartX);
                writer.Write(SubPixelStartY);
                writer.Write(SubPixelEndX);
                writer.Write(SubPixelEndY);
                writer.Write(Encoding.ASCII.GetBytes(SceneXml));
                writer.Write((byte)0);

                return memory.ToArray();
            }
        }
    }
}