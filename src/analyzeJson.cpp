#include "zhixueUtilities.hpp"
#include <jsoncpp/json/json.h>

namespace analyzeJson
{

	std::string analyzeAnsJson(std::string inputJson)
	{

		std::string index;

		std::string priNum;
		std::string subNum;
		//std::string ans;
		Json::Reader reader;
		Json::Value root;

		Json::Value finalout;

		if (reader.parse(inputJson.c_str(), root))
		{
			const Json::Value sectionList = root["result"]["sectionList"];
			for (unsigned int i = 0; i < sectionList.size(); i++)
			{
				priNum = sectionList[i]["title"].asString();
				//std::cout << priNum<<std::endl;
				const Json::Value topicList = sectionList[i]["topicList"];
				for (unsigned int i = 0; i < topicList.size(); i++)
				{

					if(i < 10){
								index = "インデックスは0"+std::__cxx11::to_string(i)+"である。——";
							}else{
								index = "インデックスは"+std::__cxx11::to_string(i)+"である。——";
							}
							

					subNum = index+topicList[i]["title"].asString();
					//std::cout << subNum<<std::endl;

					const Json::Value children = topicList[i]["children"];
					for (unsigned int i = 0; i < children.size(); i++)
					{
						
						const Json::Value answers = children[i]["answers"];
						if (answers.size() == 0)
						{
							finalout["answers"][priNum]["インデックスはない。——"+subNum][i] = "null";
						}
						//std::cout << ans<<std::endl;

						else
						{
							for (unsigned int i = 0; i < answers.size(); i++)
							{
								
							

								//std::cout << ans<<std::endl;
								finalout["答え"][priNum][subNum][i] = answers[i].asString();
								//;
							}
						}
					}
				}
			}
			const Json::Value answerAttachments = root["result"]["answerAttachments"];
			for (unsigned int i = 0; i < answerAttachments.size(); i++)
			{
				finalout["答えの添付ファイル"][i] = answerAttachments[i]["path"].asString();
			}
		}
		else
		{
			printf("err");
		}

		return finalout.toStyledString();
	}

	std::string analyzeHwListJson(std::string inputJson)
	{

		Json::Reader reader;
		Json::Value root;
		Json::Value finalout;
		std::string index;

		if (reader.parse(inputJson.c_str(), root))
		{
			//std::cout << root["result"]["list"].size() << std::endl;
			const Json::Value list = root["result"]["list"];
			for (unsigned int i = 0; i < list.size(); i++)
			{
				//std::cout << i << list[i]["hwTitle"].asString()<< list[i]["hwId"].asString()<<std::endl;
				if (i < 10)
				{
					index = "インデックスは0" + std::__cxx11::to_string(i) + "である。";
				}
				else
				{
					index = "インデックスは" + std::__cxx11::to_string(i) + "である。";
				}


				finalout[index]["Title"] = list[i]["hwTitle"].asString();
				finalout[index]["Homework ID"] = list[i]["hwId"].asString();
				finalout[index]["Student Homework ID"] = list[i]["stuHwId"].asString();
			}
		}
		else
		{
			printf("err");
		}

		return finalout.toStyledString();
	}

	int analyzeIfSuccess(std::string str)
	{
		Json::Reader reader;
		Json::Value root;
		if (reader.parse(str.c_str(), root))
		{
			if (root["code"].asString() == "000000")
			{
				return 0;
			}
			else
			{
				return -1;
			}
		}
		else
		{
			return -1;
		}
	}
	std::string index2hwId(std::string inputJson, std::string index){
		Json::Reader reader;
		Json::Value root;
		index = "インデックスは" + index + "である。";
		if (reader.parse(inputJson.c_str(), root))
		{
			return root[index]["Homework ID"].asString();
		}else{
			return "";
		}
	}
	std::string index2stuHwId(std::string inputJson, std::string index){
		Json::Reader reader;
		Json::Value root;
		index = "インデックスは" + index + "である。";
		if (reader.parse(inputJson.c_str(), root))
		{
			return root[index]["Student Homework ID"].asString();
		}else{
			return "";
		}
	}
}