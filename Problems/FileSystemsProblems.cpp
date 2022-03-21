#include <iostream>
#include "Problem1.h"
#include "PathTester.h"
#include "Problem3.h"
#include <filesystem>

int main()
{
	/*
	
		PROBLEM 1

		Problem1 problem_1_handler;
		problem_1_handler.handleProblem();
	
	*/

	/*
	
		PROBLEM 2 - PATH_TESTER

		std::filesystem::path tajny_file_path = std::filesystem::path("./documents") / "NajwiekszaTajemnicaPiotra.txt";
		std::filesystem::path directory_path = std::filesystem::path("./documents");

		PathTester pathTester;
		bool is_directory = pathTester.is_directory(tajny_file_path);

		std::cout << "DIRECTORY: " << is_directory << std::endl;

		is_directory = pathTester.is_directory(directory_path);
		std::cout << "DIRECTORY: " << is_directory << std::endl;
	
	*/

	std::filesystem::path directory_path = std::filesystem::path("./documents");

	Problem3 problem_3_handler;
	problem_3_handler.handleProblem(directory_path);

}