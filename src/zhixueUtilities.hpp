#pragma once

#include <iostream>
#include <string.h>
#include <memory>

#define postAnsURL "https://mhw.zhixue.com/hw/manage/homework/redeploy"
#define redoURL "https://mhw.zhixue.com/hw/correction/redo"
#define clkHwRedoUrl "https://mhw.zhixue.com/hw/clock/comment/redo"
#define submitURL "https://mhw.zhixue.com/hw/answer/homework/submit"

#define loginApiUrl "https://open.changyan.com/sso/v1/api"
#define casLoginUrl "https://www.zhixue.com/container/app/login/casLogin"
#define uniteLoginUrl "https://app.zhixue.com/appteacher/home/uniteLogin?"

#define reviseQuestionUrl "https://mhw.zhixue.com/hw/revise/questions"
#define hwDetailUrl "https://mhw.zhixue.com/hw/homework/detail"
#define updateHwUrl "https://mhw.zhixue.com/hw/manage/homework/update"
#define clkHWDetailUrl "https://mhw.zhixue.com/hw/clock/answer/getClockHomeworkDetail"

#define getAttachmentUrl "https://mhw.zhixue.com/hw/homework/attachment/list"

#define indexOverViewUrl "https://mhw.zhixue.com/hwreport/class/indexOverView"
#define listQuestionViewUrl "https://mhw.zhixue.com/hwreport/question/listQuestionView" 
#define getQuestionDetailUrl "https://mhw.zhixue.com/hwreport/question/getQuestionDetail"

extern bool _EMIT_UTF8 = true;

namespace analyzeJson
{
    std::string analyzeAnsJson(std::string inputJson);
    std::string analyzeHwListJson(std::string inputJson);

    int analyzeIfSuccess(std::string str);

    std::string index2stuHwId(std::string inputJson, std::string index);
    std::string index2hwId(std::string inputJson, std::string index);
    std::string clkHwDetail2clockRecordId(std::string inputJson);

    std::string format(std::string inputJson);

    std::string analyzeAttachJson(std::string inputJson);
}

namespace reqData
{
    size_t CurlWrite_CallbackFunc_StdString(void *contents, size_t size, size_t nmemb, std::string *s);
    
    std::string postAnsJson(std::string tchToken, std::string hwId);
    std::string getAttachJson(std::string stuToken, std::string stuId, std::string hwId);

    std::string getHwListJson(std::string stuToken, bool completed);
    std::string redoHomework(std::string tchToken, std::string stuToken, std::string userId, std::string hwId, bool isClkHw, std::string stuHwId);
    std::string getClkHwDetail(std::string stuToken, std::string hwId, std::string stuHwId);

    std::string sendSubbmission(std::string POSTFIELDS, std::string stuToken);

    std::string casLogin(std::string userId, std::string at);
    std::string loginApi(std::string username, std::string passwd, std::string appId, std::string ncetAppId);
    std::string uniteLogin(std::string userId, std::string at);

    std::string getReviseQuestion(std::string stuId, std::string hwId, std::string stuToken);

    std::string getHwDetail(std::string tchToken, std::string hwId);
    std::string updateHw(std::string tchToken, std::string POSTFIELDS);

    std::string showHwSubmitDetail(std::string tchToken, std::string hwId, std::string clazzId);
    std::string listQuestionView(std::string tchToken, std::string hwId, std::string clazzId);
    std::string getQuestionDetail(std::string tchToken, std::string hwId, std::string clazzId, std::string questionId);
}

namespace submission
{
    std::string prepareSubmJson(std::string inputStr, std::string stuToken, std::string stuHwId, std::string attachmentUrl);
    std::string submissionTemplate(std::string stuToken, std::string stuHwId);

    std::string prepareReviJson(std::string inputStr, std::string stuToken, std::string stuHwId, std::string stuId, std::string hwId, std::string attachmentUrl);
    std::string revisionTemplate(std::string stuToken, std::string stuHwId);

    std::string submissionPipeline(std::string tchToken, std::string hwId, std::string stuToken, std::string stuHwId, std::string attachmentUrl);
    std::string automationPipeline(std::string tchToken, std::string hwId, std::string stuToken, std::string stuId, std::string stuHwId, std::string attachmentUrl);
    std::string revisionPipeline(std::string tchToken, std::string hwId, std::string stuToken, std::string stuHwId, std::string stuId, std::string attachmentUrl);
}

namespace login
{
    std::string stuLoginPipeline(std::string username, std::string passwd);
    std::string apiRes2at(std::string inputStr);
    std::string apiRes2userId(std::string inputStr);
    std::string tchLoginPipeline(std::string username, std::string passwd);
    std::string finalout2Token(std::string inputStr);
    std::string finalout2userId(std::string inputStr);
    std::string finalout2clazzId(std::string inputStr);
}

namespace operateHw
{
    std::string prepareUpdateJson(std::string inputStr);
    std::string updateHwPipeline(std::string tchToken, std::string hwId);
    std::string showSubmitDetailPipeline(std::string tchToken, std::string hwId, std::string clazzId);
}