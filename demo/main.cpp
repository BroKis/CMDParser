#include <args_parse/args.hpp>
#include <iostream>

int main(int argc, const char ** argv)
{
    args_parse::EatParams(argc, argv);
    args_parse::ArgsParser parser;
    parser.SetValidator(new args_validator::NormalParserValidator());

    args_types::IntArg intArg =  args_types::IntArg('a', "additional", args_types::ArgumentsType::Int);
    intArg.SetIntValidator(new args_validator::IntInRangeValidator());
    std::unique_ptr<Arg> arg = std::make_unique<IntArg>(intArg);

    args_types::StringArg stringArg = args_types::StringArg('s', "string", args_types::ArgumentsType::String);
    stringArg.SetStringValidator(new args_validator::NormalStringValidator());
    std::unique_ptr<Arg> arg2 = std::make_unique<StringArg>(stringArg);
    args_types::BoolArg boolArg = args_types::BoolArg('f', "flag", args_types::ArgumentsType::Bool);
    boolArg.SetBoolValidator(new args_validator::NormalBoolValidator());
    std::unique_ptr<Arg> arg3 = std::make_unique<BoolArg>(boolArg);
    

    parser.add(std::move(arg));
    parser.add(std::move(arg2));
    parser.add(std::move(arg3));

    if (const auto result = parser.parse(argc, argv); result.isOk())
    {
        std::unique_ptr<Arg> arg1 = parser.getArgumentFromVector(0);
        if (arg1->isDefined())
        {
            arg1->showHelp();
        }
        std::unique_ptr<Arg> arg2 = parser.getArgumentFromVector(1);
        if (arg2->isDefined())
        {
           arg2->showHelp();
        }
        std::unique_ptr<Arg> arg3 = parser.getArgumentFromVector(2);
        if (arg3->isDefined())
        {
            arg3->showHelp();
        }
    }
    else
    {
        std::cerr << result.Error().description << std::endl;
        return 1;
    }
    return 0;

   

}

