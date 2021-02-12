#include "argparse/argparse.hpp"
#include "Grammar.yy.hpp"
#include "ExpertSystem.hpp"

FILE *OpenFile(const std::string &file_name) {
	FILE *f = fopen(file_name.c_str(), "r");
	if (!f)
		throw std::runtime_error("Error on opening file : " + file_name);
	return f;
}

int main(int argc, char **argv)
{
	argparse::ArgumentParser argparse("expert-system");
	
	argparse.add_argument("input_file")
			.required()
			.help("specify the input file.");
	
	argparse.add_argument("-v", "--visual")
			.help("turns on visual mode.");
	
	try {
		argparse.parse_args(argc, argv);
	}
	catch (const std::runtime_error &err) {
		std::cout << err.what() << std::endl;
		std::cout << std::endl;
		std::cout << argparse;
		exit(0);
	}
	
	try {
		ExpertSystem expertSystem;
		if (argparse.present("-v"))
			expertSystem.SetVisualMode(true);
		expertSystem.Execute(OpenFile(argparse.get<std::string>("start_puzzle")));
	}
	catch (const std::exception &exception) {
		std::cout << exception.what();
	}
	exit(0);
}
