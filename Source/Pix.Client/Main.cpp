#include <tchar.h>

#include "WindowsConsole.h"
#include "WindowsNetwork.h"

using namespace Pix::Client;

int _tmain(int argc, _TCHAR* argv[])
{
    WindowsConsole* console = new WindowsConsole(8);
    INetwork* network = new WindowsNetwork("127.0.0.1", "54000");

    console->UpdateStatus(2, "sdfsdf", 45, " : ", 34);

    delete console;
    delete network;

    return 0;
}