#include "PathTester.h"


bool PathTester::is_directory(std::filesystem::path target_path) {
	bool exists = std::filesystem::exists(target_path);
	if (!exists) {
		std::cout << "FILE DOES NOT EXISTS" << std::endl;
		return false;
	}

	bool is_directory = std::filesystem::is_directory(target_path);
	return is_directory;
}