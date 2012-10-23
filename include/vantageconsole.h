#ifndef VANTAGECONSOLE_H
#define VANTAGECONSOLE_H

#include <string>
#include <cstring>

class VantageConsole
{
public:
	VantageConsole(const std::string& port, bool verbose = false);

	void openConnection();

	void startDataLoop();

	bool isAwake();

private:
	bool wakeUpConsole();

	unsigned char *m_buffer;

	std::string m_strPort;

	int m_handle; // hanlde to the serial connection

	bool m_isAwake;
	bool m_verbose; // prints incoming data to console
	bool m_loopTerminator;
};

#endif
