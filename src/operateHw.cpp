#include "jsonRewrite.hpp"

namespace operateHw
{
    std::string prepareUpdateJson(std::string inputStr)
    {
        Json::CharReaderBuilder readerBuilder;
        JSONCPP_STRING errs;
        std::unique_ptr<Json::CharReader> reader(readerBuilder.newCharReader());
        Json::Value root;

        std::string updateJsonTemplate = "{\"base\":{\"appId\":\"OAXI57PG\",\"appVersion\":\"1.17.1877\",\"packageName\":\"com.iflytek.elpmobile.marktool\",\"sysType\":\"Android\",\"sysVersion\":\"\",\"udid\":\"00:00:00:00:00:00\"},\"params\":{}}";

        Json::Value finalout;

        if (reader->parse(inputStr.data(), inputStr.data() + inputStr.size(), &root, &errs))
        {
            if (reader->parse(updateJsonTemplate.data(), updateJsonTemplate.data() + updateJsonTemplate.size(), &finalout, &errs))
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
            else
            {
                std::cout << errs << std::endl;
                return "";
            }
        }
        else
        {
            std::cout << errs << std::endl;
            return "";
        }

        return rewrite::toStyledStringRewrite(finalout);
    }

    std::string updateHwPipeline(std::string tchToken, std::string hwId)
    {
        return reqData::updateHw(tchToken, operateHw::prepareUpdateJson(reqData::getHwDetail(tchToken, hwId)));
    }

    std::string showSubmitDetailPipeline(std::string tchToken, std::string hwId, std::string clazzId)
    {

        Json::CharReaderBuilder readerBuilder;
        JSONCPP_STRING errs;
        std::unique_ptr<Json::CharReader> reader(readerBuilder.newCharReader());
        Json::Value root;

        Json::Value finalout;
        /*概覽*/
        std::string showHwSubmitDetailResult = reqData::showHwSubmitDetail(tchToken, hwId, clazzId);
        if (reader->parse(showHwSubmitDetailResult.data(), showHwSubmitDetailResult.data() + showHwSubmitDetailResult.size(), &root, &errs))
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
            
            std::cout << errs << std::endl;
            return "";
        }
        /*詳細*/
        std::string listQuestionViewResult = reqData::listQuestionView(tchToken, hwId, clazzId);
        if (reader->parse(listQuestionViewResult.data(), listQuestionViewResult.data() + listQuestionViewResult.size(), &root, &errs))
        {

            const Json::Value listQuestionView = root["result"]["listQuestionView"];
            for (unsigned int i = 0; i < listQuestionView.size(); i++)
            {
                Json::Value temp;
                temp[listQuestionView[i]["sectionName"].asString()][listQuestionView[i]["questionTitle"].asString()]["この質問の平均得点"] = listQuestionView[i]["avgScore"].asString();
                temp[listQuestionView[i]["sectionName"].asString()][listQuestionView[i]["questionTitle"].asString()]["この質問の得点率"] = listQuestionView[i]["curScoreRate"].asString();
                std::string questionDetail = reqData::getQuestionDetail(tchToken, hwId, clazzId, listQuestionView[i]["questionId"].asString().c_str());

                Json::Value temp2;
                if (reader->parse(questionDetail.data(), questionDetail.data() + questionDetail.size(), &temp2, &errs))
                {
                    temp[listQuestionView[i]["sectionName"].asString()][listQuestionView[i]["questionTitle"].asString()]["回答の概要"] = temp2["result"]["answerDetail"];
                }
                else
                {
                    std::cout << errs << std::endl;
                    return "";
                }
                finalout["詳細"].append(temp);
            }
        }
        else
        {
            std::cout << errs << std::endl;
            return "";
        }
        return rewrite::toStyledStringRewrite(finalout);
    }
}
