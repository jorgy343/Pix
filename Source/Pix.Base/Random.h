#pragma once

namespace Pix::Base
{
    class Random
    {
    private:
        union
        {
            unsigned int _seedi;
            float _seedf;
        };

    public:
        Random()
        {
            _seedi = 92134;
        }

        inline int GetInteger()
        {
            _seedi *= 16807;
            return _seedi;
        }

        inline float GetNormalizedFloat()
        {
            _seedi *= 16807;
            _seedi = (_seedi & 0x7FFFFF) | 0x3F800000; // Random float in range [1, 2).
            _seedf -= 1.0f; // Reduce range to [0, 1).

            return _seedf;
        }
    };
}