using System.ComponentModel;
using System.Threading;

namespace Pix.Server
{
    public class Chunk : INotifyPropertyChanged
    {
        protected static int NextChunkId = 0;

        public event PropertyChangedEventHandler PropertyChanged;

        public Chunk(Scene scene, int width, int height, int startY, int maxSubPixelX, int maxSubPixelY, int subPixelStartX, int subPixelStartY, int subPixelEndX, int subPixelEndY)
        {
            ChunkId = Interlocked.Increment(ref NextChunkId);

            Scene = scene;
            StartY = startY;
            Width = width;
            Height = height;

            MaxSubPixelX = maxSubPixelX;
            MaxSubPixelY = maxSubPixelY;

            SubPixelStartX = subPixelStartX;
            SubPixelStartY = subPixelStartY;
            SubPixelEndX = subPixelEndX;
            SubPixelEndY = subPixelEndY;
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

        public int MaxSubPixelX { get; }
        public int MaxSubPixelY { get; }

        public int SubPixelStartX { get; }
        public int SubPixelStartY { get; }
        public int SubPixelEndX { get; }
        public int SubPixelEndY { get; }
    }
}