#include "vantageconsole.h"

using namespace std;

int main(int argc, char **argv)
{
	std::string port = "/dev/ttyUSB0";

	if(argc > 1)
	{
		port = argv[1];
	}

	VantageConsole* console = new VantageConsole(port, true);

	console->openConnection();
	console->startDataLoop();

	return 0;
}
