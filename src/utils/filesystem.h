#pragma once

#include <string>
#include <experimental/filesystem>

inline std::string remove_extension(const std::string& filename) {
	size_t lastdot = filename.find_last_of(".");
	if (lastdot == std::string::npos) return filename;
	return filename.substr(0, lastdot);
}

// TODO: Move in filesystem.h
inline bool FolderExists(const std::string& name, const std::string& path = "projects")
{
	for (auto& item : std::experimental::filesystem::directory_iterator(path))
	{
		if (name == item.path().filename().string())
		{
			return true;
		}
	}

	return false;
}

inline std::vector<std::experimental::filesystem::path> GetFilePathsFromDirectory(const std::string &path)
{
	std::vector<std::experimental::filesystem::path> paths;

	for (auto& item : std::experimental::filesystem::directory_iterator(std::experimental::filesystem::current_path().string() + "\\" + path))
	{
		if (item.path().has_filename() && item.path().has_extension())
		{
			paths.push_back(item.path());
		}
	}

	return paths;
}

inline std::vector<std::experimental::filesystem::path> GetRecursiveFilePathsFromDirectory(const std::string &path)
{
	std::vector<std::experimental::filesystem::path> paths;

	for (auto& item : std::experimental::filesystem::recursive_directory_iterator(std::experimental::filesystem::current_path().string() + "\\" + path))
	{
		if (std::experimental::filesystem::is_directory(item)) {}
		else
		{
			paths.push_back(item.path());
		}
	}

	return paths;
}



//std::experimental::filesystem::directory_iterator* directory_entries(const std::string& path)
//{
//	return &std::experimental::filesystem::directory_iterator(path);
//}