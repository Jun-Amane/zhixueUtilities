#include "zhixueUtilities.hpp"
#include <curl/curl.h>

size_t CurlWrite_CallbackFunc_StdString(void* contents, size_t size, size_t nmemb, std::string* s)
{
	size_t newLength = size * nmemb;
	try
	{
		s->append((char*)contents, newLength);
	}
	catch (std::bad_alloc& e)
	{
		//handle memory problem
		return 0;
	}
	return newLength;
}

std::string postAnsJson(std::string tchToken, std::string hwId){

	std::string POSTFIELDS = "{\"base\":{\"Authorization\":\""+tchToken+"\",\"appId\":\"OAXI57PG\",\"appVersion\":\"1.17.1877\",\"packageName\":\"com.iflytek.elpmobile.marktool\",\"sysType\":\"Android\",\"sysVersion\":\"Nashi\",\"udid\":\"\",\"userId\":\"0\",\"utag\":\"\"},\"params\":{\"hwId\":\""+hwId+"\"},\"token\":\""+tchToken+"\"}";
	std::string auth = "Authorization:" + tchToken;
	std::string len = "Content-Length:" + std::__cxx11::to_string(POSTFIELDS.size());

	CURL* curl;
	CURLcode res;
	struct curl_slist* headers = NULL;
	std::string str;

	headers = curl_slist_append(headers, len.c_str());
	headers = curl_slist_append(headers, auth.c_str());
	headers = curl_slist_append(headers, "Content-Type:application/json");


	curl = curl_easy_init();
	curl_easy_setopt(curl, CURLOPT_URL, postAnsURL);
	curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
	curl_easy_setopt(curl, CURLOPT_POSTFIELDS, POSTFIELDS.c_str());
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, CurlWrite_CallbackFunc_StdString);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, &str);
	curl_easy_setopt(curl, CURLOPT_POST, 1);
	curl_easy_setopt(curl, CURLOPT_VERBOSE, 0);
	//curl_easy_setopt(curl, CURLOPT_HEADER, 1);
	curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1);
	res = curl_easy_perform(curl);
	curl_easy_cleanup(curl);
	
	return str;
}

std::string getHwListJson(std::string stuToken){

	std::string getHwListURL = "https://mhw.zhixue.com/homework_middle_service/stuapp/getStudentHomeWorkList?createTime=1627527375497&pageIndex=1&completeStatus=0&pageSize=2147483647&subjectCode=-1&token="+stuToken;

	CURL* curl;
	CURLcode res;
	struct curl_slist* headers = NULL;
	std::string str;


	curl = curl_easy_init();
	curl_easy_setopt(curl, CURLOPT_URL, getHwListURL.c_str());
	curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, CurlWrite_CallbackFunc_StdString);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, &str);
	curl_easy_setopt(curl, CURLOPT_VERBOSE, 0);
	//curl_easy_setopt(curl, CURLOPT_HEADER, 1);
	curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1);
	res = curl_easy_perform(curl);
	curl_easy_cleanup(curl);
	
	return str;
}
