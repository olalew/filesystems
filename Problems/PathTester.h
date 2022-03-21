#include <filesystem>
#include <iostream>

#pragma once
class PathTester
{
public:
	bool is_directory(std::filesystem::path target_path);
};

