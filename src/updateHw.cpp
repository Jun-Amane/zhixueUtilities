#include "zhixueUtilities.hpp"
#include <jsoncpp/json/json.h>

namespace updateHw
{
    std::string prepareUpdateJson(std::string inputStr)
    {
        Json::Reader reader;
        Json::Value root;

        std::string updateJsonTemplate = "{\"base\":{\"appId\":\"OAXI57PG\",\"appVersion\":\"1.17.1877\",\"packageName\":\"com.iflytek.elpmobile.marktool\",\"sysType\":\"Android\",\"sysVersion\":\"\",\"udid\":\"00:00:00:00:00:00\"},\"params\":{}}";

        Json::Value finalout;

        if (reader.parse(inputStr.c_str(), root))
        {
            if (reader.parse(updateJsonTemplate.c_str(), finalout))
            {

                finalout["params"]["beginTime"] = root["result"]["beginTime"].asUInt64();
                finalout["params"]["description"] = root["result"]["description"].asString();
                finalout["params"]["endTime"] = root["result"]["endTime"].asUInt64();
                finalout["params"]["homeworkId"] = root["result"]["id"].asString();
                finalout["params"]["homeworkType"] = root["result"]["hwType"].asInt();
                finalout["params"]["isAllowMakeup"] = true;
                finalout["params"]["isUploadProcess"] = root["result"]["isUploadProcess"].asBool();
                finalout["params"]["phaseCode"] = root["result"]["phaseCode"].asString();
                if (root["result"]["publishAnswerTime"].isInt64())
                {
                    finalout["params"]["publishAnswerTime"] = root["result"]["publishAnswerTime"].asUInt64();
                }
                else
                {
                    finalout["params"]["publishAnswerTime"] = 0;
                }
                finalout["params"]["publishAnswerType"] = root["result"]["publishAnswerType"].asInt();
                finalout["params"]["publisherName"] = root["result"]["userName"].asString();
                finalout["params"]["reviseType"] = root["result"]["reviseType"].asInt();
                finalout["params"]["subjectCode"] = root["result"]["subjectCode"].asString();
                finalout["params"]["title"] = root["result"]["title"].asString();
            }
        }

        return finalout.toStyledString();
    }

    std::string updateHwPipeline(std::string tchToken, std::string hwId)
    {
        return reqData::updateHw(tchToken, updateHw::prepareUpdateJson(reqData::getHwDetail(tchToken, hwId)));
    }
}
