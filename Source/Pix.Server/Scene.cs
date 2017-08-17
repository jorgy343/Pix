using System.Collections.ObjectModel;
using System.ComponentModel;
using System.IO;
using System.Threading;

namespace Pix.Server
{
    public class Scene : INotifyPropertyChanged
    {
        protected static int NextSceneId = 0;

        private readonly int _sampleCountPerPixelX;
        private readonly int _sampleCountPerPixelY;

        public event PropertyChangedEventHandler PropertyChanged;

        public Scene(string sceneXml, int width, int height, int chunkCount)
        {
            _sampleCountPerPixelX = 100;
            _sampleCountPerPixelY = 100;

            SampleCount = new int[width, height];
            ColorData = new Color3[width, height];

            SceneId = Interlocked.Increment(ref NextSceneId);

            SceneXml = sceneXml;
            Width = width;
            Height = height;

            ChunkHeight = height;
            for (var sampleY = 0; sampleY < _sampleCountPerPixelY; ++sampleY)
            {
                for (var sampleX = 0; sampleX < _sampleCountPerPixelX; ++sampleX)
                    Chunks.Add(new Chunk(this, width, ChunkHeight, 0, _sampleCountPerPixelX, _sampleCountPerPixelY, sampleX, sampleY, sampleX, sampleY));
            }
        }

        public void UpdateChunk(Chunk chunk, byte[] colorData)
        {
            using (var memoryStream = new MemoryStream(colorData))
            using (var binaryReader = new BinaryReader(memoryStream))
            {
                lock (SampleCount)
                {
                    lock (ColorData)
                    {
                        for (var y = chunk.StartY; y < chunk.StartY + chunk.Height; ++y)
                        {
                            for (var x = 0; x < chunk.Width; ++x)
                            {
                                SampleCount[x, y] += (chunk.SubPixelEndX - chunk.SubPixelStartX + 1) * (chunk.SubPixelEndY - chunk.SubPixelStartY + 1);

                                float red = binaryReader.ReadSingle();
                                float green = binaryReader.ReadSingle();
                                float blue = binaryReader.ReadSingle();

                                ColorData[x, y].Red += red;
                                ColorData[x, y].Green += green;
                                ColorData[x, y].Blue += blue;
                            }
                        }
                    }
                }

                PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(nameof(SampleCount)));
                PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(nameof(ColorData)));
            }
        }

        public int[,] SampleCount { get; }
        public Color3[,] ColorData { get; }

        public int SceneId { get; }
        public string SceneXml { get; }
        public int Width { get; }
        public int Height { get; }
        public int ChunkHeight { get; }

        public ObservableCollection<Chunk> Chunks { get; } = new ObservableCollection<Chunk>();
    }
}