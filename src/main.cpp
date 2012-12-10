#include "vantageconsole.h"

int main(int argc, char **argv)
{
	bool verbose = true;

	VantageConsole* console = new VantageConsole(verbose);

	if(argc > 1)
	{
		console->setPort(argv[1]);
	}
	if(argc > 2)
	{
		console->setWebPath(argv[2]);
	}
	if(argc > 3)
	{
		console->setOutFile(argv[3]);
	}

	console->openConnection();
	console->startDataLoop();

	return 0;
}
