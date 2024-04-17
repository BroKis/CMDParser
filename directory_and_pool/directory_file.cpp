#include "directory_file.hpp"

namespace directory {
	
	void Directory::setId(const std::thread::id id)
	{
		_id = id;
	}

	void Directory::setPath(const std::filesystem::path path)
	{
		_path = path;
	}

	Directory& Directory::emplaceBackDirectory(std::filesystem::path path)
	{
		return directories.emplace_back(path);
	}
	void Directory::addFile(const std::string& file)
	{
		files.push_back(file);
	}

	void Directory::Show(const int whitespace) {
		for (auto directory : directories) {
			std::cout << std::string(whitespace,' ') << directory._path.filename().string() + ":" << _id << std::endl;
			directory.Show(whitespace + 2);
		}
		for (const auto& filename : files) {
			std::cout << std::string(whitespace+2, ' ') << filename << std::endl;
		}
	}

	std::filesystem::path Directory::getPath()
	{
		return _path;
	}

}

