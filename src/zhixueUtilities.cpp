#include "clipp.hpp"
#include "zhixueUtilities.hpp"

int main(int argc, char* argv[]) {

	enum class mode {getList, getAns, help};
	mode selected = mode::help;

	std::string tchToken;
	std::string stuToken;
	std::string hwId;
	//std::string finaloutStr;

	auto getListMode = (
		clipp::command("getList").set(selected,mode::getList),
		clipp::required("-t", "--student-token") & clipp::value("stuToken", stuToken) % "ANY Teacher's Token"
	);

	auto getAnsMode = (
		clipp::command("getAns").set(selected,mode::getAns),
		clipp::required("-t", "--teacher-token") & clipp::value("tchToken", tchToken) % "Student's Token",
		clipp::required("-i", "--homework-id") & clipp::value("hwId", hwId) % "Homework ID"
	);

	auto cli = (
    (getListMode | getAnsMode | clipp::command("help").set(selected,mode::help) ),
    clipp::option("-v", "--version").call([]{std::cout << "version 0.1fix" <<std::endl;}).doc("show version")  );


	if(parse(argc, argv, cli)) {
    switch(selected) {
        case mode::getList:  std::cout << analyzeHwListJson(getHwListJson(stuToken)) << std::endl; break;
        case mode::getAns: std::cout << analyzeAnsJson(postAnsJson(tchToken, hwId)) << std::endl; break;
        case mode::help: std::cout << clipp::make_man_page(cli, "zhixueUtilities"); break;
    }
	} else {
     std::cout << clipp::usage_lines(cli, "zhixueUtilities") << std::endl;
	}

	
	




	return 0;
}
