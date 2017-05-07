#include <SDKDDKVer.h>
#include <ppl.h>
#include <ppltasks.h>

#include <tchar.h>
#include <vector>

#include "WindowsConsole.h"
#include "WindowsNetwork.h"

#include "XmlSceneLoader.h"

using namespace Pix::Client;
using namespace Pix::Engine;

int _tmain(int argc, _TCHAR* argv[])
{
    unsigned int totalThreads = max(std::thread::hardware_concurrency(), 1);
    WindowsConsole* console = new WindowsConsole(totalThreads);

    std::vector<concurrency::task<void>> tasks;
    for (unsigned int i = 0; i < totalThreads; ++i)
    {
        auto task = concurrency::create_task([i, &console]
        {
            console->AddHistory(i, "Worker thread ", i, " started.");
            console->UpdateStatus(i, "Connecting to server...");

            INetwork* network = new WindowsNetwork("127.0.0.1", "54000");
            while (true)
            {
                console->UpdateStatusAndAddHistory(i, "Requesting chunk...");
                network->SendChunkRequestedMessage();

                auto message = network->GetMessage();
                auto messageData = message.get();

                int sceneId = *(int*)(messageData + 0);
                int chunkId = *(int*)(messageData + 4);

                int width = *(int*)(messageData + 8);
                int height = *(int*)(messageData + 12);
                int chunkHeight = *(int*)(messageData + 16);
                int startY = *(int*)(messageData + 20);

                const char* sceneXml = messageData + 24;
                console->UpdateStatusAndAddHistory(i, "Received chunk. Scene ID: ", sceneId, " Chunk ID: ", chunkId, ". Processing...");

                XmlSceneLoader sceneLoader(sceneXml);

                auto scene = sceneLoader.CreateScene();
                auto camera = sceneLoader.CreateCamera();

                // Render the scene.
                int antiAliasingLevel = 1;//scene->GetAntiAliasingLevel();
                int* sendBuffer = new int[width * chunkHeight + 4];

                Ray* rays = new Ray[antiAliasingLevel * antiAliasingLevel];
                for (int y = startY; y < startY + chunkHeight; ++y)
                {
                    for (int x = 0; x < width; ++x)
                    {
                        camera->CalculateRays(x, y, antiAliasingLevel, rays);

                        Color3 color(0.0f);
                        for (int i = 0; i < antiAliasingLevel * antiAliasingLevel; ++i)
                            color += scene->CastRay(rays[i]);

                        color = color / (float)(antiAliasingLevel * antiAliasingLevel);

                        sendBuffer[(y - startY) * width + x + 4] = (int)(color.Blue * 255.0f) | ((int)(color.Green * 255.0f) << 8) | ((int)(color.Red * 255.0f) << 16);
                    }

                    //int percentComplete = (double)(y - workerThreadState->Chunk.StartY) / workerThreadState->Chunk.ChunkHeight * 100.0;
                    //console.UpdateStatus(threadIndex + 1, "Thread ", threadIndex, ": Chunk received. Processing: ", percentComplete, "%");
                }

                //console.UpdateStatus(threadIndex + 1, "Thread ", threadIndex, ": Chunk received. Processing: 100%");

                // Cleanup resources.
                delete scene;
                delete camera;

                // Send the result.
                sendBuffer[0] = 3;
                sendBuffer[1] = (width * chunkHeight + 4) * 4 - 8;
                sendBuffer[2] = sceneId;
                sendBuffer[3] = chunkId;

                auto result = network->Send((char*)sendBuffer, (width * chunkHeight + 4) * 4);
                console->AddHistory(i, "Sent completed chunk to server: ", result, " : ", WSAGetLastError());

                delete[] sendBuffer;
            }

            delete network;
        });

        tasks.push_back(task);
    }

    for (unsigned int i = 0; i < totalThreads; i++)
        tasks[i].wait();

    delete console;
    return 0;
}