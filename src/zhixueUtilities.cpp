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

	std::string tchToken;
	std::string stuToken;
	std::string hwId;
	std::string stuId;
	std::string stuHwId;
	std::string listIndex;
	//std::string finaloutStr;

	bool useIndex = false;

	auto getListMode = (clipp::command("getList").set(selected, mode::getList),
						clipp::required("-st", "--student-token") & clipp::value("stuToken", stuToken) % "Student's Token");

	auto getAnsMode = (clipp::command("getAns").set(selected, mode::getAns),
					   clipp::required("-tt", "--teacher-token") & clipp::value("tchToken", tchToken) % "ANY Teacher's Token",
					   (clipp::required("-hi", "--homework-id") & clipp::value("hwId", hwId) % "Homework ID") | (clipp::required("-i", "--index").set(useIndex, true) & clipp::value("listIndex", listIndex) % "List Index"));

	auto redoMode = (clipp::command("redoHomework").set(selected, mode::redoHomework),
					 clipp::required("-tt", "--teacher-token") & clipp::value("tchToken", tchToken) % "ANY Teacher's Token",
					 clipp::required("-si", "--student-id") & clipp::value("stuId", stuId) % "Student's ID",
					 (clipp::required("-hi", "--homework-id") & clipp::value("hwId", hwId) % "Homework ID") | (clipp::required("-i", "--index").set(useIndex, true) & clipp::value("listIndex", listIndex) % "List Index"));

	auto submitMode = (clipp::command("submitHomework").set(selected, mode::submitHomework),
					   clipp::required("-tt", "--teacher-token") & clipp::value("tchToken", tchToken) % "ANY Teacher's Token",
					   clipp::required("-st", "--student-token") & clipp::value("stuId", stuToken) % "Student's ID",
					   (clipp::required("-hi", "--homework-ids") & clipp::value("hwId", hwId) % "Homework ID" & clipp::value("stuHwId", stuHwId) % "Student Homework ID") | (clipp::required("-i", "--index").set(useIndex, true) & clipp::value("listIndex", listIndex) % "List Index"));

	auto reviseMode = (clipp::command("autoRevise").set(selected, mode::autoRevise),
					   clipp::required("-tt", "--teacher-token") & clipp::value("tchToken", tchToken) % "ANY Teacher's Token",
					   clipp::required("-st", "--student-token") & clipp::value("stuId", stuToken) % "Student's ID",
					   (clipp::required("-hi", "--homework-ids") & clipp::value("hwId", hwId) % "Homework ID" & clipp::value("stuHwId", stuHwId) % "Student Homework ID") | (clipp::required("-i", "--index").set(useIndex, true) & clipp::value("listIndex", listIndex) % "List Index"));

	auto autoMode = (clipp::command("automation").set(selected, mode::automation),
					 clipp::required("-tt", "--teacher-token") & clipp::value("tchToken", tchToken) % "ANY Teacher's Token",
					 clipp::required("-st", "--student-token") & clipp::value("stuId", stuToken) % "Student's ID",
					 clipp::required("-si", "--student-id") & clipp::value("stuId", stuId) % "Student's ID",
					 (clipp::required("-hi", "--homework-ids") & clipp::value("hwId", hwId) % "Homework ID" & clipp::value("stuHwId", stuHwId) % "Student Homework ID") | (clipp::required("-i", "--index").set(useIndex, true) & clipp::value("listIndex", listIndex) % "List Index"));

	auto cli = ((getListMode | getAnsMode | redoMode | submitMode | reviseMode | autoMode | clipp::command("help").set(selected, mode::help)),
				clipp::option("-v", "--version").call([]
													  { std::cout << "version 1.6final" << std::endl; })
					.doc("show version"),
				clipp::option("-h", "--help").set(selected, mode::help).doc("show this help message"));

	if (parse(argc, argv, cli))
	{
		switch (selected)
		{
		case mode::getList:
			std::cout << analyzeJson::analyzeHwListJson(reqData::getHwListJson(stuToken)) << std::endl;
			break;
		case mode::getAns:
			if (useIndex)
			{
				std::string inputJson = analyzeJson::analyzeHwListJson(reqData::getHwListJson(stuToken));
				hwId = analyzeJson::index2hwId(inputJson, listIndex);
				std::cout << analyzeJson::analyzeAnsJson(reqData::postAnsJson(tchToken, hwId)) << std::endl;
			}
			else
			{
				std::cout << analyzeJson::analyzeAnsJson(reqData::postAnsJson(tchToken, hwId)) << std::endl;
			}

			break;
		case mode::redoHomework:
			if (useIndex)
			{
				std::string inputJson = analyzeJson::analyzeHwListJson(reqData::getHwListJson(stuToken));
				hwId = analyzeJson::index2hwId(inputJson, listIndex);
				std::cout << reqData::redoHomework(tchToken, stuId, hwId) << std::endl;
			}
			else
			{
				std::cout << reqData::redoHomework(tchToken, stuId, hwId) << std::endl;
			}

			break;
		case mode::submitHomework:
			if (useIndex)
			{
				std::string inputJson = analyzeJson::analyzeHwListJson(reqData::getHwListJson(stuToken));
				hwId = analyzeJson::index2hwId(inputJson, listIndex);
				stuHwId = analyzeJson::index2stuHwId(inputJson, listIndex);
				std::cout << submission::submissionPipeline(tchToken, hwId, stuToken, stuHwId) << std::endl;
			}
			else
			{
				std::cout << submission::submissionPipeline(tchToken, hwId, stuToken, stuHwId) << std::endl;
			}

			break;
		case mode::autoRevise:
			if (useIndex)
			{
				std::string inputJson = analyzeJson::analyzeHwListJson(reqData::getHwListJson(stuToken));
				hwId = analyzeJson::index2hwId(inputJson, listIndex);
				stuHwId = analyzeJson::index2stuHwId(inputJson, listIndex);
				std::cout << submission::revisionPipeline(tchToken, hwId, stuToken, stuHwId) << std::endl;
			}
			else
			{
				std::cout << submission::revisionPipeline(tchToken, hwId, stuToken, stuHwId) << std::endl;
			}

			break;
		case mode::automation:
			if (useIndex)
			{
				std::string inputJson = analyzeJson::analyzeHwListJson(reqData::getHwListJson(stuToken));
				hwId = analyzeJson::index2hwId(inputJson, listIndex);
				stuHwId = analyzeJson::index2stuHwId(inputJson, listIndex);
				std::cout << submission::automationPipeline(tchToken, hwId, stuToken, stuId, stuHwId) << std::endl;
			}
			else
			{
				std::cout << submission::automationPipeline(tchToken, hwId, stuToken, stuId, stuHwId) << std::endl;
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
