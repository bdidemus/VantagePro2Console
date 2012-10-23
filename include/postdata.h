#ifndef POSTDATA_H
#define POSTDATA_H

class VantageData;

class PostData
{
public:
	static bool postData(VantageData* dataObj);
private:
	static char* m_webPath;
};

#endif
