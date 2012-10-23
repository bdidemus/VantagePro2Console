#ifndef VANTAGEDATA_H
#define VANTAGEDATA_H

class VantageData
{
public:
	VantageData(unsigned char* data, int size);
	~VantageData();

	float getOutsideTempF();
	float getOutsideTempC();

	float getInsideTempF();
	float getInsideTempC();

	int getOutsideHumidity();
	int getInsideHumidity();

	/**
	 * @return float inch of mercury
	 */
	float getBarometer();

	/**
	 * 	value from 0 to 360 degrees
	 * 	0 - no wind data
	 * 	90 - East
	 * 	180 - South
	 * 	240 - West
	 * 	360 - North
	 */
	int getWindDirection();
	/**
	 *
	 */
	int getWindSpeedMph();
	int getWindSpeedKmh();

	float getRainRatemm();

	/**
	 * 4 possible sensors reporting data
	 *
	 * 	@param sensor
	 * 	0 index of sensor to use
	 *
	 * 	@return int < 0, error getting value
	 */
	int getSoilMoisture(int sensor);

private:
	unsigned char* m_data;
};

#endif
