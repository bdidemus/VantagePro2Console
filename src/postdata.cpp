#include "postdata.h"
#include "VantageData.h"
#include <curl/curl.h>
#include <cstring>
#include <iostream>
#include <fstream>
#include <ctime>

// Set this to the location of your default web server (if you don't want to use the command line)
char* PostData::m_webPath = 0;
char* PostData::m_outFile = 0;

bool PostData::postData(VantageData* dataObj, bool writeFile)
{
	if(!dataObj)
	{
		return false;
	}

	CURL *curl;
	CURLcode res;

	//1000 chars should be enough
	char postData[1000];

	sprintf(postData, "outtemp=%.2f&intemp=%.2f&outhum=%d&inhum=%d&" \
		  "barpress=%.2f&winddir=%d&windspeed=%d&rainamount=%.2f&soilmois=%d",
		  dataObj->getOutsideTempC(),
		  dataObj->getInsideTempC(),
		  dataObj->getOutsideHumidity(),
		  dataObj->getInsideHumidity(),
		  dataObj->getBarometer(),
		  dataObj->getWindDirection(),
		  dataObj->getWindSpeedKmh(),
		  dataObj->getRainRatemm(),
		  dataObj->getSoilMoisture(0));

	// Test data
	/*sprintf(postData, "outtemp=%.2f&intemp=%.2f&outhum=%d&inhum=%d&" \
		  "barpress=%.2f&winddir=%d&windspeed=%d&rainamount=%.2f&soilmois=%d",
		  19.23f, 22.13f, 32, 76, 23.31f, 321, 11, 0.21f, 2);*/

	if(writeFile && m_outFile)
	{
		char fileData[1000];

		time_t t = time(0);   // get time now
		struct tm* now = localtime(&t);
		char * strDate = asctime(now);
		strDate[strlen(strDate)-1] = '\0';

		sprintf(fileData, "%s,%.2f,%.2f,%d,%d,%.2f,%d,%d,%.2f,%d",
			strDate,
			dataObj->getOutsideTempC(),
			dataObj->getInsideTempC(),
			dataObj->getOutsideHumidity(),
			dataObj->getInsideHumidity(),
			dataObj->getBarometer(),
			dataObj->getWindDirection(),
			dataObj->getWindSpeedKmh(),
			dataObj->getRainRatemm(),
			dataObj->getSoilMoisture(0));

		std::ofstream file;
		file.open(m_outFile, std::ios::app);
		file << fileData;
		file << "\n";
		file.close();
	}

	curl = curl_easy_init();

	if(curl)
	{
		curl_easy_setopt(curl, CURLOPT_URL, m_webPath);
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postData);

		curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, strlen(postData));

		res = curl_easy_perform(curl);

		curl_easy_cleanup(curl);
	}

	if(res == CURLE_OK)
	{
	  return true;
	}
	else
	{
	  return false;
	}
}
