#pragma once

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
    const char ** argv);

} /* namespace args_parse */

