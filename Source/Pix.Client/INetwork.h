#pragma once

#include <memory>

#pragma warning(push)
#pragma warning(disable: 4005)
#define GetMessage GetMessage // The Windows headers define "GetMessage" as "GetMessageW". Undo that.
#pragma warning(pop)

namespace Pix::Client
{
    class INetwork
    {
    public:
        virtual int Send(const char* buffer, int bufferSizeInBytes) const = 0;
        virtual void SendChunkRequestedMessage() const = 0;

        virtual std::unique_ptr<const char[]> GetMessage() = 0;
    };
}