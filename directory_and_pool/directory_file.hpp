#pragma once
#include <thread>
#include <iostream>
#include <filesystem>
#include <list>

namespace directory
{
	/*
	* @brief Класс директории позволяющий вести обход каталога
	*/
	class Directory
	{
	private:
		/// Поле хранящее id потока
		std::thread::id _id{};
		/// поле храящее путь директорр
		std::filesystem::path _path{};
		/// поле хранящее список файлов
		std::vector<std::string> files{};
		/// поле хранящее список директорий
		std::list<Directory> directories{};
	public:
		/*
		* @brief Метод для установки Id потока директории
		* @param[in] id входящий параметр id потока, который обрабатывал директорию.
		*/
		void setId(const std::thread::id id);
		/*
		* @brief Метод для установки пути по которому находится директория
		* @param[in] path входящий параметр пути по которому находится директория.
		*/
		void setPath(const std::filesystem::path path);
		/*
		* @brief Метод для добавления файла
		* @param[in] file входящий параметр пути по которому находится директория.
		*/
		void addFile(const std::string& file);
		/*
		* @brief Метод для получения пути директории
		*/
		std::filesystem::path getPath();
		/*
		* @brief Метод для создания новой директории и ее возвращения
		* @param [in] path апарметр пути для создания объекта
		*/
		Directory& emplaceBackDirectory(std::filesystem::path path);
		/*
		*@brief Метод для вывода директорий и файлов;
		*/
		void Show(const int whitespace = 0);
		/*
		* @brief Конструктор с параметрами
		*/
		Directory(std::filesystem::path path) : _path{ path } {}
		
		~Directory() = default;
	};


}/* namespace directory*/