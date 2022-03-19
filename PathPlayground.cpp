#include "PathPlayground.h"

std::filesystem::path PathPlayground::pathGeneration() {
	std::filesystem::path doc_path = std::filesystem::path{
		"E:\\colledge\\S4\\programming\\19c5e616-gr12-repo\\lab3\\Filesystems\\Filesystems"
	};

	std::cout << "BASE PATH:" << std::endl << doc_path.string() << std::endl << std::endl;

	/*
		APPENDING:
		1. with /= operator
		2. path.append function
	*/

	doc_path /= "Documents";
	std::cout << "APPEND DOCS PATH:" << std::endl << doc_path.string() << std::endl << std::endl;

	doc_path /= "TestDirectory";
	std::cout << "APPEND TEST DIR PATH:" << std::endl << doc_path.string() << std::endl << std::endl;

	//doc_path += "test.txt";
	doc_path.append("text.txt");
	std::cout << "FINAL PATH:" << std::endl << doc_path.string() << std::endl << std::endl;

	return doc_path;
}

void PathPlayground::introspectPath(std::filesystem::path path) {
	/*
		NOW WE CAN SELECT SPECIFIC PARTS OF THE PATH:

		Source:
		Modern C++ Programming Cookbook

		1. root_name
		2. root_directory
		3. relative_path
		4. parent_path
		5. filename
		6. file_extension

	*/

	std::cout << "------------------------ ANALYSING A PATH ------------------------" << std::endl;
	std::cout << "Just to remind ourselves the path we are working with: " << std::endl << path.string() << std::endl << std::endl;

	std::cout << "ROOT: " << path.root_name() << std::endl;
	std::cout << "ROOT_DIRECTORY: " << path.root_directory() << std::endl;
	std::cout << "ROOT_PATH: " << path.root_path() << std::endl;
	std::cout << "RELATIVE_PATH: " << path.relative_path() << std::endl;
	std::cout << "PARENT_PATH: " << path.parent_path() << std::endl;

	std::cout << std::endl;
	std::cout << "FILENAME: " << path.filename() << std::endl;
	std::cout << "STEM: " << path.stem() << std::endl;
	std::cout << "EXTENSION: " << path.extension() << std::endl;

	/* has_something->has_filename, has_stem etc.to check whether a path has a particular elements */

	std::cout << std::endl;
	if (path.is_absolute()) {
		std::cout << "PATH IS ABSOLUTE" << std::endl;
	}
	else {
		std::cout << "PATH IS RELATIVE" << std::endl;
	}

	/* and now we can replace particular elements of the path */
	std::cout << std::endl;

	std::cout << "STEM: " << path.stem() << std::endl;
	std::cout << "EXTENSION: " << path.extension() << std::endl << std::endl;

	path.replace_filename("some_cool_file_name");
	path.replace_extension("png");

	std::cout << "NEW STEM: " << path.stem() << std::endl;
	std::cout << "NEW EXTENSION: " << path.extension() << std::endl;

	/* Also worth remembering is the fact that we may iterate over the path */

	std::cout << std::endl << std::endl;
	for (auto const& path_element : path) {
		std::cout << path_element << std::endl;
	}
}

void PathPlayground::fileSystemManagement() {
	std::filesystem::path base_path = std::filesystem::current_path() / "dir" / "dir" / "text.txt";
	std::cout << "WORKING FILE/DIR: " << std::endl;
	std::cout << base_path.string() << std::endl << std::endl;

	/*
		directory named 'dir' does not exists, therefore any file manipulations will end up with errors
	*/

	// Now we should get the absolute path
	std::error_code error{};
	std::filesystem::path absolute_path = std::filesystem::canonical(base_path, error); // we pass std::error_code or an exception is thrown

	std::cout << "ERROR: " << error.message() << std::endl;
	if (error.value() == 0) {
		std::cout << "CANNONICAL PATH: " << absolute_path.string() << std::endl;
	}

	if (std::filesystem::exists(absolute_path)) {
		std::cout << "Path exists " << std::endl;
	}
	else {
		std::cout << "Path does not exists " << std::endl; // safer is to check whether a path exists

		std::cout << std::endl << std::endl;

		/* Now we can create the missing directory

			If we use create_directory and path required to create some of them recursively
			then we will get back the error: 'The system cannot find the path specified.'

		*/
		std::filesystem::create_directories(base_path, error); // we here create directories recursively
		std::cout << "CREATE ERROR: " << error.message() << std::endl;

		absolute_path = std::filesystem::canonical(base_path, error);
		std::cout << "CANNONICAL PATH ERROR: " << error.message() << std::endl;

		if (error.value() == 0) {
			std::cout << "CANNONICAL PATH: " << absolute_path.string() << std::endl;
		}
	}
}

void PathPlayground::introspectFileContent() {
	std::filesystem::path base_path = std::filesystem::current_path() / "test";
	std::filesystem::path base_path2 = std::filesystem::path{ "E:\\colledge\\S4\\programming\\19c5e616-gr12-repo\\lab3\\Filesystems\\Filesystems\\test" };

	std::error_code error{};

	std::cout << "DIR: " << base_path.string() << std::endl;

	if (!std::filesystem::exists(base_path)) {
		std::cout << "PATH DOES NOT EXISTS" << std::endl;
		return;
	}

	// WE CAN CHECK PATH EQUIVALENCE:
	std::cout << std::endl;
	std::cout << "PATH 1: " << base_path.string() << std::endl;
	std::cout << "PATH 2: " << base_path2.string() << std::endl;

	if (std::filesystem::equivalent(base_path, base_path2)) {
		std::cout << "Paths are equivalent" << std::endl;
	}
	else {
		std::cout << "Paths are NOT equivalent" << std::endl;
	}

	std::cout << std::endl << std::endl;

	// LET'S PLAY WITH SOME FILES:
	std::cout << "Is directory: " << (std::filesystem::is_directory(base_path) ? "true" : "false") << std::endl;
	std::cout << "File size: " << std::filesystem::file_size(base_path) << " bits" << std::endl;
	std::cout << "Hard link count: " << std::filesystem::hard_link_count(base_path) << std::endl;

	/*
		PRESENTATION -> reading file modification time
	*/
	std::chrono::time_point<std::chrono::file_clock> file_mod_time_point = std::filesystem::last_write_time(base_path);
	std::chrono::time_point<std::chrono::utc_clock> utc_time = std::chrono::file_clock::to_utc(file_mod_time_point);

	std::chrono::time_point<std::chrono::system_clock> sys_time_point = std::chrono::utc_clock::to_sys(utc_time);
	const std::time_t t_c = std::chrono::system_clock::to_time_t(sys_time_point);

	struct tm time;
	localtime_s(&time, &t_c);

	std::cout << "TIME: " << time.tm_year + 1900 << "-" << time.tm_mon + 1 << "-" << time.tm_mday << " "
		<< time.tm_hour << ":" << time.tm_min << ":" << time.tm_sec << std::endl;

	auto status = std::filesystem::status(base_path);
	std::filesystem::perms file_permissions = status.permissions();

	std::cout << "permissions: ";

	bool owner_read_permission = (file_permissions & std::filesystem::perms::owner_read) != std::filesystem::perms::none;
	std::cout << (owner_read_permission ? "r" : "-");

	bool owner_write_permission = (file_permissions & std::filesystem::perms::owner_write) != std::filesystem::perms::none;
	std::cout << (owner_write_permission ? "w" : "-");

	/*
		PERMISSIONS LIST:

		1. owner_read 'r'
		2. owner_write 'w'
		3. owner_exec 'x'
		4. group_read 'r'
		5. group_write 'w'
		6. group_exec 'x'
		7. others_read 'r'
		8. others_write 'w'
		9. others_exec 'x'
	*/
}

void PathPlayground::iterateDirContent() {
	std::filesystem::path base_path = std::filesystem::current_path() / "test";
	
	/*
		WE CAN USE ONE OF TWO DIRECTORIES:

		1. directory_iterator
		2. recursive_directory_iterator 

	*/

	bool exists = std::filesystem::exists(base_path);
	if (!exists) {
		std::cout << "PATH DOES NOT EXIST" << std::endl;
		return;
	}

	bool is_directory = std::filesystem::is_directory(base_path);
	if (!is_directory) {
		std::cout << "NOT A DIRECTORY" << std::endl;
		return;
	}

	// NOW IS TIME TO ITERATE

	std::filesystem::directory_iterator dir_iterator = std::filesystem::directory_iterator(base_path);
	std::filesystem::directory_iterator end;
	/*
	for (auto const& entry : dir_iterator) {
		auto filename = entry.path().filename();
		auto status = entry.status();

		if (std::filesystem::is_directory(status)) {
			std::cout << "[+]" << filename << std::endl;
		}
		else if (std::filesystem::is_regular_file(status)) {
			std::cout << " " << filename << std::endl;
		}
		else {
			std::cout << "[?]" << filename << std::endl;
		}
	}
	*/
	for (; dir_iterator != end; dir_iterator++) {
		auto entry = *dir_iterator;
		auto filename = entry.path().filename();
		auto status = entry.status();

		if (std::filesystem::is_directory(status)) {
			std::cout << "[+]" << filename << std::endl;
		}
		else if (std::filesystem::is_regular_file(status)) {
			std::cout << " " << filename << std::endl;
		}
		else {
			std::cout << "[?]" << filename << std::endl;
		}
	}
}

void PathPlayground::moveDirectoryConent() {
	
	/* 
		1. To rename a directory
		2. To move a directory
		3. To rename a file
	*/

	std::filesystem::path base_path = std::filesystem::current_path() / "test";

	auto temp_path = base_path / "tmp1" / "tmp2";
	auto new_temp_path = base_path / "tmp1" / "tmp3";

	std::error_code error;
	std::filesystem::rename(temp_path, new_temp_path, error);

	if (error) std::cout << error.message() << std::endl;
}