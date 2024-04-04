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
    parser.SetValidator(new args_validator::NormalParserValidator());

    args_types::IntArg intArg = args_types::IntArg('a', "additional", args_types::ArgumentsType::Int);
    intArg.SetIntValidator(new args_validator::IntInRangeValidator());
    std::unique_ptr<args_types::Arg> arg = std::make_unique<args_types::IntArg>(intArg);

    parser.add(std::move(arg));

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

        auto result = parser.parse(3, argv).isOk();
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
    parser.SetValidator(new args_validator::NormalParserValidator());

    args_types::BoolArg boolArg = args_types::BoolArg('r', "repeater", args_types::ArgumentsType::Bool);
    boolArg.SetBoolValidator(new args_validator::NormalBoolValidator());
    std::unique_ptr<args_types::Arg> arg = std::make_unique<args_types::BoolArg>(boolArg);

    parser.add(std::move(arg));

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
    parser.SetValidator(new args_validator::NormalParserValidator());

    args_types::StringArg stringArg = args_types::StringArg('o', "output", args_types::ArgumentsType::String);
    stringArg.SetStringValidator(new args_validator::FileStringValidator());
    std::unique_ptr<args_types::Arg> arg = std::make_unique<args_types::StringArg>(stringArg);

    parser.add(std::move(arg));

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
    intArg.SetIntValidator(new args_validator::IntInRangeValidator());
    std::unique_ptr<args_types::Arg> arg1 = std::make_unique<args_types::MultiIntArg>(intArg);

    args_types::BoolArg boolArg = args_types::BoolArg('r', "repeater", args_types::ArgumentsType::Bool);
    boolArg.SetBoolValidator(new args_validator::NormalBoolValidator());
    std::unique_ptr<args_types::Arg> arg2 = std::make_unique<args_types::BoolArg>(boolArg);

    args_types::StringArg stringArg = args_types::StringArg('o', "output", args_types::ArgumentsType::String);
    stringArg.SetStringValidator(new args_validator::FileStringValidator());
    std::unique_ptr<args_types::Arg> arg3 = std::make_unique<args_types::StringArg>(stringArg);

    std::cout << "Full parse" << std::endl;
   

    std::vector argsv{"", "-a=4","-a4","-a","4","-r0","-o=output.txt"};
    SECTION("Correct parse all argument")
    {

        args_parse::ArgsParser parser;
        parser.SetValidator(new args_validator::NormalParserValidator());

        parser.add(std::move(arg1));
        parser.add(std::move(arg2));
        parser.add(std::move(arg3));

        const char** args = new const char* [2];
        auto result = parser.parse(argsv.size(), &argsv[0]).isOk();
        std::cout << std::boolalpha << result << std::endl;
        std::unique_ptr<Arg> arg1 = parser.getArgumentFromVector(0);
        REQUIRE(arg1->isDefined());
        std::unique_ptr<Arg> arg2 = parser.getArgumentFromVector(1);
        REQUIRE(arg2->isDefined());
        std::unique_ptr<Arg> arg3 = parser.getArgumentFromVector(2);
        REQUIRE(arg3->isDefined());
        REQUIRE(result);


      
    }
}
