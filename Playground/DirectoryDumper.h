#include <filesystem>
#include <iostream>
#include <fstream>

#include "FileMarker.h"

#pragma once
class DirectoryDumper
{
private:
	std::filesystem::path directory;
	std::filesystem::path dumping_file_path;
public:
	DirectoryDumper(std::filesystem::path _directory, std::filesystem::path _dumping_file_path) : directory(_directory), dumping_file_path(_dumping_file_path) {}

	std::filesystem::path dumpDirectory();
};

