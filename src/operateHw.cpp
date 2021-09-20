#include "tabulate/table.hpp"
#include "jsonRewrite.hpp"

using namespace tabulate;

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

        //        Json::Value finalout;
        Table stuTable;
        Table classDiagram;
        Table classTable;
        Table questionTable;

        std::string finalStr;

        /*概覽*/
        std::string showHwSubmitDetailResult = reqData::showHwSubmitDetail(tchToken, hwId, clazzId);
        if (reader->parse(showHwSubmitDetailResult.data(), showHwSubmitDetailResult.data() + showHwSubmitDetailResult.size(), &root, &errs))
        {
            //		Table stuTable;
            //		Table classTable;
            /*
            finalout["平均時間"] = root["result"]["classOverView"]["avgCostTime"].asString();
            finalout["平均得点"] = root["result"]["classOverView"]["avgScore"].asString();
            finalout["合計点"] = root["result"]["classOverView"]["fullScore"].asString();
            finalout["提出された人数"] = root["result"]["classOverView"]["submitCount"].asString();
            finalout["提出していない人数"] = root["result"]["classOverView"]["unSubmitCount"].asString();
            finalout["訂正した人数"] = root["result"]["classOverView"]["reviseCount"].asString();
  */

            stuTable.column(0).format().multi_byte_characters(true);
            //	    Table outTable;
            stuTable.format().width(20);
            classTable.column(0).format().multi_byte_characters(true);
            classTable.format().width(20);
            classTable.add_row({"平均時間", root["result"]["classOverView"]["avgCostTime"].asString()});
            classTable.add_row({"平均得点", root["result"]["classOverView"]["avgScore"].asString()});
            classTable.add_row({"合計点", root["result"]["classOverView"]["fullScore"].asString()});
            classTable.add_row({"提出された人数", root["result"]["classOverView"]["submitCount"].asString()});
            classTable.add_row({"提出していない人数", root["result"]["classOverView"]["unSubmitCount"].asString()});
            classTable.add_row({"訂正した人数", root["result"]["classOverView"]["reviseCount"].asString()});

            stuTable.add_row({"name", "st", "sc", "obj", "sub", "rate"});
            const Json::Value listStuOverView = root["result"]["listStuOverView"];
            for (unsigned int i = 0; i < listStuOverView.size(); i++)
            {

                stuTable.add_row({listStuOverView[i]["studentName"].asString(), listStuOverView[i]["status"].asString(), listStuOverView[i]["stuTotalScore"].asString(), listStuOverView[i]["stuTotalObjScore"].asString(), listStuOverView[i]["stuTotalSubScore"].asString(), listStuOverView[i]["stuScoreRate"].asString()});
            }

            classDiagram.add_row({classTable});
            classDiagram.add_row({stuTable});
            /*		std::stringstream ss;
	std::streambuf* buffer=std::cout.rdbuf();
		std::cout.rdbuf(ss.rdbuf());
		std::cout << classDiagram;
		finalStr = ss.str();
		std::cout.rdbuf(buffer);		*/
            //	std::cout << outTable;
        }
        else
        {

            std::cout << errs << std::endl;
            return "";
        }
        /*詳細*/
        std::string listQuestionViewResult = reqData::listQuestionView(tchToken, hwId, clazzId);
        //	Table questionTable;

        if (reader->parse(listQuestionViewResult.data(), listQuestionViewResult.data() + listQuestionViewResult.size(), &root, &errs))
        {
            questionTable.add_row({"secName", "questionTitle", "平均得点", "得点率"});

            const Json::Value listQuestionView = root["result"]["listQuestionView"];
            for (unsigned int i = 0; i < listQuestionView.size(); i++)
            {
                /*
                Json::Value temp;
                temp[listQuestionView[i]["sectionName"].asString()][listQuestionView[i]["questionTitle"].asString()]["この質問の平均得点"] = listQuestionView[i]["avgScore"].asString();
                temp[listQuestionView[i]["sectionName"].asString()][listQuestionView[i]["questionTitle"].asString()]["この質問の得点率"] = listQuestionView[i]["curScoreRate"].asString();
                */

                //  std::string questionDetail = reqData::getQuestionDetail(tchToken, hwId, clazzId, listQuestionView[i]["questionId"].asString().c_str());

                //Json::Value temp2;
                //if (reader->parse(questionDetail.data(), questionDetail.data() + questionDetail.size(), &temp2, &errs))
                //{
                //                    temp[listQuestionView[i]["sectionName"].asString()][listQuestionView[i]["questionTitle"].asString()]["回答の概要"] = temp2["result"]["answerDetail"];
                questionTable.add_row({listQuestionView[i]["sectionName"].asString(), listQuestionView[i]["questionTitle"].asString(), listQuestionView[i]["avgScore"].asString(), listQuestionView[i]["curScoreRate"].asString()});
                //}
                //                else
                //              {
                //                std::cout << errs << std::endl;
                //              return "";
                //        }
                //              finalout["詳細"].append(temp);

                //classDiagram.add_row({questionTable});
            }
            classDiagram.add_row({questionTable});
        }
        else
        {
            std::cout << errs << std::endl;
            return "";
        }

        std::stringstream ss;
        std::streambuf *buffer = std::cout.rdbuf();
        std::cout.rdbuf(ss.rdbuf());
        std::cout << classDiagram;
        finalStr = ss.str();
        std::cout.rdbuf(buffer);

        return finalStr;
        std::cout << classDiagram;
        return "";
        //return analyzeJson::format(showHwSubmitDetailResult)+"\n"+analyzeJson::format(listQuestionViewResult);
        //		return rewrite::toStyledStringRewrite(finalout);
    }
}
