#pragma once
#include <string>
#include <chrono>
namespace utils
{
        /**
        *@brief Метод приводящий string к bool
        * @param[in] str входное значение
        */
        bool stringToBool(const std::string& str);
        /**
        *@brief Метод приводящий bool к string
        * @param[in] param входное значение
        */
        std::string boolToString(const bool param);
        /**
        * @brief Метод, выделяющее короткое имя длинного аргумента
        * @param[in] str передаваемый в метод аргумент
        */
        std::string extractShortFormOfLongName(const std::string& str);
        /**
        * @brief Метод, приводящий значение к микросекундам в зависимости от литерала
        * @param[in] value передаваемый в метод параметр значение
        * @param[in] unit передаваемый в метод литерал
        */
        std::chrono::microseconds chronoToMicroseconds(long long value, std::string& unit);
   
}/*namespace utils*/