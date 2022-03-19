#include <filesystem>
#include <fstream>
#include <chrono>
#include <iostream>

#pragma once
class PathPlayground
{
public:
	std::filesystem::path pathGeneration();
	
	void introspectPath(std::filesystem::path path);
	void fileSystemManagement();
	void introspectFileContent();

	void iterateDirContent();
};

