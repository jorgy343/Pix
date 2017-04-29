#pragma once

namespace Pix::Client
{
    enum class NetworkState
    {
        Initialize,
        MessageReady,
        ReadingMessageType,
        ReadingMessageSize,
        ReadingMessage
    };
}