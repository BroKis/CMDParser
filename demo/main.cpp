#include <args_parse/args.hpp>
#include <args_parse/utils.hpp>
#include <iostream>

int main(int argc, const char ** argv)
{
    args_parse::EatParams(argc, argv);
    args_parse::ArgsParser parser;
    args_validator::NormalParserValidator validator;
    parser.SetValidator(&validator);

    args_types::IntArg intArg =  args_types::IntArg('a', "additional", args_types::ArgumentsType::Int);
    args_validator::IntInRangeValidator validator1;
    intArg.SetIntValidator(&validator1);


    args_types::StringArg stringArg = args_types::StringArg('s', "string", args_types::ArgumentsType::String);
    args_validator::NormalStringValidator validator2;
    stringArg.SetStringValidator(&validator2);

    args_types::BoolArg boolArg = args_types::BoolArg('f', "flag", args_types::ArgumentsType::Bool);
    args_validator::NormalBoolValidator validator3;
    boolArg.SetBoolValidator(&validator3);
    

    parser.add(&intArg);
    parser.add(&stringArg);
    parser.add(&boolArg);

    if (const auto result = parser.parse(argc, argv); result.isOk())
    {
        std::cout<<parser.GetHelp()<<std::endl;
       
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

