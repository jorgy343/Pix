#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include <SDKDDKVer.h>

#include <tchar.h>

#include "XmlSceneLoader.h"

using namespace Pix::Engine;

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }

    return TRUE;
}

extern "C"
{
    __declspec(dllexport) void Trace(
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
        const char* sceneXml,
        float* pixelData)
    {
        auto subPixelWidth = subPixelEndX - subPixelStartX + 1;
        auto subPixelHeight = subPixelEndY - subPixelStartY + 1;

        XmlSceneLoader sceneLoader(sceneXml);

        const auto materialGeometryMap = new MaterialGeometryMap();
        const auto scene = sceneLoader.CreateScene(materialGeometryMap);

        const auto rays = new Ray[subPixelWidth * subPixelHeight];
        for (auto y = startY; y < startY + chunkHeight; ++y)
        {
            for (auto x = 0; x < width; ++x)
            {
                scene->GetCamera()->CalculateRays(IntVector2(x, y), IntVector2(maxSubPixelX, maxSubPixelY), IntVector2(subPixelStartX, subPixelStartY), IntVector2(subPixelEndX, subPixelEndY), rays);

                Color3 color(0.0f);
                for (auto i = 0; i < subPixelWidth * subPixelHeight; ++i)
                    color += scene->CastRay(rays[i]);

                pixelData[(y - startY) * width * 3 + x * 3 + 0] = color.Red;
                pixelData[(y - startY) * width * 3 + x * 3 + 1] = color.Green;
                pixelData[(y - startY) * width * 3 + x * 3 + 2] = color.Blue;
            }
        }
    }
}