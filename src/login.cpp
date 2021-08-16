#include "zhixueUtilities.hpp"
#include <jsoncpp/json/json.h>

namespace login
{
    std::string apiRes2userId(std::string inputStr)
    {

        Json::Reader reader;
        Json::Value root;

        std::string userId = "";

        if (reader.parse(inputStr.c_str(), root))
        {
            if (root["code"] == "success")
            {
                userId = root["data"]["userId"].asString();
                return userId;
            }
            else
            {
                return inputStr;
            }
        }
        else
        {
            printf("\nerr\n");
            return inputStr;
        }
    }

    std::string apiRes2at(std::string inputStr)
    {

        Json::Reader reader;
        Json::Value root;

        std::string at = "";

        if (reader.parse(inputStr.c_str(), root))
        {
            if (root["code"] == "success")
            {
                at = root["data"]["at"].asString();
                return at;
            }
            else
            {
                return inputStr;
            }
        }
        else
        {
            printf("\nerr\n");
            return inputStr;
        }
    }

    std::string stuLoginPipeline(std::string username, std::string passwd)
    {

        Json::Reader reader;
        Json::Value root;

        Json::Value finalout;

        std::string userId = login::apiRes2userId(reqData::loginApi(username, passwd, "zhixue_student", "5nSML4Imp8JYefnV3EIfXcOgx4JpPQ7M"));
        std::string at = login::apiRes2at(reqData::loginApi(username, passwd, "zhixue_student", "5nSML4Imp8JYefnV3EIfXcOgx4JpPQ7M"));

        // std::cout << userId << std::endl << at <<std::endl;

        if (userId != "" && at != "")
        {
            std::string resultStr = reqData::casLogin(userId, at);
            //std::cout << resultStr << std::endl;
            if (reader.parse(resultStr.c_str(), root))
            {
                if (root["errorInfo"].asString() == "操作成功")
                {

                    finalout["name"] = root["result"]["userInfo"]["name"].asString();
                    finalout["userId"] = root["result"]["userInfo"]["id"].asString();
                    finalout["token"] = root["result"]["token"].asString();
                    finalout["clazzId"] = root["result"]["clazzInfo"]["id"].asString();
                }
                else
                {
                    finalout = root;
                }
            }
            else
            {
                printf("\nerr1\n");
            }
        }
        else
        {
            printf("\nerr2\n");
        }
        return finalout.toStyledString();
    }

    std::string tchLoginPipeline(std::string username, std::string passwd)
    {

        Json::Reader reader;
        Json::Value root;

        Json::Value finalout;

        std::string userId = login::apiRes2userId(reqData::loginApi(username, passwd, "zhixue_teacher", "E3KzZvjVkC8kQXWBlR5521GztpApNn99"));
        std::string at = login::apiRes2at(reqData::loginApi(username, passwd, "zhixue_teacher", "E3KzZvjVkC8kQXWBlR5521GztpApNn99"));

        // std::cout << userId << std::endl << at <<std::endl;

        if (userId != "" && at != "")
        {
            std::string resultStr = reqData::uniteLogin(userId, at);
            //std::cout << resultStr << std::endl;
            if (reader.parse(resultStr.c_str(), root))
            {
                if (root["errorInfo"].asString() == "操作成功")
                {

                    finalout["name"] = root["result"]["user"]["userInfo"]["name"].asString();
                    finalout["userId"] = root["result"]["user"]["userInfo"]["id"].asString();
                    finalout["token"] = root["result"]["user"]["token"].asString();
                }
                else
                {
                    finalout = root;
                }
            }
            else
            {
                printf("\nerr\n");
            }
        }
        else
        {
            printf("\nerr\n");
        }
        return finalout.toStyledString();
    }

    std::string finalout2Token(std::string inputStr)
    {
        Json::Reader reader;
        Json::Value root;

        if (reader.parse(inputStr.c_str(), root))
        {
            return root["token"].asString();
        }
        else
        {
            return "";
        }
    }

    std::string finalout2userId(std::string inputStr)
    {
        Json::Reader reader;
        Json::Value root;

        if (reader.parse(inputStr.c_str(), root))
        {
            return root["userId"].asString();
        }
        else
        {
            return "";
        }
    }
    std::string finalout2clazzId(std::string inputStr)
    {
        Json::Reader reader;
        Json::Value root;

        if (reader.parse(inputStr.c_str(), root))
        {
            return root["clazzId"].asString();
        }
        else
        {
            return "";
        }
    }
}
