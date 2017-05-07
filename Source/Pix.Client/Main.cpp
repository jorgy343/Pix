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