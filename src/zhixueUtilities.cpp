#include "clipp.hpp"
#include "zhixueUtilities.hpp"

int main(int argc, char *argv[])
{

	enum class mode
	{
		getList,
		getAns,
		redoHomework,
		help
	};
	mode selected = mode::help;

	std::string tchToken;
	std::string stuToken;
	std::string hwId;
	std::string stuId;
	//std::string finaloutStr;

	auto getListMode = (clipp::command("getList").set(selected, mode::getList),
						clipp::required("-t", "--student-token") & clipp::value("stuToken", stuToken) % "Student's Token");

	auto getAnsMode = (clipp::command("getAns").set(selected, mode::getAns),
					   clipp::required("-t", "--teacher-token") & clipp::value("tchToken", tchToken) % "ANY Teacher's Token",
					   clipp::required("-w", "--homework-id") & clipp::value("hwId", hwId) % "Homework ID");

	auto redoMode = (clipp::command("redoHomework").set(selected, mode::redoHomework),
					 clipp::required("-t", "--teacher-token") & clipp::value("tchToken", tchToken) % "ANY Teacher's Token",
					 clipp::required("-s", "--student-id") & clipp::value("stuId", stuId) % "Student's ID",
					 clipp::required("-w", "--homework-id") & clipp::value("hwId", hwId) % "Homework ID");

	auto cli = ((getListMode | getAnsMode | redoMode | clipp::command("help").set(selected, mode::help)),
				clipp::option("-v", "--version").call([]
													  { std::cout << "version 0.1fix" << std::endl; })
					.doc("show version"));

	if (parse(argc, argv, cli))
	{
		switch (selected)
		{
		case mode::getList:
			std::cout << analyzeJson::analyzeHwListJson(reqData::getHwListJson(stuToken)) << std::endl;
			break;
		case mode::getAns:
			std::cout << analyzeJson::analyzeAnsJson(reqData::postAnsJson(tchToken, hwId)) << std::endl;
			break;
		case mode::redoHomework:
			std::cout << reqData::redoHomework(tchToken, stuId, hwId) << std::endl;
			break;
		case mode::help:
			std::cout << clipp::make_man_page(cli, "zhixueUtilities");
			break;
		}
	}
	else
	{
		std::cout << clipp::usage_lines(cli, "zhixueUtilities") << std::endl;
	}

	return 0;
}
