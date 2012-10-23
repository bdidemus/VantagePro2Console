#include "postdata.h"
#include "VantageData.h"
#include <curl/curl.h>
#include <cstring>

// Set this to the loction of your webserver
char* PostData::m_webPath = "http://www.rhaithware.com/weatherstation/datareceiver.php";

bool PostData::postData(VantageData* dataObj)
{
	if(!dataObj)
	{
		return false;
	}

	CURL *curl;
	CURLcode res;

	//1000 chars should be enough
	char* postData = new char[1000];

	sprintf(postData, "outtemp=%f.2&intemp=%f.2&outhum=%d&inhum=%d&" \
		  "barpress=%f.2&winddir=%d&windspeed=%d&rainamount=%f.2&soilmois=%d",
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
