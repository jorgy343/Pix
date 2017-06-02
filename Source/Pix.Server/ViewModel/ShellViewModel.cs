using Pix.Server.Messages;
using System.Collections.Concurrent;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.IO;
using System.Linq;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Threading.Tasks;

namespace Pix.Server.ViewModel
{
    public class ShellViewModel : ViewModelBase
    {
        public ShellViewModel()
        {
            CreateSceneCommand = new RelayCommand(CreateSceneViewModel);
            StartServer();
        }

        public void CreateSceneViewModel(object parameter)
        {
            var sceneViewModel = new SceneViewModel(@"C:\Repos\Pix\Source\TestScene.xml", 480, 320, 320 / 2);
            SceneViewModels.Add(sceneViewModel);

            foreach (var chunk in sceneViewModel.Scene.Chunks)
                ChunksToProcess.Add(chunk);
        }

        public async void StartServer()
        {
            var listener = new TcpListener(new IPEndPoint(IPAddress.Parse("127.0.0.1"), 54000));
            listener.Start();

            while (true)
            {
                try
                {
                    var client = await listener.AcceptTcpClientAsync().ConfigureAwait(false);
                    Clients.Add(client);

                    await Task.Run(() => HandleConnection(client));
                }
                catch
                {

                }
            }
        }

        public void StopServer()
        {
            try
            {
                foreach (var client in Clients)
                    client.Close();

                Listener.Stop();
            }
            catch
            {

            }
        }

        public async void HandleConnection(TcpClient client)
        {
            var messageReader = new MessageReader(client);
            var chunksBeingProcessed = new List<Chunk>();

            try
            {
                while (true)
                {
                    var message = await messageReader.GetMessage();
                    if (message == null)
                        break; // Client disconnected; remove client from the list of active clients.

                    if (message is ChunkRequestedMessage)
                    {
                        var chunkToProcess = ChunksToProcess.Take();
                        chunksBeingProcessed.Add(chunkToProcess);

                        chunkToProcess.IsBeingWorkedOn = true;

                        var networkStream = client.GetStream();
                        using (var writer = new BinaryWriter(networkStream, Encoding.Default, true))
                        {
                            var sceneAsBytes = Encoding.ASCII.GetBytes(chunkToProcess.Scene.SceneXml);

                            writer.Write((int)SendMessageType.ChunkSentForProcessing);
                            writer.Write(sizeof(int) * 6 + sceneAsBytes.Length + 1);

                            writer.Write(chunkToProcess.Scene.SceneId);
                            writer.Write(chunkToProcess.ChunkId);

                            writer.Write(chunkToProcess.Width);
                            writer.Write(chunkToProcess.Scene.Height);
                            writer.Write(chunkToProcess.Height);
                            writer.Write(chunkToProcess.StartY);

                            writer.Write(sceneAsBytes);
                            writer.Write((byte)0);

                            writer.Flush();
                        }
                    }
                    else if (message is ChunkCompletedMessage)
                    {
                        var chunkCompletedMessage = (ChunkCompletedMessage)message;

                        var sceneViewModel = SceneViewModels.SingleOrDefault(x => x.Scene.SceneId == chunkCompletedMessage.SceneId);
                        var chunk = sceneViewModel?.Scene.Chunks.SingleOrDefault(x => x.ChunkId == chunkCompletedMessage.ChunkId);

                        if (chunk != null)
                        {
                            chunksBeingProcessed.Remove(chunk);

                            chunk.IsBeingWorkedOn = false;
                            chunk.IsCompleted = true;

                            sceneViewModel.UpdateChunk(chunk, chunkCompletedMessage.ColorData);
                        }
                    }
                }
            }
            catch
            {

            }
            finally
            {
                Clients.Remove(client);
                foreach (var chunk in chunksBeingProcessed) // Add any unfinished chunks back into the work queue.
                    ChunksToProcess.Add(chunk);
            }
        }

        public TcpListener Listener { get; set; }
        public ObservableCollection<TcpClient> Clients { get; } = new ObservableCollection<TcpClient>();
        public ObservableCollection<SceneViewModel> SceneViewModels { get; } = new ObservableCollection<SceneViewModel>();
        public BlockingCollection<Chunk> ChunksToProcess { get; } = new BlockingCollection<Chunk>();

        public RelayCommand CreateSceneCommand { get; }
    }
}