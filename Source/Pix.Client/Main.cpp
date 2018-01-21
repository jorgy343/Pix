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
    SetPriorityClass(GetCurrentProcess(), BELOW_NORMAL_PRIORITY_CLASS);

    unsigned int totalThreads = max(std::thread::hardware_concurrency(), 1);
    totalThreads = 1;

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

                int maxSubPixelX = *(int*)(messageData + 24);
                int maxSubPixelY = *(int*)(messageData + 28);

                int subPixelStartX = *(int*)(messageData + 32);
                int subPixelStartY = *(int*)(messageData + 36);
                int subPixelEndX = *(int*)(messageData + 40);
                int subPixelEndY = *(int*)(messageData + 44);

                const char* sceneXml = messageData + 48;
                console->UpdateStatusAndAddHistory(i, "Received chunk. Scene ID: ", sceneId, " Chunk ID: ", chunkId, ". Processing...");

                int subPixelWidth = subPixelEndX - subPixelStartX + 1;
                int subPixelHeight = subPixelEndY - subPixelStartY + 1;

                XmlSceneLoader sceneLoader(sceneXml);

                auto materialGeometryMap = new MaterialGeometryMap();
                auto scene = sceneLoader.CreateScene(materialGeometryMap);

                // Render the scene.
                uint32_t* sendBuffer = new uint32_t[width * chunkHeight * 3 + 4]; // 3: three floats per pixel; 4: four integers for the header

                Ray* rays = new Ray[subPixelWidth * subPixelHeight];
                for (int y = startY; y < startY + chunkHeight; ++y)
                {
                    for (int x = 0; x < width; ++x)
                    {
                        //if (x != 221 || y != 73)
                        //    continue;

                        scene->GetCamera()->CalculateRays(IntVector2(x, y), IntVector2(maxSubPixelX, maxSubPixelY), IntVector2(subPixelStartX, subPixelStartY), IntVector2(subPixelEndX, subPixelEndY), rays);

                        Color3 color(0.0f);
                        for (int i = 0; i < subPixelWidth * subPixelHeight; ++i)
                            color += scene->CastRay(rays[i]);

                        float* floatBuffer = (float*)sendBuffer;

                        floatBuffer[(y - startY) * width * 3 + x * 3 + 4 + 0] = color.Red;
                        floatBuffer[(y - startY) * width * 3 + x * 3 + 4 + 1] = color.Green;
                        floatBuffer[(y - startY) * width * 3 + x * 3 + 4 + 2] = color.Blue;
                    }
                }

                // Send the result.
                sendBuffer[0] = 1;
                sendBuffer[1] = (width * chunkHeight * 3 + 2) * 4;
                sendBuffer[2] = sceneId;
                sendBuffer[3] = chunkId;

                auto result = network->Send((char*)sendBuffer, (width * chunkHeight * 3 + 4) * 4);
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