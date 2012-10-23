#include "VantageData.h"
#include <cstring>

VantageData::VantageData(unsigned char* data, int size) :
m_data(0)
{
	m_data = new unsigned char[500];
	memcpy(m_data, data, size);
}

float VantageData::getOutsideTempC()
{
	return (getOutsideTempF() - 32) * 5 / 9;
}

float VantageData::getOutsideTempF()
{
	return (float)((m_data[14] << 8) | m_data[13]) / 10.f;
}

float VantageData::getInsideTempC()
{
	return (getInsideTempF() - 32) * 5 / 9;
}

float VantageData::getInsideTempF()
{
	return (float)((m_data[11] << 8) | m_data[10]) / 10.f;
}

int VantageData::getOutsideHumidity()
{
	return (int)m_data[34];
}

int VantageData::getInsideHumidity()
{
	return (int)m_data[12];
}

float VantageData::getBarometer()
{
	return ((unsigned int)((m_data[9] << 8) | m_data[8])) / 1000.f;
}

int VantageData::getWindDirection()
{
	return (unsigned int)m_data[17];
}

int VantageData::getWindSpeedKmh()
{
	return (int)(getWindSpeedMph() * 1.6f);
}

int VantageData::getWindSpeedMph()
{
	return (unsigned int)m_data[15];
}

float VantageData::getRainRatemm()
{
	return (unsigned int)m_data[43] * 0.2;
}

int VantageData::getSoilMoisture(int sensor)
{
	int val = -1;
	if(sensor >= 0 && sensor < 4) {
		val = m_data[63+sensor];
	}

	return val;
}

VantageData::~VantageData()
{
	delete m_data;
}




