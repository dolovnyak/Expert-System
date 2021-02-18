#include "argparse/argparse.hpp"
#include "Grammar.yy.hpp"
#include "ExpertSystem.hpp"
#include "Visualizer.hpp"

FILE *open_file(const std::string &file_name) {
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
			.default_value(false)
			.implicit_value(true)
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
		std::unique_ptr<ExpertSystemData> data = std::unique_ptr<ExpertSystemData>(ExpertSystem::Parse(open_file(argparse.get<std::string>("input_file"))));
		ExpertSystem::Solve(*data);

		if (argparse.get<bool>("--visual")) {
			Visualizer visualizer;
			visualizer.SetupImGui();
			visualizer.Show(data);
		} else {
			for (Expression *expression : data->GetQueries()) {
				std::cout << *expression << " = " << Expression::GetStateName(expression->GetState()) << std::endl;
			}
		}
	}
	catch (const std::exception &exception) {
		std::cout << exception.what();
	}
	exit(0);
}