using System.Runtime.InteropServices;

namespace Pix.Server
{
    [StructLayout(LayoutKind.Explicit, Pack = 1)]
    struct ColorBgr32
    {
        [FieldOffset(0)]
        public byte Blue;

        [FieldOffset(1)]
        public byte Green;

        [FieldOffset(2)]
        public byte Red;

        [FieldOffset(3)]
        public byte X;

        public ColorBgr32(int value)
        {
            Blue = (byte)(value & 0x0000_00ff);
            Green = (byte)(value & 0x0000_ff00);
            Red = (byte)(value & 0x00ff_0000);
            X = (byte)(value & 0xff00_0000);
        }

        public int ToInt32()
        {
            return Blue | (Green << 8) | (Red << 16) | (X << 24);
        }
    }
}