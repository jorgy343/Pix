using System;

namespace Pix.Managed.Common
{
    public struct Tiny
    {
        private readonly ushort _value;

        public Tiny(ushort value)
        {
            _value = value;
        }

        public Tiny(float value)
        {
            if (float.IsNegativeInfinity(value) || float.IsNaN(value) || value < 0f)
            {
                _value = 0;
            }
            else if (float.IsPositiveInfinity(value))
            {
                _value = 0b0000_1111_1111_1111;
            }
            else
            {
                var exponent = (0x7F80_0000 & (uint)value) >> 23;

                if (exponent > 4)
                {
                    exponent = 4;
                }

                _value = 0;
                _value |= (ushort)(exponent << 10); // Set the exponent.
            }
        }

        public Tiny(double value)
            : this((float)value)
        {

        }
    }
}