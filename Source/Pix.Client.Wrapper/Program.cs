using Pix.Managed.Common;
using Pix.Managed.Common.NetworkMessages;
using System;
using System.Collections.Concurrent;
using System.Net.Sockets;
using System.Runtime.InteropServices;
using System.Threading;

namespace Pix.Client.Wrapper
{
    public static class Program
    {
        private static TcpClient _tcpClient;

        private static readonly BlockingCollection<ChunkToProcessMessage> _chunksToProcess = new BlockingCollection<ChunkToProcessMessage>(Environment.ProcessorCount);
        private static readonly BlockingCollection<ChunkCompletedMessage> _chunksCompleted = new BlockingCollection<ChunkCompletedMessage>();

        public static void NetworkReadingThread()
        {
            var networkStream = _tcpClient.GetStream();
            var messageReader = new MessageReader(_tcpClient);

            while (true)
            {
                var requestChunkMessage = new RequestChunkMessage();
                var requestChunkMessageBytes = requestChunkMessage.ToBytes();

                lock (_tcpClient)
                {
                    networkStream.Write(requestChunkMessageBytes, 0, requestChunkMessageBytes.Length);
                }

                var message = messageReader.GetMessage().Result;

                switch (message)
                {
                    case ChunkToProcessMessage chunkToProcess:
                        _chunksToProcess.Add(chunkToProcess);
                        break;
                }
            }
        }

        public static void WorkerThread()
        {
            while (true)
            {
                var chunkToProcess = _chunksToProcess.Take();

                var pixelData = new float[chunkToProcess.Width * chunkToProcess.Height * 3];
                var pixelDataBytes = new byte[pixelData.Length * 4];

                Trace(
                    chunkToProcess.Width,
                    chunkToProcess.Height,
                    chunkToProcess.ChunkHeight,
                    chunkToProcess.StartY,
                    chunkToProcess.MaxSubPixelX,
                    chunkToProcess.MaxSubPixelY,
                    chunkToProcess.SubPixelStartX,
                    chunkToProcess.SubPixelStartY,
                    chunkToProcess.SubPixelEndX,
                    chunkToProcess.SubPixelEndY,
                    chunkToProcess.SceneXml,
                    pixelData);

                Buffer.BlockCopy(pixelData, 0, pixelDataBytes, 0, pixelDataBytes.Length);

                _chunksCompleted.Add(new ChunkCompletedMessage(chunkToProcess.SceneId, chunkToProcess.ChunkId, pixelDataBytes));
            }
        }

        public static void Main(string[] args)
        {
            _tcpClient = new TcpClient("127.0.0.1", 54000);

            var networkReadingThread = new Thread(NetworkReadingThread)
            {
                Name = "NetworkReadingThread",
                IsBackground = false,
                Priority = ThreadPriority.AboveNormal
            };

            networkReadingThread.Start();

            var workerThreads = new Thread[Environment.ProcessorCount];

            for (var i = 0; i < Environment.ProcessorCount; ++i)
            {
                var workerThread = new Thread(WorkerThread)
                {
                    Name = $"WorkerThread{i}",
                    IsBackground = false,
                    Priority = ThreadPriority.BelowNormal
                };

                workerThreads[i] = workerThread;

                workerThread.Start();
            }

            var networkStream = _tcpClient.GetStream();

            while (true)
            {
                var chunkCompletedMessage = _chunksCompleted.Take();
                var chunkCompletedMessageBytes = chunkCompletedMessage.ToBytes();

                lock (_tcpClient)
                {
                    networkStream.Write(chunkCompletedMessageBytes, 0, chunkCompletedMessageBytes.Length);
                }
            }

            //var sceneXml = @"
            //    <?xml version=""1.0"" encoding=""utf-8""?>
            //    <Scene xmlns:xsi=""http://www.w3.org/2001/XMLSchema-instance"" xsi:noNamespaceSchemaLocation=""PixScene.xsd"">

            //      <Options>
            //        <MaxDepth>20</MaxDepth>
            //        <DefaultColor>0</DefaultColor>
            //        <AntialiasingLevel>3</AntialiasingLevel>
            //        <RussianRouletteDepthStart>5</RussianRouletteDepthStart>
            //        <RussianRouletteStopProbability>0.1</RussianRouletteStopProbability>
            //      </Options>

            //      <Camera>
            //        <PerspectiveCamera Position=""0,0,0"" LookAt=""0,-1.5,-5"" Up=""0,1,0"" ScreenWidth=""640"" ScreenHeight=""480"" FieldOfView=""1.57079633"" />
            //      </Camera>

            //      <Materials>
            //        <MonteCarloDiffuseMaterial Name=""WhiteDiffuse"" Color=""1"" EmissiveColor=""0"" />
            //        <MonteCarloDiffuseMaterial Name=""RedDiffuse"" Color=""1,0,0"" EmissiveColor=""0"" />
            //        <MonteCarloDiffuseMaterial Name=""GreenDiffuse"" Color=""0,1,0"" EmissiveColor=""0"" />
            //        <MonteCarloDiffuseMaterial Name=""BlueDiffuse"" Color=""0,0,1"" EmissiveColor=""0"" />
            //        <SpecularMaterial Name=""Mirror"" />
            //      </Materials>

            //      <Lights>
            //        <!--<PointLight Color=""1.0"" Position=""0,1.9,-3"" />-->
            //      </Lights>

            //      <RootGeometry>
            //        <GeometryGroup>
            //          <Geometries>
            //            <Sphere Center=""0,1.9,-3"" Radius=""0.5"">
            //              <Material>
            //                <MonteCarloDiffuseMaterial Color=""0"" EmissiveColor=""75"" />
            //              </Material>
            //            </Sphere>

            //            <Sphere Center=""-0.75,-1.45,-4.4"" Radius=""1.05"">
            //              <Material>
            //                <SpecularMaterial />
            //                <!--<MonteCarloDiffuseMaterial Color=""0.5,1,0.5"" EmissiveColor=""0"" />-->
            //              </Material>
            //            </Sphere>

            //            <Sphere Center=""2.0,-2.05,-3.7"" Radius=""0.5"">
            //              <Material>
            //                <MonteCarloDiffuseMaterial Color=""1,1,0.1"" EmissiveColor=""0"" />
            //              </Material>
            //            </Sphere>

            //            <Sphere Center=""-1.75,-1.95,-3.1"" Radius=""0.6"">
            //              <Material>
            //                <MonteCarloDiffuseMaterial Color=""0.33,0.33,1"" EmissiveColor=""0"" />
            //              </Material>
            //            </Sphere>

            //            <PlaneD MaterialName=""WhiteDiffuse"" Normal=""0,1,0"" D=""2.5"" />
            //            <PlaneD MaterialName=""WhiteDiffuse"" Normal=""0,-1,0"" D=""3"" />

            //            <PlaneD MaterialName=""RedDiffuse"" Normal=""1,0,0"" D=""2.75"" />
            //            <PlaneD MaterialName=""GreenDiffuse"" Normal=""-1,0,0"" D=""2.75"" />

            //            <PlaneD MaterialName=""WhiteDiffuse"" Normal=""0,0,-1"" D=""0.5"" />
            //            <PlaneD MaterialName=""WhiteDiffuse"" Normal=""0,0,1"" D=""5.5"" />
            //          </Geometries>
            //        </GeometryGroup>
            //      </RootGeometry>

            //    </Scene>";

            //const int width = 640;
            //const int height = 480;

            //var pixelData = new float[width * height * 3];
            //Trace(width, height, height, 0, 0, 0, 0, 0, 0, 0, sceneXml, pixelData);
        }

        [DllImport("Pix.Client.Windows.dll")]
        public static extern void Trace(
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
            [MarshalAs(UnmanagedType.LPStr)] string sceneXml,
            float[] pixelData);
    }
}