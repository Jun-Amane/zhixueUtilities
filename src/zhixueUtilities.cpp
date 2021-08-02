#include "clipp.hpp"
#include "zhixueUtilities.hpp"

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
		help
	};
	mode selected = mode::help;

	//std::string tchToken;
	//std::string stuToken;
	std::string hwId;
	//std::string stuId;
	std::string stuHwId;
	std::string listIndex;
	std::string stuUsername;
	std::string stuPasswd;
	std::string tchUsername;
	std::string tchPasswd;
	//std::string finaloutStr;

	bool useIndex = false;
	bool completed = false;

	auto getListMode = (clipp::command("getList").set(selected, mode::getList),
						clipp::required("-stu", "--student-login") & clipp::value("stuUsername", stuUsername) % "Student's username" & clipp::value("stuPasswd", stuPasswd) % "Student's Psssword",
						clipp::option("--already-done").set(completed, true).doc("use the list of completed homeworks"));

	auto getAnsMode = (clipp::command("getAns").set(selected, mode::getAns),
					   clipp::required("-tch", "--teacher-login") & clipp::value("tchUsername", tchUsername) % "ANY Teacher's Username" & clipp::value("tchPasswd", tchPasswd) % "THE Teacher's encoded Password",
					   (clipp::required("-hi", "--homework-id") & clipp::value("hwId", hwId) % "Homework ID") | clipp::required("-stu", "--student-login") & clipp::value("stuUsername", stuUsername) % "Student's username" & clipp::value("stuPasswd", stuPasswd) % "Student's Psssword" & (clipp::required("-i", "--index").set(useIndex, true) & clipp::value("listIndex", listIndex) % "List Index"),
					   clipp::option("--already-done").set(completed, true).doc("use the list of completed homeworks"));

	auto redoMode = (clipp::command("redoHomework").set(selected, mode::redoHomework),
					 clipp::required("-tch", "--teacher-login") & clipp::value("tchUsername", tchUsername) % "ANY Teacher's Username" & clipp::value("tchPasswd", tchPasswd) % "THE Teacher's encoded Password",
					 clipp::required("-stu", "--student-login") & clipp::value("stuUsername", stuUsername) % "Student's username" & clipp::value("stuPasswd", stuPasswd) % "Student's Psssword",
					 (clipp::required("-hi", "--homework-id") & clipp::value("hwId", hwId) % "Homework ID") | clipp::required("-stu", "--student-login") & clipp::value("stuUsername", stuUsername) % "Student's username" & clipp::value("stuPasswd", stuPasswd) % "Student's Psssword" & (clipp::required("-i", "--index").set(useIndex, true) & clipp::value("listIndex", listIndex) % "List Index"),
					 clipp::option("--already-done").set(completed, true).doc("use the list of completed homeworks"));

	auto submitMode = (clipp::command("submitHomework").set(selected, mode::submitHomework),
					   clipp::required("-tch", "--teacher-login") & clipp::value("tchUsername", tchUsername) % "ANY Teacher's Username" & clipp::value("tchPasswd", tchPasswd) % "THE Teacher's encoded Password",
					   clipp::required("-stu", "--student-login") & clipp::value("stuUsername", stuUsername) % "Student's username" & clipp::value("stuPasswd", stuPasswd) % "Student's Psssword",
					   (clipp::required("-hi", "--homework-ids") & clipp::value("hwId", hwId) % "Homework ID" & clipp::value("stuHwId", stuHwId) % "Student Homework ID") | (clipp::required("-i", "--index").set(useIndex, true) & clipp::value("listIndex", listIndex) % "List Index"),
					   clipp::option("--already-done").set(completed, true).doc("use the list of completed homeworks"));

	auto reviseMode = (clipp::command("autoRevise").set(selected, mode::autoRevise),
					   clipp::required("-tch", "--teacher-login") & clipp::value("tchUsername", tchUsername) % "ANY Teacher's Username" & clipp::value("tchPasswd", tchPasswd) % "THE Teacher's encoded Password",
					   clipp::required("-stu", "--student-login") & clipp::value("stuUsername", stuUsername) % "Student's username" & clipp::value("stuPasswd", stuPasswd) % "Student's Psssword",
					   (clipp::required("-hi", "--homework-ids") & clipp::value("hwId", hwId) % "Homework ID" & clipp::value("stuHwId", stuHwId) % "Student Homework ID") | (clipp::required("-i", "--index").set(useIndex, true) & clipp::value("listIndex", listIndex) % "List Index"),
					   clipp::option("--already-done").set(completed, true).doc("use the list of completed homeworks"));

	auto autoMode = (clipp::command("automation").set(selected, mode::automation),
					 clipp::required("-tch", "--teacher-login") & clipp::value("tchUsername", tchUsername) % "ANY Teacher's Username" & clipp::value("tchPasswd", tchPasswd) % "THE Teacher's encoded Password",
					 clipp::required("-stu", "--student-login") & clipp::value("stuUsername", stuUsername) % "Student's username" & clipp::value("stuPasswd", stuPasswd) % "Student's Psssword",
					 (clipp::required("-hi", "--homework-ids") & clipp::value("hwId", hwId) % "Homework ID" & clipp::value("stuHwId", stuHwId) % "Student Homework ID") | (clipp::required("-i", "--index").set(useIndex, true) & clipp::value("listIndex", listIndex) % "List Index"),
					 clipp::option("--already-done").set(completed, true).doc("use the list of completed homeworks"));

	auto cli = ((getListMode | getAnsMode | redoMode | submitMode | reviseMode | autoMode | clipp::command("help").set(selected, mode::help)),
				clipp::option("-v", "--version").call([]
													  { std::cout << "version 6.4final" << std::endl; })
					.doc("show version"),
				clipp::option("-h", "--help").set(selected, mode::help).doc("show this help message"));

	if (parse(argc, argv, cli))
	{
		switch (selected)
		{
		case mode::getList:
			std::cout << analyzeJson::analyzeHwListJson(reqData::getHwListJson(login::finalout2Token(login::stuLoginPipeline(stuUsername, stuPasswd)), completed)) << std::endl;
			break;
		case mode::getAns:
			if (useIndex)
			{
				std::string inputJson = analyzeJson::analyzeHwListJson(reqData::getHwListJson(login::finalout2Token(login::stuLoginPipeline(stuUsername, stuPasswd)), completed));
				hwId = analyzeJson::index2hwId(inputJson, listIndex);
				std::cout << analyzeJson::analyzeAnsJson(reqData::postAnsJson(login::finalout2Token(login::tchLoginPipeline(tchUsername, tchPasswd)), hwId)) << std::endl;
			}
			else
			{
				std::cout << analyzeJson::analyzeAnsJson(reqData::postAnsJson(login::finalout2Token(login::tchLoginPipeline(tchUsername, tchPasswd)), hwId)) << std::endl;
			}

			break;
		case mode::redoHomework:
			if (useIndex)
			{
				std::string inputJson = analyzeJson::analyzeHwListJson(reqData::getHwListJson(login::finalout2Token(login::stuLoginPipeline(stuUsername, stuPasswd)), completed));
				hwId = analyzeJson::index2hwId(inputJson, listIndex);
				std::cout << reqData::redoHomework(login::finalout2Token(login::tchLoginPipeline(tchUsername, tchPasswd)), login::finalout2userId(login::stuLoginPipeline(stuUsername, stuPasswd)), hwId) << std::endl;
			}
			else
			{
				std::cout << reqData::redoHomework(login::finalout2Token(login::tchLoginPipeline(tchUsername, tchPasswd)), login::finalout2userId(login::stuLoginPipeline(stuUsername, stuPasswd)), hwId) << std::endl;
			}

			break;
		case mode::submitHomework:
			if (useIndex)
			{
				std::string inputJson = analyzeJson::analyzeHwListJson(reqData::getHwListJson(login::finalout2Token(login::stuLoginPipeline(stuUsername, stuPasswd)), completed));
				hwId = analyzeJson::index2hwId(inputJson, listIndex);
				stuHwId = analyzeJson::index2stuHwId(inputJson, listIndex);
				std::cout << submission::submissionPipeline(login::finalout2Token(login::tchLoginPipeline(tchUsername, tchPasswd)), hwId, login::finalout2Token(login::stuLoginPipeline(stuUsername, stuPasswd)), stuHwId) << std::endl;
			}
			else
			{
				std::cout << submission::submissionPipeline(login::finalout2Token(login::tchLoginPipeline(tchUsername, tchPasswd)), hwId, login::finalout2Token(login::stuLoginPipeline(stuUsername, stuPasswd)), stuHwId) << std::endl;
			}

			break;
		case mode::autoRevise:
			if (useIndex)
			{
				std::string inputJson = analyzeJson::analyzeHwListJson(reqData::getHwListJson(login::finalout2Token(login::stuLoginPipeline(stuUsername, stuPasswd)), completed));
				hwId = analyzeJson::index2hwId(inputJson, listIndex);
				stuHwId = analyzeJson::index2stuHwId(inputJson, listIndex);
				std::cout << submission::revisionPipeline(login::finalout2Token(login::tchLoginPipeline(tchUsername, tchPasswd)), hwId, login::finalout2Token(login::stuLoginPipeline(stuUsername, stuPasswd)), stuHwId, login::finalout2userId(login::stuLoginPipeline(stuUsername, stuPasswd))) << std::endl;
			}
			else
			{
				std::cout << submission::revisionPipeline(login::finalout2Token(login::tchLoginPipeline(tchUsername, tchPasswd)), hwId, login::finalout2Token(login::stuLoginPipeline(stuUsername, stuPasswd)), stuHwId, login::finalout2userId(login::stuLoginPipeline(stuUsername, stuPasswd))) << std::endl;
			}

			break;
		case mode::automation:
			if (useIndex)
			{
				std::string inputJson = analyzeJson::analyzeHwListJson(reqData::getHwListJson(login::finalout2Token(login::stuLoginPipeline(stuUsername, stuPasswd)), completed));
				hwId = analyzeJson::index2hwId(inputJson, listIndex);
				stuHwId = analyzeJson::index2stuHwId(inputJson, listIndex);
				std::cout << submission::automationPipeline(login::finalout2Token(login::tchLoginPipeline(tchUsername, tchPasswd)), hwId, login::finalout2Token(login::stuLoginPipeline(stuUsername, stuPasswd)), login::finalout2userId(login::stuLoginPipeline(stuUsername, stuPasswd)), stuHwId) << std::endl;
			}
			else
			{
				std::cout << submission::automationPipeline(login::finalout2Token(login::tchLoginPipeline(tchUsername, tchPasswd)), hwId, login::finalout2Token(login::stuLoginPipeline(stuUsername, stuPasswd)), login::finalout2userId(login::stuLoginPipeline(stuUsername, stuPasswd)), stuHwId) << std::endl;
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
