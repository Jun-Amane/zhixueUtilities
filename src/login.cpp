#include "zhixueUtilities.hpp"
#include <jsoncpp/json/json.h>

namespace login
{
    std::string apiRes2userId(std::string inputStr)
    {

        Json::CharReaderBuilder readerBuilder;
        Json::Value def;
        Json::CharReaderBuilder::setDefaults(&def);
        def["emitUTF8"] = true;
        readerBuilder.settings_ = def;
        JSONCPP_STRING errs;
		JSONCPP_STRING errs;
		std::unique_ptr<Json::CharReader> reader(readerBuilder.newCharReader());
        Json::Value root;

        std::string userId = "";

        if (reader->parse(inputStr.data(), inputStr.data() + inputStr.size(), &root, &errs))
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
            std::cout << errs << std::endl;
            return inputStr;
        }
    }

    std::string apiRes2at(std::string inputStr)
    {

        Json::CharReaderBuilder readerBuilder;
        Json::Value def;
        Json::CharReaderBuilder::setDefaults(&def);
        def["emitUTF8"] = true;
        readerBuilder.settings_ = def;
        JSONCPP_STRING errs;
		JSONCPP_STRING errs;
		std::unique_ptr<Json::CharReader> reader(readerBuilder.newCharReader());
        Json::Value root;

        std::string at = "";

        if (reader->parse(inputStr.data(), inputStr.data() + inputStr.size(), &root, &errs))
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
            std::cout << errs << std::endl;
            return inputStr;
        }
    }

    std::string stuLoginPipeline(std::string username, std::string passwd)
    {

        Json::CharReaderBuilder readerBuilder;
        Json::Value def;
        Json::CharReaderBuilder::setDefaults(&def);
        def["emitUTF8"] = true;
        readerBuilder.settings_ = def;
        JSONCPP_STRING errs;
		JSONCPP_STRING errs;
		std::unique_ptr<Json::CharReader> reader(readerBuilder.newCharReader());
        Json::Value root;

        Json::Value finalout;

        std::string userId = login::apiRes2userId(reqData::loginApi(username, passwd, "zhixue_student", "5nSML4Imp8JYefnV3EIfXcOgx4JpPQ7M"));
        std::string at = login::apiRes2at(reqData::loginApi(username, passwd, "zhixue_student", "5nSML4Imp8JYefnV3EIfXcOgx4JpPQ7M"));

        // std::cout << userId << std::endl << at <<std::endl;

        if (userId != "" && at != "")
        {
            std::string resultStr = reqData::casLogin(userId, at);
            //std::cout << resultStr << std::endl;
            if (reader->parse(resultStr.data(), resultStr.data() + resultStr.size(), &root, &errs))
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
                std::cout << errs << std::endl;
            }
        }
        else
        {
            printf("\nerr:非零项目为零\n");
        }
        return finalout.toStyledString();
    }

    std::string tchLoginPipeline(std::string username, std::string passwd)
    {

        Json::CharReaderBuilder readerBuilder;
        Json::Value def;
        Json::CharReaderBuilder::setDefaults(&def);
        def["emitUTF8"] = true;
        readerBuilder.settings_ = def;
        JSONCPP_STRING errs;
		JSONCPP_STRING errs;
		std::unique_ptr<Json::CharReader> reader(readerBuilder.newCharReader());
        Json::Value root;

        Json::Value finalout;

        std::string userId = login::apiRes2userId(reqData::loginApi(username, passwd, "zhixue_teacher", "E3KzZvjVkC8kQXWBlR5521GztpApNn99"));
        std::string at = login::apiRes2at(reqData::loginApi(username, passwd, "zhixue_teacher", "E3KzZvjVkC8kQXWBlR5521GztpApNn99"));

        // std::cout << userId << std::endl << at <<std::endl;

        if (userId != "" && at != "")
        {
            std::string resultStr = reqData::uniteLogin(userId, at);
            //std::cout << resultStr << std::endl;
            if (reader->parse(resultStr.data(), resultStr.data() + resultStr.size(), &root, &errs))
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
                std::cout << errs << std::endl;
                return "";
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
        Json::CharReaderBuilder readerBuilder;
        Json::Value def;
        Json::CharReaderBuilder::setDefaults(&def);
        def["emitUTF8"] = true;
        readerBuilder.settings_ = def;
        JSONCPP_STRING errs;
		JSONCPP_STRING errs;
		std::unique_ptr<Json::CharReader> reader(readerBuilder.newCharReader());
        Json::Value root;

        if (reader->parse(inputStr.data(), inputStr.data() + inputStr.size(), &root, &errs))
        {
            return root["token"].asString();
        }
        else
        {
            std::cout << errs << std::endl;
            return "";
        }
    }

    std::string finalout2userId(std::string inputStr)
    {
        Json::CharReaderBuilder readerBuilder;
        Json::Value def;
        Json::CharReaderBuilder::setDefaults(&def);
        def["emitUTF8"] = true;
        readerBuilder.settings_ = def;
        JSONCPP_STRING errs;
		JSONCPP_STRING errs;
		std::unique_ptr<Json::CharReader> reader(readerBuilder.newCharReader());
        Json::Value root;

        if (reader->parse(inputStr.data(), inputStr.data() + inputStr.size(), &root, &errs))
        {
            return root["userId"].asString();
        }
        else
        {
            std::cout << errs << std::endl;
            return "";
        }
    }
    std::string finalout2clazzId(std::string inputStr)
    {
        Json::CharReaderBuilder readerBuilder;
        Json::Value def;
        Json::CharReaderBuilder::setDefaults(&def);
        def["emitUTF8"] = true;
        readerBuilder.settings_ = def;
        JSONCPP_STRING errs;
		JSONCPP_STRING errs;
		std::unique_ptr<Json::CharReader> reader(readerBuilder.newCharReader());
        Json::Value root;

        if (reader->parse(inputStr.data(), inputStr.data() + inputStr.size(), &root, &errs))
        {
            return root["clazzId"].asString();
        }
        else
        {
            std::cout << errs << std::endl;
            return "";
        }
    }
}
