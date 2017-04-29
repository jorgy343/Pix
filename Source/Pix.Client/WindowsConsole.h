#pragma once

#define WIN32_LEAN_AND_MEAN

#include <Windows.h>
#include <ppl.h>

#include <functional>
#include <sstream>
#include <vector>

namespace Pix::Client
{
    class WindowsConsole
    {
    private:
        concurrency::reader_writer_lock _lock;

        int _width;
        int _height;

        HANDLE _handle;

        std::unique_ptr<CHAR_INFO[]> _buffer;
        std::vector<std::string> _stringBuffer;

        SMALL_RECT _windowSize;
        COORD _bufferSize;
        COORD _bufferCoordinates;
        SMALL_RECT _completeWriteArea;

        std::unique_ptr<CHAR_INFO[]> ReadLineBuffer(int line)
        {
            auto buffer = std::make_unique<CHAR_INFO[]>(_width);
            SMALL_RECT window = { (SHORT)0, (SHORT)line, (SHORT)(_width - 1), (SHORT)(line + 1) };

            ReadConsoleOutputA(_handle, buffer.get(), COORD{ (short)_width, 1 }, COORD{ 0, 0 }, &window);
        }

    public:
        const int HistoryEntries = 6;

        WindowsConsole(const WindowsConsole&) = delete;
        WindowsConsole(WindowsConsole&&) = delete;

        WindowsConsole& operator=(const WindowsConsole&) & = delete;
        WindowsConsole& operator=(WindowsConsole&&) & = delete;

        WindowsConsole(int totalGroups)
        {
            _width = 120;
            _height = totalGroups * HistoryEntries;

            _windowSize = { 0, 0, (short)_width - 1, (short)_height - 1 };
            _bufferSize = { (short)_width, (short)_height };
            _bufferCoordinates = { 0, 0 };
            _completeWriteArea = { 0, 0, (short)_width - 1, (short)_height - 1 };

            _buffer = std::make_unique<CHAR_INFO[]>(_width * _height);
            memset(_buffer.get(), 0, sizeof(*_buffer.get()) * _width * _height);

            _stringBuffer = std::vector<std::string>(_height);
            for (int i = 0; i < _height; ++i)
                _stringBuffer.push_back(std::string());

            _handle = GetStdHandle(STD_OUTPUT_HANDLE);

            SetConsoleWindowInfo(_handle, true, &_windowSize);
            SetConsoleScreenBufferSize(_handle, _bufferSize);

            for (int i = 0; i < _width * _height; ++i)
                _buffer[i].Attributes = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;

            WriteConsoleOutputA(_handle, _buffer.get(), _bufferSize, _bufferCoordinates, &_completeWriteArea);
        }

    private:
        void UpdateBuffer()
        {
            _lock.lock();
            for (int row = 0; row < _height; ++row)
            {
                auto pointer = _buffer.get() + row * _width;
                auto string = _stringBuffer[row];

                // Move this block to the initialization code.
                if (row % HistoryEntries == 0)
                {
                    auto tempPointer = pointer;
                    for (int i = 0; i < _width; ++i)
                        (tempPointer++)->Attributes = 11;
                }

                int i = 0;
                for (; i < min(string.length(), _width); ++i)
                    (pointer++)->Char.AsciiChar = string[i];

                for (; i < _width; ++i)
                    (pointer++)->Char.AsciiChar = ' ';
            }

            WriteConsoleOutputA(_handle, _buffer.get(), _bufferSize, _bufferCoordinates, &_completeWriteArea);
            _lock.unlock();
        }

        void CreateString(std::stringstream& stringStream)
        {

        }

        template <typename T, typename... Ts>
        void CreateString(std::stringstream& stringStream, T value, Ts... values)
        {
            stringStream << value;
            CreateString(stringStream, values...);
        }

    public:
        template <typename... Ts>
        void UpdateStatus(int group, Ts... values)
        {
            std::stringstream stringStream;
            CreateString(stringStream, values...);

            _stringBuffer[group * HistoryEntries] = stringStream.str();
            UpdateBuffer();
        }

        template <typename... Ts>
        void AddHistory(int group, Ts... values)
        {
            std::stringstream stringStream;
            CreateString(stringStream, values...);

            for (int i = 1; i <= HistoryEntries - 2; ++i)
                _stringBuffer[group * HistoryEntries + i] = _stringBuffer[group * HistoryEntries + i + 1];

            _stringBuffer[group * HistoryEntries + HistoryEntries - 1] = "    " + stringStream.str();
            UpdateBuffer();
        }
    };
}