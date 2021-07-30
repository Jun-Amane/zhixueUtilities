#pragma once

#include <iostream>
#include <string.h>




#define postAnsURL "https://mhw.zhixue.com/hw/manage/homework/redeploy"




size_t CurlWrite_CallbackFunc_StdString(void* contents, size_t size, size_t nmemb, std::string* s);
std::string postAnsJson(std::string tchToken, std::string hwId);
std::string analyzeAnsJson(std::string inputJson);
std::string analyzeHwListJson(std::string inputJson);
std::string getHwListJson(std::string stuToken);