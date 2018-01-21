using Pix.Managed.Common;
using Pix.Managed.Common.NetworkMessages;
using System;
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
            var sceneViewModel = new SceneViewModel(@"C:\Repos\Pix\Source\TestScene.xml", 640, 480, 480 / 2);
            SceneViewModels.Add(sceneViewModel);

            var random = new Random();

            foreach (var chunk in sceneViewModel.Scene.Chunks.OrderBy(_ => random))
            {
                ChunksToProcess.Add(chunk);
            }
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
                {
                    client.Close();
                }

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
                    {
                        break; // Client disconnected; remove client from the list of active clients.
                    }

                    switch (message)
                    {
                        case RequestChunkMessage _:
                            var chunkToProcess = ChunksToProcess.Take();
                            chunksBeingProcessed.Add(chunkToProcess);

                            chunkToProcess.IsBeingWorkedOn = true;

                            var networkStream = client.GetStream();

                            var chunkToProcessMessage = new ChunkToProcessMessage(
                                chunkToProcess.Scene.SceneId,
                                chunkToProcess.ChunkId,
                                chunkToProcess.Width,
                                chunkToProcess.Scene.Height,
                                chunkToProcess.Height,
                                chunkToProcess.StartY,
                                chunkToProcess.MaxSubPixelX,
                                chunkToProcess.MaxSubPixelY,
                                chunkToProcess.SubPixelStartX,
                                chunkToProcess.SubPixelStartY,
                                chunkToProcess.SubPixelEndX,
                                chunkToProcess.SubPixelEndY,
                                chunkToProcess.Scene.SceneXml);

                            var messageBytes = chunkToProcessMessage.ToBytes();
                            await networkStream.WriteAsync(messageBytes, 0, messageBytes.Length);

                            break;

                        case ChunkCompletedMessage chunkCompletedMessage:
                            var sceneViewModel = SceneViewModels.SingleOrDefault(x => x.Scene.SceneId == chunkCompletedMessage.SceneId);
                            var chunk = sceneViewModel?.Scene.Chunks.SingleOrDefault(x => x.ChunkId == chunkCompletedMessage.ChunkId);

                            if (chunk != null)
                            {
                                chunksBeingProcessed.Remove(chunk);

                                chunk.IsBeingWorkedOn = false;
                                chunk.IsCompleted = true;

                                sceneViewModel.Scene.UpdateChunk(chunk, chunkCompletedMessage.ColorData);
                                sceneViewModel.UpdateChunk(chunk);
                            }

                            break;
                    }
                }
            }
            catch
            {
            }
            finally
            {
                if (Clients.Contains(client))
                {
                    Clients.Remove(client);
                }

                foreach (var chunk in chunksBeingProcessed) // Add any unfinished chunks back into the work queue.
                {
                    ChunksToProcess.Add(chunk);
                }
            }
        }

        public TcpListener Listener { get; set; }
        public ObservableCollection<TcpClient> Clients { get; } = new ObservableCollection<TcpClient>();
        public ObservableCollection<SceneViewModel> SceneViewModels { get; } = new ObservableCollection<SceneViewModel>();
        public BlockingCollection<Chunk> ChunksToProcess { get; } = new BlockingCollection<Chunk>();

        public RelayCommand CreateSceneCommand { get; }
    }
}