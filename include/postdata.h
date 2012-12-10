#ifndef POSTDATA_H
#define POSTDATA_H

class VantageData;

class PostData
{
public:
	static bool postData(VantageData* dataObj, bool writeFile = false);

	static void setWebPath(char* webpath) { m_webPath = webpath; }
	static void setOutFile(char* outFile) { m_outFile = outFile; }
private:
	static char* m_webPath;
	static char* m_outFile;
};

#endif
