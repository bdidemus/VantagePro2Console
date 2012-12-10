#include "vantageconsole.h"
#include "VantageData.h"
#include <stdio.h>
#include <fcntl.h>
#include <termios.h>
#include <iostream>
#include "postdata.h"

using namespace std;

#define BUFFER_SIZE 500
#define DELAY 30 // Time between next console query

VantageConsole::VantageConsole(bool verbose) :
m_strPort("/dev/ttyUSB0"),
m_handle(-1),
m_isAwake(false),
m_loopTerminator(true),
m_verbose(verbose),
m_writeFile(false)
{
}

void VantageConsole::openConnection()
{
	//int fd = open(port, O_RDWR | O_NOCTTY | O_NDELAY | O_NONBLOCK);
	m_handle = open(m_strPort.c_str(), O_RDWR | O_NONBLOCK);
	if(m_handle == -1)
	{
		m_isAwake = false;
		printf("Failed to open port %s", m_strPort.c_str());
		throw std::exception();
	}

	struct termios port_settings;      // structure to store the port settings in

	cfsetispeed(&port_settings, B19200);    // set baud rates
	cfsetospeed(&port_settings, B19200);

	port_settings.c_cflag &= ~PARENB;    // set no parity, stop bits, data bits
	port_settings.c_cflag &= ~CSTART;
	port_settings.c_cflag &= ~CSTOPB;
	port_settings.c_cflag &= ~CSIZE;
	port_settings.c_cflag |= CS8;

	cfmakeraw(&port_settings);
	tcsetattr(m_handle, TCSANOW, &port_settings);    // apply the settings to the port

	if(!wakeUpConsole())
	{
		printf("Failed to wakeup console.\n");
		throw exception();
	}
}

bool VantageConsole::wakeUpConsole()
{
	for(int i = 0; i < 5; i++)
	{
		printf("waking up console attempt %d\n", i+1);

		write(m_handle, "\n", 1); // wakeup

		sleep(4);

		unsigned char buffer[BUFFER_SIZE];
		read(m_handle, &buffer, 2);

		if(buffer[0] == '\n' && buffer[1] == '\r')
		{
			printf("I'm awake\n");
			m_isAwake = true;

			break;
		}
	}

	return m_isAwake;
}

void VantageConsole::startDataLoop()
{
	if(isAwake())
	{
		m_loopTerminator = false;
		do
		{
			write(m_handle, "LOOP 1\n", 8);

			unsigned char buffer[BUFFER_SIZE];
			//memset(m_buffer, 0, sizeof(m_buffer)*BUFFER_SIZE);

			sleep(2);

			int bytesRead = read(m_handle, &buffer, BUFFER_SIZE);

			if(bytesRead > 0)
			{
				VantageData* vantageData = new VantageData(buffer, BUFFER_SIZE);

				if(m_verbose)
				{
					printf("Inside Temp: %5.2f \n", vantageData->getInsideTempC());
					printf("Outside Temp: %5.2f \n\n", vantageData->getOutsideTempC());
					printf("Inside Humidity: %d \n", vantageData->getInsideHumidity());
					printf("Outside Humidity: %d \n\n", vantageData->getOutsideHumidity());
					printf("Barometer Value: %5.2f \n\n", vantageData->getBarometer());
					printf("Wind Direction: %d \n", vantageData->getWindDirection());
					printf("Wind Speed: %d /kmh \n\n", vantageData->getWindSpeedKmh());
				}
				PostData::postData(vantageData, m_writeFile);

				delete vantageData;
			}

			sleep(DELAY);
		} while(!m_loopTerminator);

	}
}

void VantageConsole::stopDataLoop()
{
	m_loopTerminator = true;
}

bool VantageConsole::isAwake()
{
	return m_isAwake;
}

void VantageConsole::setOutFile(char* outFile)
{
	PostData::setOutFile(outFile);
	m_writeFile = true;
}

void VantageConsole::setWebPath(char* webPath)
{
	PostData::setWebPath(webPath);
}

void VantageConsole::setPort(const std::string& port)
{
	m_strPort = port;
}

VantageConsole::~VantageConsole()
{
}

