#include "args_parse/args.hpp"
#include "args_parse/utils.hpp"
#include "args_parse/single_arg.hpp"
#include "args_parse/multi_arg.hpp"
#include <iostream>


int main(int argc, const char** argv) {
    

    args_parser::EatParams(argc, argv);

    args_parser::ArgsParser<std::string> parser;
    args_validator::NormalParserValidator<std::string> validator;
    parser.SetValidator(&validator);

    single_arg::SingleArgument<int, int> intArg = { 'a', "additional", true };
    args_validator::InRangeValidator validator1{ -10,10 };
    intArg.setValidator(&validator1);

    single_arg::SingleArgument<std::string> stringArg = { 's', "string", true };
    args_validator::NormalStringValidator<std::string> validator2{"/@0-9"};
    stringArg.setValidator(&validator2);

    single_arg::SingleArgument<bool> boolArg = { 'f', "flag",true };
    args_validator::NormalBoolValidator<std::string> validator3{};
    boolArg.setValidator(&validator3);


    parser.add(&intArg);
    parser.add(&stringArg);
    parser.add(&boolArg);


    if (const auto result = parser.parse(argc, argv); result.isOk())
    {
        std::cout << parser.GetHelp() << std::endl;

        if (intArg.isDefined())
        {
            std::cout << intArg.getLongName() << ":" << intArg.GetValue() << std::endl;
        }

        if (stringArg.isDefined())
        {
            std::cout << stringArg.getLongName() << ":" << stringArg.GetValue() << std::endl;
        }

        if (boolArg.isDefined())
        {
            std::cout << boolArg.getLongName() << ":" << utils::boolToString(boolArg.GetValue()) << std::endl;
        }
    }
    else
    {
        std::cerr << result.Error().description << std::endl;
        return 1;
    }

    return 0;

}