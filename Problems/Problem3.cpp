#include "Problem3.h"

void Problem3::handleProblem(std::filesystem::path target_path) {

	std::filesystem::directory_iterator directory_iterator = std::filesystem::directory_iterator(target_path);
	std::filesystem::directory_iterator end;

	{
		std::ofstream output_file("./output.txt");
		if (output_file.is_open()) {
			for (; directory_iterator != end; directory_iterator++) {

				std::filesystem::directory_entry entry = *directory_iterator;
				std::string file_path = entry.path().string();

				std::ifstream input_file(file_path);
				if (input_file.is_open()) {

					std::string line;
					while (!input_file.eof()) {
						getline(input_file, line);
						output_file << line;
					}

					input_file.close();
				}
			}
		}
		output_file.close();
	}

	
}