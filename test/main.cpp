#include <catch2/catch_all.hpp>
#include "args_parse/args.hpp"
#include "args_parse/args_error.hpp"
#include "args_parse/single_arg.hpp"
#include "args_parse/multi_arg.hpp"
#include "args_parse/args_validator.hpp"
#include <iostream>
#include <memory>


TEST_CASE("IntArg", "[all]")
{
    args_parser::ArgsParser parser{};
    args_validator::NormalParserValidator<std::string> parserValidator{};
    parser.SetValidator(&parserValidator);

    single_arg::SingleArgument<int, int> intArg{ 'a', "additional", true };
    args_validator::InRangeValidator<int> rangeValidator{ -5,5 };
    intArg.setValidator(&rangeValidator);
    parser.add(&intArg);

    std::cout << "IntArg" << std::endl;

    SECTION("Correct parse short argument with equal")
    {
        std::vector argsv{ " ","-a=4" };
        auto result = parser.parse((int)argsv.size(), &argsv[0]).isOk();
        std::cout << std::boolalpha << result << std::endl;
        REQUIRE(result);
    }

    SECTION("Argument greater then right border of range")
    {
        std::vector argsv{ " ","-a=6" };
        auto result = parser.parse((int)argsv.size(), &argsv[0]).isOk();
        std::cout << std::boolalpha << result << std::endl;
        REQUIRE_FALSE(result);
    }

    SECTION("Argument lether then left border of range")
    {
        std::vector argsv{ " ","-a=-6" };
        auto result = parser.parse((int)argsv.size(),&argsv[0]).isOk();
        std::cout << std::boolalpha << result << std::endl;
        REQUIRE_FALSE(result);

    }

    SECTION("Correct parse short argument without equal")
    {
        std::vector argsv{ " ","-a4" };
        auto result = parser.parse((int)argsv.size(), &argsv[0]).isOk();
        std::cout << std::boolalpha << result << std::endl;
        REQUIRE(result);

    }
    SECTION("Correct parse short argument without equal and next parameter ")
    {
        std::vector argsv{ " ","-a","4"};
        auto result = parser.parse((int)argsv.size(), &argsv[0]).isOk();
        std::cout << std::boolalpha << result << std::endl;
        REQUIRE(result);

    }

    SECTION("Correct parse short argument with equal")
    {
        std::vector argsv{ " ","-a=4" };
        auto result = parser.parse((int)argsv.size(), &argsv[0]).isOk();
        std::cout << std::boolalpha << result << std::endl;
        REQUIRE(result);

    }

    SECTION("Incorrect parse wrong argument")
    {
        std::vector argsv{ " ","------------" };
        auto result = parser.parse((int)argsv.size(), &argsv[0]).isOk();
        std::cout << std::boolalpha << result << std::endl;
        REQUIRE_FALSE(result);
    }
    SECTION("Incorrect parse short argument")
    {
        std::vector argsv{ " ","---a=4" };
        auto result = parser.parse((int)argsv.size(), &argsv[0]).isOk();
        std::cout << std::boolalpha << result << std::endl;
        REQUIRE_FALSE(result);
    }

    SECTION("Incorrect parse number")
    {
        std::vector argsv{ " ","458" };
        auto result = parser.parse((int)argsv.size(), &argsv[0]).isOk();
        std::cout << std::boolalpha << result << std::endl;
        REQUIRE_FALSE(result);
    }

    SECTION("Correct parse long argument with equal")
    {
        std::vector argsv{ " ","--additional=4" };
        auto result = parser.parse((int)argsv.size(), &argsv[0]).isOk();
        std::cout << std::boolalpha << result << std::endl;
        REQUIRE(result);

    }

    SECTION("Correct parse long argument without equal and next parameter ")
    {
        std::vector argsv{ " ","--additional","4"};
        auto result = parser.parse((int)argsv.size(), &argsv[0]).isOk();
        std::cout << std::boolalpha << result << std::endl;
        REQUIRE(result);

    }
    SECTION("Incorrect parse short argument with equal and empty parameter")
    {
        std::vector argsv{ " ","-a=" };
        auto result = parser.parse((int)argsv.size(), &argsv[0]).isOk();
        std::cout << std::boolalpha << result << std::endl;
        REQUIRE_FALSE(result);

    }

    SECTION("Incorrect parse long argument with equal and empty parameter")
    {
        std::vector argsv{ " ","--additional=" };
        auto result = parser.parse((int)argsv.size(), &argsv[0]).isOk();
        std::cout << std::boolalpha << result << std::endl;
        REQUIRE_FALSE(result);

    }
    SECTION("Incorrect parse")
    {
        std::vector argsv{ " ","--additional4" };
        auto result = parser.parse((int)argsv.size(), &argsv[0]).isOk();
        std::cout << std::boolalpha << result << std::endl;
        REQUIRE_FALSE(result);
    }
    SECTION("Parse short form of long name")
    {

        std::vector argsv{ " ","--add","4" };
        auto result = parser.parse((int)argsv.size(), &argsv[0]).isOk();
        std::cout << std::boolalpha << result << std::endl;
        REQUIRE(result);
    }

}

TEST_CASE("Bool Arg", "[all]")
{
    args_parser::ArgsParser parser{};
    args_validator::NormalParserValidator<std::string> parserValidator{};
    parser.SetValidator(&parserValidator);

    single_arg::SingleArgument<bool, std::string> boolArg{ 'r', "repeater", true };
    args_validator::NormalBoolValidator<std::string> validator2{};
    boolArg.setValidator(&validator2);

    parser.add(&boolArg);

    std::cout << "BoolArg" << std::endl;
    SECTION("Parse normal with true parameter with equal ")
    {
        std::vector argsv{ " ","-r=true" };
        auto result = parser.parse((int)argsv.size(), &argsv[0]).isOk();
        std::cout << std::boolalpha << result << std::endl;
        REQUIRE(result);
    }

    SECTION("Parse normal with false parameter with equal")
    {
        std::vector argsv{ " ","-r=false" };
        auto result = parser.parse((int)argsv.size(), &argsv[0]).isOk();
        std::cout << std::boolalpha << result << std::endl;
        REQUIRE(result);
    }

    SECTION("Parse normal with zero parameter without equal")
    {
        std::vector argsv{ " ","-r0" };
        auto result = parser.parse((int)argsv.size(), &argsv[0]).isOk();
        std::cout << std::boolalpha << result << std::endl;
        REQUIRE(result);
    }

    SECTION("Parse normal with one parameter without equal")
    {
        std::vector argsv{ " ","-r1" };
        auto result = parser.parse((int)argsv.size(), &argsv[0]).isOk();
        std::cout << std::boolalpha << result << std::endl;
        REQUIRE(result);
    }
    SECTION("Parse incorrect argument")
    {
        std::vector argsv{ " ","-r4" };
        auto result = parser.parse((int)argsv.size(), &argsv[0]).isOk();
        std::cout << std::boolalpha << result << std::endl;
        REQUIRE(result);

    }
}

TEST_CASE("String Arg", "[all]")
{
    args_parser::ArgsParser parser{};
    args_validator::NormalParserValidator<std::string> parserValidator{};
    parser.SetValidator(&parserValidator);

    single_arg::SingleArgument<std::string, std::string> fileArg{ 'o', "output", true};
    args_validator::NormalFileValidator<std::string> fileValidator {".txt"};
    fileArg.setValidator(&fileValidator);

    parser.add(&fileArg);

    std::cout << "StringArg" << std::endl;
    SECTION("Parse short argument with equal ")
    {
        std::vector argsv{ " ","-o=output.txt" };
        auto result = parser.parse((int)argsv.size(), &argsv[0]).isOk();
        std::cout << std::boolalpha << result << std::endl;
        REQUIRE(result);
    }

    SECTION("Parse short argument without equal")
    {
        std::vector argsv{ " ","-ooutput.txt" };
        auto result = parser.parse((int)argsv.size(), &argsv[0]).isOk();
        std::cout << std::boolalpha << result << std::endl;
        REQUIRE(result);
    }

    SECTION("Parse short argument with param how next argument")
    {
        std::vector argsv{ " ","-o","output.txt" };
        auto result = parser.parse((int)argsv.size(), &argsv[0]).isOk();
        std::cout << std::boolalpha << result << std::endl;
        REQUIRE(result);
    }

    SECTION("Parse short form of long name")
    {
        std::vector argsv{ " ","-out","output.txt" };
        auto result = parser.parse((int)argsv.size(), &argsv[0]).isOk();
        std::cout << std::boolalpha << result << std::endl;
        REQUIRE(result);
    }
    SECTION("Parse incorrect argument")
    {
        std::vector argsv{ " ","--output=haram.bgb" };
        auto result = parser.parse((int)argsv.size(), &argsv[0]).isOk();
        std::cout << std::boolalpha << result << std::endl;
        REQUIRE(result);

    }
}

TEST_CASE("FloatArg", "[all]")
{
    args_parser::ArgsParser parser{};
    args_validator::NormalParserValidator<std::string> parserValidator{};
    parser.SetValidator(&parserValidator);

    single_arg::SingleArgument<float, float> intArg{ 'a', "additional", true };
    args_validator::InRangeValidator<float> rangeValidator{ -5.0,5.0 };
    intArg.setValidator(&rangeValidator);


    parser.add(&intArg);

    std::cout << "FloatArg" << std::endl;

    SECTION("Correct parse short argument with equal")
    {
        std::vector argsv{ " ","-a=4.0" };
        auto result = parser.parse((int)argsv.size(), &argsv[0]).isOk();
        std::cout << std::boolalpha << result << std::endl;
        REQUIRE(result);

    }

    SECTION("Correct parse short argument without equal")
    {
        std::vector argsv{ " ","-a4.0" };
        auto result = parser.parse((int)argsv.size(), &argsv[0]).isOk();
        std::cout << std::boolalpha << result << std::endl;
        REQUIRE(result);

    }
    SECTION("Correct parse short argument without equal and next parameter ")
    {
        std::vector argsv{ " ","-a4.5" };
        auto result = parser.parse((int)argsv.size(), &argsv[0]).isOk();
        std::cout << std::boolalpha << result << std::endl;
        REQUIRE(result);

    }

    SECTION("Incorrect parse wrong argument")
    {
        std::vector argsv{ " ","------" };
        auto result = parser.parse((int)argsv.size(), &argsv[0]).isOk();
        std::cout << std::boolalpha << result << std::endl;
        REQUIRE_FALSE(result);
    }
    SECTION("Incorrect parse short argument")
    {
        std::vector argsv{ " ","-a=4.0" };
        auto result = parser.parse((int)argsv.size(), &argsv[0]).isOk();
        std::cout << std::boolalpha << result << std::endl;
        REQUIRE_FALSE(result);
    }

    SECTION("Incorrect parse number")
    {
        std::vector argsv{ " ","458" };
        auto result = parser.parse((int)argsv.size(), &argsv[0]).isOk();
        std::cout << std::boolalpha << result << std::endl;
        REQUIRE_FALSE(result);
    }

    SECTION("Correct parse long argument with equal")
    {
        std::vector argsv{ " ","--additional=4.0" };
        auto result = parser.parse((int)argsv.size(), &argsv[0]).isOk();
        std::cout << std::boolalpha << result << std::endl;
        REQUIRE(result);
    }

    SECTION("Correct parse long argument without equal and next parameter ")
    {
       
        std::vector argsv{ " ","--additional","4.0" };
        auto result = parser.parse((int)argsv.size(), &argsv[0]).isOk();
        std::cout << std::boolalpha << result << std::endl;
        REQUIRE(result);
    }
    SECTION("Incorrect parse short argument with equal and empty parameter")
    {
        std::vector argsv{ " ","-a=" };
        auto result = parser.parse((int)argsv.size(), &argsv[0]).isOk();
        std::cout << std::boolalpha << result << std::endl;
        REQUIRE(result);
    }

    SECTION("Incorrect parse long argument with equal and empty parameter")
    {
        std::vector argsv{ " ","--additional=" };
        auto result = parser.parse((int)argsv.size(), &argsv[0]).isOk();
        std::cout << std::boolalpha << result << std::endl;
        REQUIRE(result);
    }
    SECTION("Incorrect parse")
    {
        std::vector argsv{ " ","--additional4.0" };
        auto result = parser.parse((int)argsv.size(), &argsv[0]).isOk();
        std::cout << std::boolalpha << result << std::endl;
        REQUIRE_FALSE(result);
    }
    SECTION("Parse short form of long name")
    {
        std::vector argsv{ " ","--add=4.0" };
        auto result = parser.parse((int)argsv.size(), &argsv[0]).isOk();
        std::cout << std::boolalpha << result << std::endl;
        REQUIRE(result);
    }

    SECTION("Argument greater then right border of range")
    {
        std::vector argsv{ " ","-a=6.0" };
        auto result = parser.parse((int)argsv.size(), &argsv[0]).isOk();
        std::cout << std::boolalpha << result << std::endl;
        REQUIRE(result);
    }

    SECTION("Argument lether then left border of range")
    {
        std::vector argsv{ " ","-a=-4.0" };
        auto result = parser.parse((int)argsv.size(), &argsv[0]).isOk();
        std::cout << std::boolalpha << result << std::endl;
        REQUIRE(result);

    }

}

TEST_CASE("Parse all arguments")
{



    multi_arg::MultiArgument<int, int>intArg = { 'a', "additional", true };
    args_validator::InRangeValidator<int> validator1{ -10,10 };
    intArg.setValidator(&validator1);


    single_arg::SingleArgument<bool> boolArg = { 'r', "repeater", true };
    args_validator::NormalBoolValidator<std::string> validator2{};
    boolArg.setValidator(&validator2);

    single_arg::SingleArgument<std::string> stringArg = { 'o', "output", true };
    args_validator::NormalFileValidator<std::string> validator3{ ".txt" };
    stringArg.setValidator(&validator3);

    single_arg::SingleArgument<bool> helpArg = { 'h', "help", false };

    std::cout << "Full parse" << std::endl;


    std::vector argsv{ "", "-a=4","-a4","-a","4","-r0","-o=output.txt", "-h" };
    SECTION("Correct parse all argument")
    {

        args_parser::ArgsParser parser{};
        args_validator::NormalParserValidator<std::string> parserValidator{};
        parser.SetValidator(&parserValidator);

        parser.add(&intArg);
        parser.add(&boolArg);
        parser.add(&stringArg);
        parser.add(&helpArg);

      
        const auto result = parser.parse((int)argsv.size(), &argsv[0]).isOk();
        std::cout << std::boolalpha << result << std::endl;


        REQUIRE(helpArg.isDefined());
        std::cout << parser.GetHelp() << std::endl;
        REQUIRE(intArg.isDefined());
        for (size_t i = 0; i < intArg.getSize(); i++)
        {
            std::cout << intArg.getByIndex(i) << " ";
        }
        std::cout<<std::endl;
        REQUIRE(boolArg.isDefined());
        REQUIRE(stringArg.isDefined());
        REQUIRE(result);
    }
}

TEST_CASE("Parse single user type")
{
    args_parser::ArgsParser parser{};
    args_validator::NormalParserValidator<std::string> parserValidator{};
    parser.SetValidator(&parserValidator);

    std::cout << "Parse user type" << std::endl;
    SECTION("Correct parse of user type")
    {
        single_arg::SingleArgument<user_types::ChronoCloack,std::string> debugSleep{ 'd',"debug-sleep",true};
        args_validator::NormalChronoValidator<std::string> chronoValidator{};
        debugSleep.setValidator(&chronoValidator);
        parser.add(&debugSleep);


        const char** argv = new const char* [2];
        const char* str = "-d=10ms";
        argv[1] = str;

        auto result = parser.parse(2, argv).isOk();
        std::cout << std::boolalpha << result << std::endl;
        std::cout << debugSleep.GetValue().GetMicroseconds().count() << std::endl;
        REQUIRE(result);
    }

    SECTION("incorrect parse of user type")
    {
        single_arg::SingleArgument<user_types::ChronoCloack, std::string> debugSleep{ 'd',"debug-sleep",true };
        args_validator::NormalChronoValidator<std::string> chronoValidator{};
        debugSleep.setValidator(&chronoValidator);
        parser.add(&debugSleep);


        const char** argv = new const char* [2];
        const char* str = "-d=10ds";
        argv[1] = str;

        auto result = parser.parse(2, argv).isOk();
        std::cout << std::boolalpha << result << std::endl;
        REQUIRE_FALSE(result);
    }
}