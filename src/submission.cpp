#include "zhixueUtilities.hpp"
#include <jsoncpp/json/json.h>

namespace submission
{

    std::string prepareSubmJson(std::string inputStr, std::string stuToken, std::string stuHwId)
    {

        std::string str = submissionTemplate(stuToken, stuHwId);

        std::string questionId;
        std::string childQuestionId;
        //std::string ans;
        Json::Reader reader;
        Json::Value root;
        std::string answer = "";

        Json::Value finalout;
        if (reader.parse(str.c_str(), finalout))
        {
            if (reader.parse(inputStr.c_str(), root))
            {
                const Json::Value sectionList = root["result"]["sectionList"];
                for (unsigned int i = 0; i < sectionList.size(); i++)
                {

                    const Json::Value topicList = sectionList[i]["topicList"];
                    for (unsigned int i = 0; i < topicList.size(); i++)
                    {

                        questionId = topicList[i]["questionId"].asString();

                        const Json::Value children = topicList[i]["children"];
                        for (unsigned int i = 0; i < children.size(); i++)
                        {
                            childQuestionId = children[i]["childQuestionId"].asString();

                            const Json::Value answers = children[i]["answers"];
                            if (answers.size() == 0)
                            {

                                Json::Value temp;
                                std::string tempe = "{\"answer\":\"\",\"attachments\":[],\"childQuestionId\":\"" + childQuestionId + "\",\"duration\":0,\"feedback\":0,\"questionId\":\"" + questionId + "\"}";
                                if (reader.parse(tempe.c_str(), temp))
                                {
                                    finalout["params"]["questions"].append(temp);
                                }
                            }

                            else
                            {
                                for (unsigned int i = 0; i < answers.size(); i++)
                                {
                                    if (i == 0)
                                    {
                                        answer = answers[i].asString();
                                    }
                                    else
                                    {
                                        answer += "または";
                                        answer += answers[i].asString();
                                    }
                                    /*Json::Value temp;
                                    std::string tempe = "{\"answer\":\"" + answer + "\",\"attachments\":[],\"childQuestionId\":\"" + childQuestionId + "\",\"duration\":0,\"feedback\":0,\"questionId\":\"" + questionId + "\"}";
                                    if (reader.parse(tempe.c_str(), temp))
                                    {
                                        finalout["params"]["questions"].append(Json::Value(temp));
                                    }*/
                                }

                                Json::Value temp;
                                std::string tempe = "{\"answer\":\"" + answer + "\",\"attachments\":[],\"childQuestionId\":\"" + childQuestionId + "\",\"duration\":0,\"feedback\":0,\"questionId\":\"" + questionId + "\"}";
                                if (reader.parse(tempe.c_str(), temp))
                                {
                                    finalout["params"]["questions"].append(Json::Value(temp));
                                }
                            }
                        }
                    }
                }
            }
            else
            {
                printf("\nerr\n");
            }
        }

        return finalout.toStyledString();
    }

    std::string submissionTemplate(std::string stuToken, std::string stuHwId)
    {

        std::string finalout = "{\"base\":{\"Authorization\":\"" + stuToken + "\",\"appId\":\"OAXI57PG\",\"appVersion\":\"2.0.1542\",\"packageName\":\"com.iflytek.elpmobile.student\",\"sysType\":\"Android\",\"sysVersion\":\"Nashi\",\"udid\":\"0\",\"userId\":\"0\",\"utag\":\"\"},\"params\":{\"duration\":0,\"questions\":[],\"stuHwId\":\"" + stuHwId + "\",\"submitType\":\"SUBMIT\"}}";
        return finalout;
    }

    std::string submissionPipeline(std::string tchToken, std::string hwId, std::string stuToken, std::string stuHwId)
    {
        return reqData::sendSubbmission(submission::prepareSubmJson(reqData::postAnsJson(tchToken, hwId), stuToken, stuHwId), stuToken);
    }

    std::string automationPipeline(std::string tchToken, std::string hwId, std::string stuToken, std::string stuId, std::string stuHwId)
    {
        std::string rtn = "Submissing\n" + reqData::sendSubbmission(submission::prepareSubmJson(reqData::postAnsJson(tchToken, hwId), stuToken, stuHwId), stuToken);
        //std::string rtn = submission::prepareSubmJson(reqData::postAnsJson(tchToken, hwId), stuToken, stuHwId);
        rtn += "\nRejecting\n";
        rtn += reqData::redoHomework(tchToken, stuId, hwId);
        return rtn;
    }

    std::string revisionTemplate(std::string stuToken, std::string stuHwId)
    {

        std::string finalout = "{\"base\":{\"Authorization\":\"" + stuToken + "\",\"appId\":\"OAXI57PG\",\"appVersion\":\"2.0.1542\",\"packageName\":\"com.iflytek.elpmobile.student\",\"sysType\":\"Android\",\"sysVersion\":\"Nashi\",\"udid\":\"0\",\"userId\":\"0\",\"utag\":\"\"},\"params\":{\"duration\":0,\"questions\":[],\"stuHwId\":\"" + stuHwId + "\",\"submitType\":\"REVISE\"}}";
        return finalout;
    }

    std::string prepareReviJson(std::string inputStr, std::string stuToken, std::string stuHwId, std::string stuId, std::string hwId)
    {

        std::string str = revisionTemplate(stuToken, stuHwId);

        std::string questionId;
        std::string childQuestionId;
        //std::string ans;
        Json::Reader reader;
        Json::Value root;
        Json::Value reviseQuest;

        Json::Value finalout;
        if (reader.parse(str.c_str(), finalout))
        {
            if (reader.parse(inputStr.c_str(), root))
            {
                const Json::Value sectionList = root["result"]["sectionList"];
                for (unsigned int i = 0; i < sectionList.size(); i++)
                {

                    const Json::Value topicList = sectionList[i]["topicList"];
                    for (unsigned int i = 0; i < topicList.size(); i++)
                    {

                        questionId = topicList[i]["questionId"].asString();
                        if (reader.parse(reqData::getReviseQuestion(stuId, hwId, stuToken).c_str(), reviseQuest))
                        {
                            //std::cout << reqData::getReviseQuestion(stuId, hwId,stuToken);
                            for (unsigned int j = 0; j < reviseQuest["result"]["questions"].size(); j++)
                            {

                                if (reviseQuest["result"]["questions"][j]["questionId"] == questionId)
                                {
                                    const Json::Value children = topicList[i]["children"];
                                    for (unsigned int i = 0; i < children.size(); i++)
                                    {
                                        childQuestionId = children[i]["childQuestionId"].asString();

                                        for (unsigned int k = 0; k < reviseQuest["result"]["questions"][j]["childQuestions"].size(); k++)
                                            if (reviseQuest["result"]["questions"][j]["childQuestions"][k]["childQuestionId"] == childQuestionId)
                                            {
                                                const Json::Value answers = children[i]["answers"];
                                                if (answers.size() == 0)
                                                {

                                                    Json::Value temp;
                                                    std::string tempe = "{\"answer\":\"\",\"attachments\":[],\"childQuestionId\":\"" + childQuestionId + "\",\"duration\":0,\"feedback\":0,\"questionId\":\"" + questionId + "\"}";
                                                    if (reader.parse(tempe.c_str(), temp))
                                                    {
                                                        finalout["params"]["questions"].append(temp);
                                                    }
                                                }

                                                else
                                                {
                                                    for (unsigned int i = 0; i < answers.size(); i++)
                                                    {

                                                        Json::Value temp;
                                                        std::string tempe = "{\"answer\":\"" + answers[i].asString() + "\",\"attachments\":[],\"childQuestionId\":\"" + childQuestionId + "\",\"duration\":0,\"feedback\":0,\"questionId\":\"" + questionId + "\"}";
                                                        if (reader.parse(tempe.c_str(), temp))
                                                        {
                                                            finalout["params"]["questions"].append(Json::Value(temp));
                                                        }
                                                    }
                                                }
                                            }
                                    }
                                }
                            }
                        }
                    }
                }
            }
            else
            {
                printf("\nerr\n");
            }
        }

        return finalout.toStyledString();
    }
    std::string revisionPipeline(std::string tchToken, std::string hwId, std::string stuToken, std::string stuHwId, std::string stuId)
    {
        return reqData::sendSubbmission(submission::prepareReviJson(reqData::postAnsJson(tchToken, hwId), stuToken, stuHwId, stuId, hwId), stuToken);
    }
}