#include "clipp.hpp"
#include "zhixueUtilities.hpp"
#include <cstdlib>

int main(int argc, char *argv[])
{
	enum class mode
	{
		getList,
		getAns,
		redoHomework,
		submitHomework,
		automation,
		autoRevise,
		availablize,
		help
	};
	mode selected = mode::help;

	//std::string tchToken;
	//std::string stuToken;
	std::string hwId = "";
	//std::string stuId;
	std::string stuHwId = "";
	std::string listIndex = "";
	std::string stuUsername = "";
	std::string stuPasswd = "";
	std::string tchUsername = "";
	std::string tchPasswd = "";
	std::string attachmentUrl = "";

	//std::string finaloutStr;

	bool useIndex = false;
	bool completed = false;

	auto getListMode = (clipp::command("getList").set(selected, mode::getList),
						clipp::option("-stu", "--student-login") & clipp::value("stuUsername", stuUsername) % "Student's username" & clipp::value("stuPasswd", stuPasswd) % "Student's Psssword",
						clipp::option("--already-done").set(completed, true).doc("use the list of completed homeworks"));

	auto getAnsMode = (clipp::command("getAns").set(selected, mode::getAns),
					   clipp::option("-tch", "--teacher-login") & clipp::value("tchUsername", tchUsername) % "ANY Teacher's Username" & clipp::value("tchPasswd", tchPasswd) % "THE Teacher's encoded Password",
					   clipp::option("-hi", "--homework-id") & clipp::value("hwId", hwId) % "Homework ID",
					   clipp::option("-stu", "--student-login") & clipp::value("stuUsername", stuUsername) % "Student's username" & clipp::value("stuPasswd", stuPasswd) % "Student's Psssword",
					   clipp::option("--index").set(useIndex, true) & clipp::value("listIndex", listIndex) % "List Index",
					   clipp::option("--already-done").set(completed, true).doc("use the list of completed homeworks"));

	auto redoMode = (clipp::command("redo").set(selected, mode::redoHomework),
					 clipp::option("-tch", "--teacher-login") & clipp::value("tchUsername", tchUsername) % "ANY Teacher's Username" & clipp::value("tchPasswd", tchPasswd) % "THE Teacher's encoded Password",
					 clipp::option("-stu", "--student-login") & clipp::value("stuUsername", stuUsername) % "Student's username" & clipp::value("stuPasswd", stuPasswd) % "Student's Psssword",
					 clipp::option("-hi", "--homework-id") & clipp::value("hwId", hwId) % "Homework ID",
					 clipp::option("-stu", "--student-login") & clipp::value("stuUsername", stuUsername) % "Student's username" & clipp::value("stuPasswd", stuPasswd) % "Student's Psssword",
					 clipp::option("--index").set(useIndex, true) & clipp::value("listIndex", listIndex) % "List Index",
					 clipp::option("--already-done").set(completed, true).doc("use the list of completed homeworks"));

	auto submitMode = (clipp::command("autoSubmit").set(selected, mode::submitHomework),
					   clipp::option("-tch", "--teacher-login") & clipp::value("tchUsername", tchUsername) % "ANY Teacher's Username" & clipp::value("tchPasswd", tchPasswd) % "THE Teacher's encoded Password",
					   clipp::option("-stu", "--student-login") & clipp::value("stuUsername", stuUsername) % "Student's username" & clipp::value("stuPasswd", stuPasswd) % "Student's Psssword",
					   clipp::option("-hi", "--homework-ids") & clipp::value("hwId", hwId) % "Homework ID" & clipp::value("stuHwId", stuHwId) % "Student Homework ID",
					   clipp::option("--index").set(useIndex, true) & clipp::value("listIndex", listIndex) % "List Index",
					   clipp::option("--with-attachment") & clipp::value("attachmentUrl", attachmentUrl) % "Attachmenet URL, only supports pics, maybe",
					   clipp::option("--already-done").set(completed, true).doc("use the list of completed homeworks"));

	auto reviseMode = (clipp::command("autoRevise").set(selected, mode::autoRevise),
					   clipp::option("-tch", "--teacher-login") & clipp::value("tchUsername", tchUsername) % "ANY Teacher's Username" & clipp::value("tchPasswd", tchPasswd) % "THE Teacher's encoded Password",
					   clipp::option("-stu", "--student-login") & clipp::value("stuUsername", stuUsername) % "Student's username" & clipp::value("stuPasswd", stuPasswd) % "Student's Psssword",
					   clipp::option("-hi", "--homework-ids") & clipp::value("hwId", hwId) % "Homework ID" & clipp::value("stuHwId", stuHwId) % "Student Homework ID",
					   clipp::option("--index").set(useIndex, true) & clipp::value("listIndex", listIndex) % "List Index",
					   clipp::option("--with-attachment") & clipp::value("attachmentUrl", attachmentUrl) % "Attachmenet URL, only supports pics, maybe",
					   clipp::option("--already-done").set(completed, true).doc("use the list of completed homeworks"));

	auto autoMode = (clipp::command("automation").set(selected, mode::automation),
					 clipp::option("-tch", "--teacher-login") & clipp::value("tchUsername", tchUsername) % "ANY Teacher's Username" & clipp::value("tchPasswd", tchPasswd) % "THE Teacher's encoded Password",
					 clipp::option("-stu", "--student-login") & clipp::value("stuUsername", stuUsername) % "Student's username" & clipp::value("stuPasswd", stuPasswd) % "Student's Psssword",
					 clipp::option("-hi", "--homework-ids") & clipp::value("hwId", hwId) % "Homework ID" & clipp::value("stuHwId", stuHwId) % "Student Homework ID",
					 clipp::option("--index").set(useIndex, true) & clipp::value("listIndex", listIndex) % "List Index",
					 clipp::option("--with-attachment") & clipp::value("attachmentUrl", attachmentUrl) % "Attachmenet URL, only supports pics, maybe",
					 clipp::option("--already-done").set(completed, true).doc("use the list of completed homeworks"));

	auto availMode = (clipp::command("availablize").set(selected, mode::availablize),
					  clipp::option("-tch", "--teacher-login") & clipp::value("tchUsername", tchUsername) % "ANY Teacher's Username" & clipp::value("tchPasswd", tchPasswd) % "THE Teacher's encoded Password",
					  clipp::option("-stu", "--student-login") & clipp::value("stuUsername", stuUsername) % "Student's username" & clipp::value("stuPasswd", stuPasswd) % "Student's Psssword",
					  clipp::option("-hi", "--homework-id") & clipp::value("hwId", hwId) % "Homework ID",
					  clipp::option("--index").set(useIndex, true) & clipp::value("listIndex", listIndex) % "List Index",
					  clipp::option("--already-done").set(completed, true).doc("use the list of completed homeworks"));

	auto cli = ((getListMode | getAnsMode | redoMode | submitMode | reviseMode | autoMode | availMode | clipp::command("help").set(selected, mode::help)),
				clipp::option("-v", "--version").call([]
													  { std::cout << "version 1.28b" << std::endl; })
					.doc("show version"),
				clipp::option("-h", "--help").set(selected, mode::help).doc("show this help message"));

	if (parse(argc, argv, cli))
	{
		if (std::getenv("stuUsername") != nullptr)
		{
			stuUsername = std::getenv("stuUsername");
		}
		if (std::getenv("stuPasswd") != nullptr)
		{
			stuPasswd = std::getenv("stuPasswd");
		}
		if (std::getenv("tchUsername") != nullptr)
		{
			tchUsername = std::getenv("tchUsername");
		}
		if (std::getenv("tchPasswd") != nullptr)
		{
			tchPasswd = std::getenv("tchPasswd");
		}
		switch (selected)
		{
		case mode::getList:
			if (stuUsername.empty() || stuPasswd.empty())
			{
				std::cout << "ログインに必要な情報が不足しています。" << std::endl;
				break;
			}
			else
			{
				std::cout << analyzeJson::analyzeHwListJson(reqData::getHwListJson(login::finalout2Token(login::stuLoginPipeline(stuUsername, stuPasswd)), completed)) << std::endl;
			}

			break;
		case mode::getAns:
			if (tchUsername.empty() || tchPasswd.empty())
			{
				std::cout << "ログインに必要な情報が不足しています。" << std::endl;
				break;
			}
			else
			{
				if (useIndex)
				{
					if (stuUsername.empty() || stuPasswd.empty())
					{
						std::cout << "ログインに必要な情報が不足しています。" << std::endl;
						break;
					}
					else
					{
						std::string inputJson = analyzeJson::analyzeHwListJson(reqData::getHwListJson(login::finalout2Token(login::stuLoginPipeline(stuUsername, stuPasswd)), completed));
						hwId = analyzeJson::index2hwId(inputJson, listIndex);
						std::cout << analyzeJson::analyzeAnsJson(reqData::postAnsJson(login::finalout2Token(login::tchLoginPipeline(tchUsername, tchPasswd)), hwId)) << std::endl;
					}
				}
				else
				{
					if (hwId.empty())
					{
						std::cout << "クエリに必要な情報が不足しています。" << std::endl;
						break;
					}
					else
					{
						std::cout << analyzeJson::analyzeAnsJson(reqData::postAnsJson(login::finalout2Token(login::tchLoginPipeline(tchUsername, tchPasswd)), hwId)) << std::endl;
					}
				}
			}

			break;
		case mode::redoHomework:
			if (tchUsername.empty() || tchPasswd.empty() || stuUsername.empty() || stuPasswd.empty())
			{
				std::cout << "ログインに必要な情報が不足しています。" << std::endl;
				break;
			}
			else
			{
				if (useIndex)
				{
					std::string inputJson = analyzeJson::analyzeHwListJson(reqData::getHwListJson(login::finalout2Token(login::stuLoginPipeline(stuUsername, stuPasswd)), completed));
					hwId = analyzeJson::index2hwId(inputJson, listIndex);
					std::cout << reqData::redoHomework(login::finalout2Token(login::tchLoginPipeline(tchUsername, tchPasswd)), login::finalout2userId(login::stuLoginPipeline(stuUsername, stuPasswd)), hwId) << std::endl;
				}
				else
				{
					if (hwId.empty())
					{
						std::cout << "クエリに必要な情報が不足しています。" << std::endl;
						break;
					}
					else
					{
						std::cout << reqData::redoHomework(login::finalout2Token(login::tchLoginPipeline(tchUsername, tchPasswd)), login::finalout2userId(login::stuLoginPipeline(stuUsername, stuPasswd)), hwId) << std::endl;
					}
				}
			}
			break;
		case mode::submitHomework:
			if (tchUsername.empty() || tchPasswd.empty() || stuUsername.empty() || stuPasswd.empty())
			{
				std::cout << "ログインに必要な情報が不足しています。" << std::endl;
				break;
			}
			else
			{
				if (useIndex)
				{
					std::string inputJson = analyzeJson::analyzeHwListJson(reqData::getHwListJson(login::finalout2Token(login::stuLoginPipeline(stuUsername, stuPasswd)), completed));
					hwId = analyzeJson::index2hwId(inputJson, listIndex);
					stuHwId = analyzeJson::index2stuHwId(inputJson, listIndex);
					std::cout << submission::submissionPipeline(login::finalout2Token(login::tchLoginPipeline(tchUsername, tchPasswd)), hwId, login::finalout2Token(login::stuLoginPipeline(stuUsername, stuPasswd)), stuHwId, attachmentUrl) << std::endl;
				}
				else
				{
					if (hwId.empty() || stuHwId.empty())
					{
						std::cout << "クエリに必要な情報が不足しています。" << std::endl;
						break;
					}
					else
					{
						std::cout << submission::submissionPipeline(login::finalout2Token(login::tchLoginPipeline(tchUsername, tchPasswd)), hwId, login::finalout2Token(login::stuLoginPipeline(stuUsername, stuPasswd)), stuHwId, attachmentUrl) << std::endl;
					}
				}
			}
			break;
		case mode::autoRevise:
			if (tchUsername.empty() || tchPasswd.empty() || stuUsername.empty() || stuPasswd.empty())
			{
				std::cout << "ログインに必要な情報が不足しています。" << std::endl;
				break;
			}
			else
			{
				if (useIndex)
				{
					std::string inputJson = analyzeJson::analyzeHwListJson(reqData::getHwListJson(login::finalout2Token(login::stuLoginPipeline(stuUsername, stuPasswd)), completed));
					hwId = analyzeJson::index2hwId(inputJson, listIndex);
					stuHwId = analyzeJson::index2stuHwId(inputJson, listIndex);
					std::cout << submission::revisionPipeline(login::finalout2Token(login::tchLoginPipeline(tchUsername, tchPasswd)), hwId, login::finalout2Token(login::stuLoginPipeline(stuUsername, stuPasswd)), stuHwId, login::finalout2userId(login::stuLoginPipeline(stuUsername, stuPasswd)), attachmentUrl) << std::endl;
				}
				else
				{
					if (hwId.empty() || stuHwId.empty())
					{
						std::cout << "クエリに必要な情報が不足しています。" << std::endl;
						break;
					}
					else
					{
						std::cout << submission::revisionPipeline(login::finalout2Token(login::tchLoginPipeline(tchUsername, tchPasswd)), hwId, login::finalout2Token(login::stuLoginPipeline(stuUsername, stuPasswd)), stuHwId, login::finalout2userId(login::stuLoginPipeline(stuUsername, stuPasswd)), attachmentUrl) << std::endl;
					}
				}
			}

			break;
		case mode::automation:
			if (tchUsername.empty() || tchPasswd.empty() || stuUsername.empty() || stuPasswd.empty())
			{
				std::cout << "ログインに必要な情報が不足しています。" << std::endl;
				break;
			}
			else
			{
				if (useIndex)
				{
					std::string inputJson = analyzeJson::analyzeHwListJson(reqData::getHwListJson(login::finalout2Token(login::stuLoginPipeline(stuUsername, stuPasswd)), completed));
					hwId = analyzeJson::index2hwId(inputJson, listIndex);
					stuHwId = analyzeJson::index2stuHwId(inputJson, listIndex);
					std::cout << submission::automationPipeline(login::finalout2Token(login::tchLoginPipeline(tchUsername, tchPasswd)), hwId, login::finalout2Token(login::stuLoginPipeline(stuUsername, stuPasswd)), login::finalout2userId(login::stuLoginPipeline(stuUsername, stuPasswd)), stuHwId, attachmentUrl) << std::endl;
				}
				else
				{
					std::cout << submission::automationPipeline(login::finalout2Token(login::tchLoginPipeline(tchUsername, tchPasswd)), hwId, login::finalout2Token(login::stuLoginPipeline(stuUsername, stuPasswd)), login::finalout2userId(login::stuLoginPipeline(stuUsername, stuPasswd)), stuHwId, attachmentUrl) << std::endl;
				}
			}
			break;

		case mode::availablize:
			if (tchUsername.empty() || tchPasswd.empty())
			{
				std::cout << "ログインに必要な情報が不足しています。" << std::endl;
				break;
			}
			else
			{
				if (useIndex)
				{
					if (stuUsername.empty() || stuPasswd.empty())
					{
						std::cout << "ログインに必要な情報が不足しています。" << std::endl;
						break;
					}
					else
					{
						std::string inputJson = analyzeJson::analyzeHwListJson(reqData::getHwListJson(login::finalout2Token(login::stuLoginPipeline(stuUsername, stuPasswd)), completed));
						hwId = analyzeJson::index2hwId(inputJson, listIndex);
						std::cout << updateHw::updateHwPipeline(login::finalout2Token(login::tchLoginPipeline(tchUsername, tchPasswd)), hwId) << std::endl;
					}
				}
				else
				{
					if (hwId.empty() || stuHwId.empty())
					{
						std::cout << "クエリに必要な情報が不足しています。" << std::endl;
						break;
					}
					else
					{
						std::cout << updateHw::updateHwPipeline(login::finalout2Token(login::tchLoginPipeline(tchUsername, tchPasswd)), hwId) << std::endl;
					}
				}
			}
			break;
		case mode::help:
			std::cout << clipp::make_man_page(cli, "zhixueUtilities") << std::endl;
			break;
		}
	}
	else
	{
		std::cout << clipp::make_man_page(cli, "zhixueUtilities") << std::endl;
	}

	return 0;
}
