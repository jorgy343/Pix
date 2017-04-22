using System.Collections.ObjectModel;
using System.Threading;

namespace Pix.Server
{
    public class Scene
    {
        protected static int NextSceneId = 0;

        public Scene(string sceneXml, int width, int height, int chunkCount)
        {
            SceneId = Interlocked.Increment(ref NextSceneId);

            SceneXml = sceneXml;
            Width = width;
            Height = height;

            ChunkHeight = height / chunkCount;
            for (int y = 0; y < height; y += ChunkHeight)
                Chunks.Add(new Chunk(this, y, width, ChunkHeight));
        }

        public int SceneId { get; }
        public string SceneXml { get; }
        public int Width { get; }
        public int Height { get; }
        public int ChunkHeight { get; }

        public ObservableCollection<Chunk> Chunks { get; } = new ObservableCollection<Chunk>();
    }
}