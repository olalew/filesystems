#include "Problem1.h"

void Problem1::handleProblem() {

	std::filesystem::path tajemnica_path = std::filesystem::path("./documents") / "NajwiekszaTajemnicaPiotra.txt";

	/*
		FILE SIZE
		std::filesystem::file_size(tajemnica_path)
	*/
	std::cout << "FILE SIZE: " << std::filesystem::file_size(tajemnica_path) << " bits" << std::endl;

	/*
		LAST WRITE DATE
		std::filesystem::last_write_time(tajemnica_path)
	*/
	std::chrono::time_point<std::chrono::file_clock> last_modification_date = std::filesystem::last_write_time(tajemnica_path);
	std::chrono::time_point<std::chrono::utc_clock> utc_last_modification_date = std::chrono::file_clock::to_utc(last_modification_date);
	std::chrono::time_point<std::chrono::system_clock> system_last_modification_date = std::chrono::utc_clock::to_sys(utc_last_modification_date);

	std::time_t time_last_modification_date = std::chrono::system_clock::to_time_t(system_last_modification_date);

	struct tm time;
	localtime_s(&time, &time_last_modification_date);

	std::cout << "LAST MODIFICATION DATE: " << time.tm_year + 1900 << "-" << time.tm_mon << "-" << time.tm_mday << " " << time.tm_hour << ":"
		<< time.tm_min << ":" << time.tm_sec << std::endl;

	/*
		FILE ASSIGNED PERMISSIONS:
	*/
	std::filesystem::file_status file_status = std::filesystem::status(tajemnica_path);
	std::filesystem::perms file_permissions = file_status.permissions();

	bool owner_read_permission = (file_permissions & std::filesystem::perms::owner_read) != std::filesystem::perms::none;
	bool owner_write_permission = (file_permissions & std::filesystem::perms::owner_read) != std::filesystem::perms::none;
	bool owner_exec_permission = (file_permissions & std::filesystem::perms::owner_exec) != std::filesystem::perms::none;

	bool group_read_permission = (file_permissions & std::filesystem::perms::group_read) != std::filesystem::perms::none;
	bool group_write_permission = (file_permissions & std::filesystem::perms::group_write) != std::filesystem::perms::none;
	bool group_exec_permission = (file_permissions & std::filesystem::perms::group_exec) != std::filesystem::perms::none;
	
	bool other_read_permission = (file_permissions & std::filesystem::perms::others_read) != std::filesystem::perms::none;
	bool other_write_permission = (file_permissions & std::filesystem::perms::others_write) != std::filesystem::perms::none;
	bool other_exec_permission = (file_permissions & std::filesystem::perms::others_exec) != std::filesystem::perms::none;

	std::cout << (owner_read_permission ? 'r' : '-') << (owner_write_permission ? 'w' : '-') << (owner_exec_permission ? 'e' : '-')
		<< (group_read_permission ? 'r' : '-') << (group_write_permission ? 'w' : '-') << (group_exec_permission ? 'e' : '-')
		<< (other_read_permission ? 'r' : '-') << (other_write_permission ? 'w' : '-') << (other_exec_permission ? 'e' : '-') << std::endl;
}