#include "zhixueUtilities.hpp"
#include <curl/curl.h>

namespace reqData
{
	size_t CurlWrite_CallbackFunc_StdString(void *contents, size_t size, size_t nmemb, std::string *s)
	{
		size_t newLength = size * nmemb;
		try
		{
			s->append((char *)contents, newLength);
		}
		catch (std::bad_alloc &e)
		{
			//handle memory problem
			return 0;
		}
		return newLength;
	}

	std::string postAnsJson(std::string tchToken, std::string hwId)
	{

		std::string POSTFIELDS = "{\"base\":{\"Authorization\":\"" + tchToken + "\",\"appId\":\"OAXI57PG\",\"appVersion\":\"1.17.1877\",\"packageName\":\"com.iflytek.elpmobile.marktool\",\"sysType\":\"Android\",\"sysVersion\":\"Nashi\",\"udid\":\"\",\"userId\":\"0\",\"utag\":\"\"},\"params\":{\"hwId\":\"" + hwId + "\"},\"token\":\"" + tchToken + "\"}";
		std::string auth = "Authorization:" + tchToken;
		std::string len = "Content-Length:" + std::__cxx11::to_string(POSTFIELDS.size());

		CURL *curl;
		CURLcode res;
		struct curl_slist *headers = nullptr;
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

	std::string getHwListJson(std::string stuToken, bool completed)
	{
		std::string getHwListURL;
		if (!completed)
		{
			getHwListURL = "https://mhw.zhixue.com/homework_middle_service/stuapp/getStudentHomeWorkList?createTime=1627527375497&pageIndex=1&completeStatus=0&pageSize=2147483647&subjectCode=-1&token=" + stuToken;
		}
		else
		{
			getHwListURL = "https://mhw.zhixue.com/homework_middle_service/stuapp/getStudentHomeWorkList?createTime=1627527375497&pageIndex=1&completeStatus=1&pageSize=2147483647&subjectCode=-1&token=" + stuToken;
		}

		CURL *curl;
		CURLcode res;
		struct curl_slist *headers = nullptr;
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

	std::string redoHomework(std::string tchToken, std::string stuId, std::string hwId)
	{

		std::string POSTFIELDS = "{\"base\":{\"Authorization\":\"" + tchToken + "\",\"appId\":\"OAXI57PG\",\"appVersion\":\"1.17.1877\",\"packageName\":\"com.iflytek.elpmobile.marktool\",\"sysType\":\"Android\",\"sysVersion\":\"Nashi\",\"udid\":\"\",\"userId\":\"0\",\"utag\":\"\"},\"params\":{\"classId\":\"0\",\"hwId\":\"" + hwId + "\",\"redoReason\":\"Nashi\",\"studentId\":\"" + stuId + "\"},\"token\":\"" + tchToken + "\"}";
		std::string auth = "Authorization:" + tchToken;
		std::string len = "Content-Length:" + std::__cxx11::to_string(POSTFIELDS.size());

		CURL *curl;
		CURLcode res;
		struct curl_slist *headers = nullptr;
		std::string str;

		headers = curl_slist_append(headers, len.c_str());
		headers = curl_slist_append(headers, auth.c_str());
		headers = curl_slist_append(headers, "Content-Type:application/json");

		curl = curl_easy_init();
		curl_easy_setopt(curl, CURLOPT_URL, redoURL);
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

		int rtn = analyzeJson::analyzeIfSuccess(str);
		if (rtn == 0)
		{
			return ("成功！");
		}
		else
		{
			return str;
		}
	}

	std::string sendSubbmission(std::string POSTFIELDS, std::string stuToken)
	{

		std::string auth = "Authorization:" + stuToken;
		std::string len = "Content-Length:" + std::__cxx11::to_string(POSTFIELDS.size());

		CURL *curl;
		CURLcode res;
		struct curl_slist *headers = nullptr;
		std::string str;

		headers = curl_slist_append(headers, len.c_str());
		headers = curl_slist_append(headers, auth.c_str());
		headers = curl_slist_append(headers, "Content-Type:application/json");

		curl = curl_easy_init();
		curl_easy_setopt(curl, CURLOPT_URL, submitURL);
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

		int rtn = analyzeJson::analyzeIfSuccess(str);
		if (rtn == 0)
		{
			return ("成功！");
		}
		else
		{
			return str;
		}
	}

	std::string loginApi(std::string username, std::string passwd, std::string appId, std::string ncetAppId)
	{

		std::string POSTFIELDS = "encode=true&password=" + passwd + "&ncetAppId=" + ncetAppId + "&method=sso.login.account&encodeType=R2%2FP&useAreaExamNo=true&appId=" + appId + "&client=android&key=auto&mac=00%3A00%3A00%3A00%3A00%3A00&username=" + username + "&extInfo=%7B%22deviceId%22%3A%220%22%7D";
		std::string len = "Content-Length:" + std::__cxx11::to_string(POSTFIELDS.size());

		CURL *curl;
		CURLcode res;
		struct curl_slist *headers = nullptr;
		std::string str;

		headers = curl_slist_append(headers, len.c_str());
		headers = curl_slist_append(headers, "Content-Type:application/x-www-form-urlencoded");

		curl = curl_easy_init();
		curl_easy_setopt(curl, CURLOPT_URL, loginApiUrl);
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
	std::string casLogin(std::string userId, std::string at)
	{

		std::string POSTFIELDS = "at=" + at + "&ncetAppId=5nSML4Imp8JYefnV3EIfXcOgx4JpPQ7M&loginType=login_name&tokenTimeout=0&userId=" + userId + "&autoLogin=false";
		std::string len = "Content-Length:" + std::__cxx11::to_string(POSTFIELDS.size());

		CURL *curl;
		CURLcode res;
		struct curl_slist *headers = nullptr;
		std::string str;

		headers = curl_slist_append(headers, len.c_str());
		headers = curl_slist_append(headers, "Content-Type: application/x-www-form-urlencoded");
		//headers = curl_slist_append(headers, "Accept-Encoding: gzip");
		headers = curl_slist_append(headers, "User-Agent: okhttp/3.12.12");
		headers = curl_slist_append(headers, "deviceId:0");
		headers = curl_slist_append(headers, "browserVersion:");
		headers = curl_slist_append(headers, "channelId:");
		headers = curl_slist_append(headers, "deviceMac:00:00:00:00:00:00");
		headers = curl_slist_append(headers, "appName:com.iflytek.elpmobile.student");
		headers = curl_slist_append(headers, "channel:11000001");
		headers = curl_slist_append(headers, "resolution:");
		headers = curl_slist_append(headers, "authbizcode:0001");
		headers = curl_slist_append(headers, "deviceType:");
		headers = curl_slist_append(headers, "deviceName:");
		headers = curl_slist_append(headers, "sucUserToken:");

		curl = curl_easy_init();
		curl_easy_setopt(curl, CURLOPT_URL, casLoginUrl);
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

	std::string uniteLogin(std::string userId, std::string at)
	{

		std::string POSTFIELDS = "token=&appId=zhixue_teacher&at=" + at + "&autologin=false&ncetAppId=E3KzZvjVkC8kQXWBlR5521GztpApNn99&userId=" + userId;
		std::string len = "Content-Length:" + std::__cxx11::to_string(POSTFIELDS.size());

		CURL *curl;
		CURLcode res;
		struct curl_slist *headers = nullptr;
		std::string str;

		headers = curl_slist_append(headers, len.c_str());
		headers = curl_slist_append(headers, "Content-Type: application/x-www-form-urlencoded");
		//headers = curl_slist_append(headers, "Accept-Encoding: gzip");
		headers = curl_slist_append(headers, "User-Agent: okhttp/3.12.12");
		headers = curl_slist_append(headers, "deviceId:0");
		headers = curl_slist_append(headers, "browserVersion:");
		headers = curl_slist_append(headers, "channelId:");
		headers = curl_slist_append(headers, "deviceMac:00:00:00:00:00:00");
		headers = curl_slist_append(headers, "appName:com.iflytek.elpmobile.marktool");
		headers = curl_slist_append(headers, "channel:31000001");
		headers = curl_slist_append(headers, "resolution:");
		headers = curl_slist_append(headers, "authbizcode:0002");
		headers = curl_slist_append(headers, "deviceType:");
		headers = curl_slist_append(headers, "deviceName:");
		headers = curl_slist_append(headers, "sucUserToken:");

		curl = curl_easy_init();
		curl_easy_setopt(curl, CURLOPT_URL, uniteLoginUrl);
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
	std::string getReviseQuestion(std::string stuId, std::string hwId, std::string stuToken)
	{

		std::string POSTFIELDS = "{\"base\":{\"appId\":\"APP\",\"extend\":{},\"packageName\":\"\",\"sysType\":\"\",\"sysVersion\":\"\",\"udid\":\"\"},\"params\":{\"hwId\":\"" + hwId + "\",\"studentId\":\"" + stuId + "\"}}";
		std::string len = "Content-Length:" + std::__cxx11::to_string(POSTFIELDS.size());
		std::string auth = "Authorization:" + stuToken;

		CURL *curl;
		CURLcode res;
		struct curl_slist *headers = nullptr;
		std::string str;

		headers = curl_slist_append(headers, len.c_str());
		headers = curl_slist_append(headers, auth.c_str());
		headers = curl_slist_append(headers, "Content-Type:application/json");

		curl = curl_easy_init();
		curl_easy_setopt(curl, CURLOPT_URL, reviseQuestionUrl);
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

	std::string getHwDetail(std::string tchToken, std::string hwId)
	{

		std::string POSTFIELDS = "{\"base\":{\"appId\":\"OAXI57PG\",\"appVersion\":\"1.17.1877\",\"packageName\":\"com.iflytek.elpmobile.marktool\",\"sysType\":\"Android\",\"sysVersion\":\"\",\"udid\":\"00:00:00:00:00:00\"},\"params\":{\"hwId\":\"" + hwId + "\"}}";
		std::string len = "Content-Length:" + std::__cxx11::to_string(POSTFIELDS.size());
		std::string auth = "Authorization:" + tchToken;

		CURL *curl;
		CURLcode res;
		struct curl_slist *headers = nullptr;
		std::string str;

		headers = curl_slist_append(headers, len.c_str());
		headers = curl_slist_append(headers, auth.c_str());
		headers = curl_slist_append(headers, "Content-Type:application/json");

		curl = curl_easy_init();
		curl_easy_setopt(curl, CURLOPT_URL, hwDetailUrl);
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

	std::string updateHw(std::string tchToken, std::string POSTFIELDS)
	{
		std::string len = "Content-Length:" + std::__cxx11::to_string(POSTFIELDS.size());
		std::string auth = "Authorization:" + tchToken;

		CURL *curl;
		CURLcode res;
		struct curl_slist *headers = nullptr;
		std::string str;

		headers = curl_slist_append(headers, len.c_str());
		headers = curl_slist_append(headers, auth.c_str());
		headers = curl_slist_append(headers, "Content-Type:application/json");

		curl = curl_easy_init();
		curl_easy_setopt(curl, CURLOPT_URL, updateHwUrl);
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

		int rtn = analyzeJson::analyzeIfSuccess(str);
		if (rtn == 0)
		{
			return ("成功！");
		}
		else
		{
			return str;
		}
	}

}