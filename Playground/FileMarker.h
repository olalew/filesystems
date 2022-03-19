#include <string>
#include <filesystem>
#include <fstream>
#include <iostream>

#pragma once
class FileMarker
{
private:
	std::string relative_path;
	size_t file_length;
	char* file_content;

public:
	FileMarker(std::string _path) : relative_path(_path) {}
	
	~FileMarker() {
		if (this->file_length > 0) {
			delete this->file_content;
			this->file_content = nullptr;
			this->file_length = 0;
		}
	}

	std::string get_relative_path();
	size_t get_file_length();

	char* get_file_content();

	bool load_content();

	bool serialize(std::ofstream& output_file);
};

