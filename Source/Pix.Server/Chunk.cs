using System.ComponentModel;
using System.Threading;

namespace Pix.Server
{
    public class Chunk : INotifyPropertyChanged
    {
        protected static int NextChunkId = 0;

        public event PropertyChangedEventHandler PropertyChanged;

        public Chunk(Scene scene, int startY, int width, int height)
        {
            ChunkId = Interlocked.Increment(ref NextChunkId);

            Scene = scene;
            StartY = startY;
            Width = width;
            Height = height;
        }

        protected virtual void OnPropertyChanged(string propertyName)
        {
            PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(propertyName));
        }

        public bool IsBeingWorkedOn { get; set; }
        public bool IsCompleted { get; set; }

        public int ChunkId { get; }
        public Scene Scene { get; }
        public int StartY { get; }
        public int Width { get; }
        public int Height { get; }
    }
}