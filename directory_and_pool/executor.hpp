#pragma once
#include "thread_pool.hpp"
#include "directory_file.hpp"
#include <filesystem>

namespace executor {

	/*
	* @brief Выполняемый потоками метод
	* @param[in] pool параметр Пула потоков
	* @param[in] directory входящий параметр директории
	*/
	void execution_function(thread_pool::ThreadPool& pool, directory::Directory&directory)
	{
		std::filesystem::path folder_path = directory.getPath();
		if (!std::filesystem::exists(folder_path)) {
			return;
		}

		directory.setId(std::this_thread::get_id());
		std::filesystem::directory_iterator end_itr;
		for (std::filesystem::directory_iterator itr(folder_path); itr != end_itr; ++itr)
		{
			if (itr->is_directory())
			{
				directory::Directory&new_directory = directory.emplaceBackDirectory(itr->path());
				
				pool.enqueue([&pool, &new_directory]() {
					execution_function(pool, new_directory);
					std::this_thread::sleep_for(pool.getDebugSleep());
					});
			}
			else
			{
				directory.addFile(itr->path().filename().string());
			}
		}
	}
}/*namespace executor*/