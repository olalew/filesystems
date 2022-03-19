#include "FileMarker.h"

std::string FileMarker::get_relative_path() {
	return this->relative_path;
}

size_t FileMarker::get_file_length() {
	return this->file_length;
}

char* FileMarker::get_file_content() {
	return this->file_content;
}

bool FileMarker::load_content() {
	std::filesystem::path full_path = std::filesystem::current_path() / relative_path;
	
	std::ifstream input_file(full_path.string(), std::ios::binary);
	if (!input_file.is_open()) {
		std::cout << "CANNOT OPEN FILE: " << relative_path << std::endl << std::endl;
		return false;
	}

	input_file.seekg(0, std::ios_base::end);
	this->file_length = static_cast<size_t>(input_file.tellg());
	input_file.seekg(0, std::ios_base::beg);

	char* content = new char[this->file_length];
	input_file.read(content, this->file_length);

	this->file_content = content;

	auto success = !input_file.fail() && this->file_length == input_file.gcount();

	input_file.close();
	return success;
}

bool FileMarker::serialize(std::ofstream& output_file) {
	auto path = static_cast<int>(relative_path.size());

	output_file.write(reinterpret_cast<char*>(&relative_path), sizeof(relative_path));
	output_file.write(relative_path.data(), relative_path.size());

	output_file.write(reinterpret_cast<char*>(&file_length), sizeof(file_length));
	output_file.write(file_content, file_length);

	return !output_file.fail();
}