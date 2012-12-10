#ifndef VANTAGECONSOLE_H
#define VANTAGECONSOLE_H

#include <string>
#include <cstring>

class VantageConsole
{
public:
	VantageConsole(bool verbose = false);
	~VantageConsole();

	void openConnection();

	void startDataLoop();
	void stopDataLoop();

	void setOutFile(char* outFile);
	void setWebPath(char* webPath);
	void setPort(const std::string&);

	bool isAwake();

private:
	bool wakeUpConsole();

	std::string m_strPort;

	int m_handle; // hanlde to the serial connection

	bool m_isAwake;
	bool m_verbose; // prints incoming data to console
	bool m_loopTerminator;
	bool m_writeFile;
};

#endif
