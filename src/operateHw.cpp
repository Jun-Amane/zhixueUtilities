#include "zhixueUtilities.hpp"
#include <jsoncpp/json/json.h>

namespace operateHw
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
        return reqData::updateHw(tchToken, operateHw::prepareUpdateJson(reqData::getHwDetail(tchToken, hwId)));
    }

    std::string showSubmitDetailPipeline(std::string tchToken, std::string hwId, std::string clazzId)
    {

        Json::Reader reader;
        Json::Value root;

        Json::Value finalout;
        /*概覽*/
        if (reader.parse(reqData::showHwSubmitDetail(tchToken, hwId, clazzId).c_str(), root))
        {

            finalout["平均時間"] = root["result"]["classOverView"]["avgCostTime"].asString();
            finalout["平均得点"] = root["result"]["classOverView"]["avgScore"].asString();
            finalout["合計点"] = root["result"]["classOverView"]["fullScore"].asString();
            finalout["提出された人数"] = root["result"]["classOverView"]["submitCount"].asString();
            finalout["提出していない人数"] = root["result"]["classOverView"]["unSubmitCount"].asString();
            finalout["訂正した人数"] = root["result"]["classOverView"]["reviseCount"].asString();
        }
        else
        {
            return "";
        }
        /*詳細*/
        if (reader.parse(reqData::listQuestionView(tchToken, hwId, clazzId).c_str(), root))
        {

            const Json::Value listQuestionView = root["result"]["listQuestionView"];
            for (unsigned int i = 0; i < listQuestionView.size(); i++)
            {
                Json::Value temp;
                temp[listQuestionView[i]["sectionName"].asString()][listQuestionView[i]["questionTitle"].asString()]["この質問の平均得点"] = listQuestionView[i]["avgScore"].asString();
                temp[listQuestionView[i]["sectionName"].asString()][listQuestionView[i]["questionTitle"].asString()]["この質問の得点率"] = listQuestionView[i]["curScoreRate"].asString();
                std::string questionDetail = reqData::getQuestionDetail(tchToken, hwId, clazzId, listQuestionView[i]["questionId"].asString().c_str());


                Json::Value temp2;
                if(reader.parse(questionDetail.c_str(),temp2)){
                    temp[listQuestionView[i]["sectionName"].asString()][listQuestionView[i]["questionTitle"].asString()]["回答の概要"] = temp2["result"]["answerDetail"];
                }
                finalout["詳細"].append(temp);
            }
        }
        else
        {
            return "";
        }
        return finalout.toStyledString();
    }
}
