#include "DirectoryDumper.h"

std::filesystem::path DirectoryDumper::dumpDirectory() {
	bool exists = std::filesystem::exists(directory);

	if (!exists) {
		std::cout << "File does not exist" << std::endl << std::endl;
		return std::filesystem::path();
	}

	bool is_directory = std::filesystem::is_directory(directory);

	if (!is_directory) {
		std::cout << "Not a directory. " << std::endl << std::endl;
		return std::filesystem::path();
	}

	std::ofstream dumping_file(dumping_file_path.string(), std::ios::binary);
	if (!dumping_file.is_open()) {
		std::cout << "Cannot open dumping file. " << std::endl;
		return std::filesystem::path();
	}

	std::filesystem::directory_iterator dir_it = std::filesystem::directory_iterator(directory);
	std::filesystem::directory_iterator end;
	for (; dir_it != end; dir_it++) {
		auto entry = *dir_it;
		auto status = entry.status();

		if (!std::filesystem::is_regular_file(status)) {
			continue;
		}

		std::filesystem::path entry_path = entry.path();
		std::string extension = entry_path.extension().string();

		if (extension == ".txt") {
			std::cout << "TEXT FILE" << std::endl; // TIME TO DUMP IN HERE
		}

		FileMarker fileMarker((entry_path.parent_path() / entry_path.filename()).string());
		fileMarker.load_content();

		fileMarker.serialize(dumping_file);
	}
	dumping_file.close();
	return std::filesystem::path();
}