#include <catch2/catch_all.hpp>
#include "args_parse/args.hpp"
#include "args_parse/args_error.hpp"
#include "args_parse/args_types.hpp"
#include "args_parse/args_validator.hpp"
#include <iostream>
#include <memory>

TEST_CASE("IntArg", "[all]")
{
    args_parse::ArgsParser parser;
    args_validator::NormalParserValidator validator; 
    parser.SetValidator(&validator);

    args_types::IntArg intArg = args_types::IntArg('a', "additional", args_types::ArgumentsType::Int);
    args_validator::IntInRangeValidator validator1;
    intArg.SetIntValidator(&validator1);
  

    parser.add(&intArg);

    std::cout << "IntArg" << std::endl;

    SECTION("Correct parse short argument with equal")
    {
        const char** argv = new const char* [2];
        const char* str = "-a=4";
        argv[1] = str;

        auto result = parser.parse(2, argv).isOk();
        std::cout << std::boolalpha << result << std::endl;
        REQUIRE(result);

    }

    SECTION("Correct parse short argument without equal")
    {
        const char** argv = new const char* [2];
        const char* str = "-a4";
        argv[1] = str;

        auto result = parser.parse(2, argv).isOk();
        std::cout << std::boolalpha << result << std::endl;
        REQUIRE(result);

    }
    SECTION("Correct parse short argument without equal and next parameter ")
    {
        const char** argv = new const char* [3];
        const char* str = "-a";
        const char* str2 = "4";
        argv[1] = str;
        argv[2] = str2;

        const auto result = parser.parse(3, argv).isOk();
        std::cout << std::boolalpha << result << std::endl;
        REQUIRE(result);

    }

    SECTION("Correct parse short argument with equal")
    {
        const char** argv = new const char* [2];
        const char* str = "-a=4";
        argv[1] = str;
   

        auto result = parser.parse(2, argv).isOk();
        std::cout << std::boolalpha << result << std::endl;
        REQUIRE(result);

    }

    SECTION("Incorrect parse wrong argument")
    {
        const char** argv = new const char* [2];
        const char* str = "------";
        argv[1] = str;


        auto result = parser.parse(2, argv).isOk();
        std::cout << std::boolalpha << result << std::endl;
        REQUIRE_FALSE(result);
    }
    SECTION("Incorrect parse short argument")
    {
        const char** argv = new const char* [2];
        const char* str = "---a=4";
        argv[1] = str;


        auto result = parser.parse(2, argv).isOk();
        std::cout << std::boolalpha << result << std::endl;
        REQUIRE_FALSE(result);
    }

    SECTION("Incorrect parse number")
    {
        const char** argv = new const char* [2];
        const char* str = "458";
        argv[1] = str;

        auto result = parser.parse(2, argv).isOk();
        std::cout << std::boolalpha << result << std::endl;
        REQUIRE_FALSE(result);
    }

    SECTION("Correct parse long argument with equal")
    {
        const char** argv = new const char* [2];
        const char* str = "--additional=4";
        argv[1] = str;


        auto result = parser.parse(2, argv).isOk();
        std::cout << std::boolalpha << result << std::endl;
        REQUIRE(result);

    }

    SECTION("Correct parse long argument without equal and next parameter ")
    {
        const char** argv = new const char* [3];
        const char* str = "--additional";
        const char* str2 = "4";
        argv[1] = str;
        argv[2] = str2;

        auto result = parser.parse(2, argv).isOk();
        std::cout << std::boolalpha << result << std::endl;
        REQUIRE(result);

    }
    SECTION("Incorrect parse short argument with equal and empty parameter")
    {
        const char** argv = new const char* [2];
        const char* str = "-a=";
        argv[1] = str;

        auto result = parser.parse(2, argv).isOk();
        std::cout << std::boolalpha << result << std::endl;
        REQUIRE_FALSE(result);

    }
    
    SECTION("Incorrect parse long argument with equal and empty parameter")
    {
        const char** argv = new const char* [2];
        const char* str = "--additional=";
        argv[1] = str;


        auto result = parser.parse(2, argv).isOk();
        std::cout << std::boolalpha << result << std::endl;
        REQUIRE_FALSE(result);

    }
    SECTION("Incorrect parse")
    {
        const char** argv = new const char* [2];
        const char* str = "--additional4";
        argv[1] = str;


        auto result = parser.parse(2, argv).isOk();
        std::cout << std::boolalpha << result << std::endl;
        REQUIRE_FALSE(result);

    }
    SECTION("Parse short form of long name")
    {
        const char** argv = new const char* [3];
        const char* str = "--add";
        const char* str2 = "4";
        argv[1] = str;
        argv[2] = str2;

        auto result = parser.parse(3, argv).isOk();
        std::cout << std::boolalpha << result << std::endl;
        REQUIRE(result);
    }

}
TEST_CASE("Bool Arg", "[all]")
{
    args_parse::ArgsParser parser;
    args_validator::NormalParserValidator validator;
    parser.SetValidator(&validator);

    args_types::BoolArg boolArg = args_types::BoolArg('r', "repeater", args_types::ArgumentsType::Bool);
    args_validator::NormalBoolValidator validator2;
    boolArg.SetBoolValidator(&validator2);
   
    parser.add(&boolArg);

    std::cout << "BoolArg" << std::endl;
    SECTION("Parse normal with true parameter with equal ")
    {
        const char** argv = new const char* [2];
        const char* str = "-r=true";
        argv[1] = str;

        auto result = parser.parse(2, argv).isOk();
        std::cout << std::boolalpha << result << std::endl;
        REQUIRE(result);
    }

    SECTION("Parse normal with false parameter with equal")
    {
        const char** argv = new const char* [2];
        const char* str = "-r=true";
        argv[1] = str;

        auto result = parser.parse(2, argv).isOk();
        std::cout << std::boolalpha << result << std::endl;
        REQUIRE(result);
    }

    SECTION("Parse normal with zero parameter without equal")
    {
        const char** argv = new const char* [2];
        const char* str = "-r0";
        argv[1] = str;

        auto result = parser.parse(2, argv).isOk();
        std::cout << std::boolalpha << result << std::endl;
        REQUIRE(result);
    }

    SECTION("Parse normal with one parameter without equal")
    {
        const char** argv = new const char* [3];
        const char* str = "-r";
        const char* str2 = "1";
        argv[1] = str;
        argv[2] = str2;

        auto result = parser.parse(3, argv).isOk();
        std::cout << std::boolalpha << result << std::endl;
        REQUIRE(result);
    }
    SECTION("Parse incorrect argument")
    {
        const char** argv = new const char* [2];
        const char* str = "-r4";
        argv[1] = str;

        auto result = parser.parse(2, argv).isOk();
        std::cout << std::boolalpha << result << std::endl;
        REQUIRE_FALSE(result);

    }
}

TEST_CASE("String Arg", "[all]")
{
    args_parse::ArgsParser parser;
    args_validator::NormalParserValidator validator;
    parser.SetValidator(&validator);

    args_types::StringArg stringArg = args_types::StringArg('o', "output", args_types::ArgumentsType::String);
    args_validator::FileStringValidator validator2;
    stringArg.SetStringValidator(&validator2);
   

    parser.add(&stringArg);

    std::cout << "StringArg" << std::endl;
    SECTION("Parse short argument with equal ")
    {
        const char** argv = new const char* [2];
        const char* str = "-o=output.txt";
        argv[1] = str;

        auto result = parser.parse(2, argv).isOk();
        std::cout << std::boolalpha << result << std::endl;
        REQUIRE(result);
    }

    SECTION("Parse short argument without equal")
    {
        const char** argv = new const char* [2];
        const char* str = "-ooutput.txt";
        argv[1] = str;

        auto result = parser.parse(2, argv).isOk();
        std::cout << std::boolalpha << result << std::endl;
        REQUIRE(result);
    }

    SECTION("Parse short argument with param how next argument")
    {
        const char** argv = new const char* [3];
        const char* str = "-o";
        const char* str2 = "output.txt";
        argv[1] = str;
        argv[2] = str2;

        auto result = parser.parse(3, argv).isOk();
        std::cout << std::boolalpha << result << std::endl;
        REQUIRE(result);
    }

    SECTION("Parse short form of long name")
    {
        const char** argv = new const char* [3];
        const char* str = "--out";
        const char* str2 = "output.txt";
        argv[1] = str;
        argv[2] = str2;

        auto result = parser.parse(3, argv).isOk();
        std::cout << std::boolalpha << result << std::endl;
        REQUIRE(result);
    }
    SECTION("Parse incorrect argument")
    {
        const char** argv = new const char* [2];
        const char* str = "--output=haram.bgb";
        argv[1] = str;

        auto result = parser.parse(2, argv).isOk();
        std::cout << std::boolalpha << result << std::endl;
        REQUIRE_FALSE(result);

    }
}
TEST_CASE("Parse all arguments")
{

    

    args_types::MultiIntArg intArg = args_types::MultiIntArg('a', "additional", args_types::ArgumentsType::Int);
    args_validator::IntInRangeValidator validator1;
    intArg.SetIntValidator(&validator1);


    args_types::BoolArg boolArg = args_types::BoolArg('r', "repeater", args_types::ArgumentsType::Bool);
    args_validator::NormalBoolValidator validator2;
    boolArg.SetBoolValidator(&validator2);

    args_types::StringArg stringArg = args_types::StringArg('o', "output", args_types::ArgumentsType::String);
    args_validator::FileStringValidator validator3;
    stringArg.SetStringValidator(&validator3);
    
    args_types::StringArg helpArg = args_types::StringArg('h', "help", args_types::ArgumentsType::Empty);

    std::cout << "Full parse" << std::endl;
   

    std::vector argsv{"", "-a=4","-a4","-a","4","-r0","-o=output.txt", "-h"};
    SECTION("Correct parse all argument")
    {

        args_parse::ArgsParser parser;
        args_validator::NormalParserValidator validator;
        parser.SetValidator(&validator);

        parser.add(&intArg);
        parser.add(&boolArg);
        parser.add(&stringArg);
        parser.add(&helpArg);

        const char** args = new const char* [2];
        const auto result = parser.parse((int)argsv.size(), &argsv[0]).isOk();
        std::cout << std::boolalpha << result << std::endl;

        
        REQUIRE(helpArg.isDefined());
        std::cout << parser.GetHelp() << std::endl;
        REQUIRE(intArg.isDefined());
        REQUIRE(boolArg.isDefined());
        REQUIRE(stringArg.isDefined());
        REQUIRE(result);


      
    }
}
