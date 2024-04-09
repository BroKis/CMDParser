#pragma once
#include "args_types.hpp"
#include <map>
#include <memory>
using namespace args_types;
namespace args_parse
{

    /// @brief Функция для обработки аргументов командной строки.
    /// 
    /// Просто берет и обрабатывает.
    /// 
    /// @attention
    /// Подразумевается, что все аргументы имеют корректное значение.
    ///
    void EatParams(
        /// Сколько всего аргументов.
        int argc,
        /// Значения аргументов. Должно быть ровно @a argc.
        const char** argv);


    /// @brief Класс-парсер аргументов командной строки
    ///
    /// Содержит поля и методы необходимые парсеру
    class ArgsParser
    {
    public:
        ///@brief Метод, добавляющий аргумент в вектор аргументов
        ///
        /// Добавляет аргумент в вектор
        /// 
        /// @attention
        /// Подразумевается умный указатель
        virtual void add(
            ///умный указатель на аргумент
            Arg* arg
        );
        ///@brief Метод, который парсит входной поток аргументов
        ///
        /// Парсит входной поток аргументов командной строки
        virtual args_error::ParseResult parse(
            /// сколько всего аргументов
            int argc,
            /// значений аргументов. Должно быть ровно @argc
            const char** argv);
        /// @brief Метод для извлечения аргумента из вектора аргуменета
        ///
        /// Извлекает аргумент из вектора аргументов
        virtual Arg* getArgumentFromVector(
            ///номер аргумента в векторе
            int index
        ) const;
        /// @brief Метод, устанавливающий валидатор парсера командной строки
        ///
        /// Устанвавливает валидатор парсера 
        void SetValidator(
            /// валидатор парсера командной строки
            args_validator::ParserValidator* validator
        );

        virtual std::string GetHelp() const;
    private:
        /// @brief Метод, который проверяет можно ли распарсить аргумент
        ///
        ///Проверяет можно ли распарсить аргумент
        virtual args_error::ParseResult tryParse(
            /// Аргумент, который нужнот распарсить
            const std::string& parseable_arg
        );
        /// @brief Метод, который выделяет параметр из аргумента
        ///
        ///Выделяет метод из аргумента
        virtual std::string extractParameter(
            /// строка-источник
            const std::string & source, 
            /// разделитель
            std::string& extractable);
        /// @brief Метод, устанавливающий значение для длинной команды со знаком = или без
        ///
        /// Устанавливает значение аргумента длинной команды со знаком равно или без знака
        /// 
        /// @attention
        /// Подразумевается, что все аргументы корректны
        virtual args_error::ParseResult setParamsInLongNameWithEqualOrWithout(
            /// строка источник
            const std::string& source, 
            /// аргумент которому присваивается значение
            Arg* arg, 
            /// масств аргументов
            const char**argv, 
            /// индекс аргумента командной строки
            int&index
        );
        /// @brief Метод, устанавливающий значение для коротокй команды со знаком =
        ///
        /// Устанавливает значение аргумента короткой команды со знаком равно
        /// 
        /// @attention
        /// Подразумевается, что все аргументы корректны
        virtual args_error::ParseResult setParamsInShortNameWithEqual(
            /// строка-источник
            const std::string& source,
            /// аргумент, которому устанавливается значение
            Arg* arg
        );

        /// @brief Метод, устанавливающий значение для коротокй команды без знака =
        ///
        /// Устанавливает значение аргумента короткой команды без знака равно
        /// 
        /// @attention
        /// Подразумевается, что все аргументы корректны
        virtual args_error::ParseResult setParamsInShortNameWithoutEqual(
            /// строка-источник
            const std::string& source, 
            /// аргумент, которому присваивают значение
            Arg* arg,
            /// массив аргументов
            const char** argv, 
            /// индекс аргумента
            int &index);
        /// @brief Метод, парсящий длинную команду
        ///
        /// Парсит длинную команду
        /// 
        /// @attention
        /// Подразумевается, что все аргументы корректны
        virtual args_error::ParseResult parseLongCommandArgument(
            /// строка-источник
            const std::string& source, 
            /// массив аргументов
            const char**argv, 
            /// индекс аргумента
            int &index);
        /// @brief Метод, парсящий короткую команду
        ///
        /// Парсит короткую команду
        /// 
        /// @attention
        /// Подразумевается, что все аргументы корректны
        virtual args_error::ParseResult parseShortCommandArgument(
            /// короткая команда
            const std::string& source, 
            /// массив аргументов
            const char**argv, 
            /// индекс аргумента
            int &index
        );

       
        /// @brief Поле для валидатора парсера
        args_validator::ParserValidator* _validator{};
        /// @brief Поле список аргументов
        std::vector<Arg*> Args{};
    protected:
        
    };
}/* namespace args_parse */

