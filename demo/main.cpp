#include <args_parse/args.hpp>

int main(int argc, const char ** argv)
{
    args_parse::EatParams(argc, argv);
    args_parse::ArgsParser parser;

    Arg* arg = new args_types::IntArg('a', "append");
    Arg* arg2 = new args_types::IntArg('s', "substriction");
    Arg* arg3 = new args_types::StringArg('i', "input");
    Arg* arg4 = new args_types::StringArg('o', "output");
    Arg* arg5 = new args_types::StringArg('y', "yes");
    Arg* arg6 = new args_types::MultiBoolArg('v', "verbose");

    parser.add(arg);
    parser.add(arg2);
    parser.add(arg3);
    parser.add(arg4);
    parser.add(arg5);
    parser.add(arg6);

    if (parser.parse(argc, argv))
    {
        if (arg->isDefined())
        {
            arg->showHelp();
        }
        if (arg2->isDefined())
        {
            arg2->showHelp();
        }
        if (arg3->isDefined())
        {
            arg3->showHelp();
        }
        if (arg4->isDefined())
        {
            arg4->showHelp();
        }
        if (arg5->isDefined())
        {
            arg5->showHelp();
        }
        if (arg6->isDefined())
        {
            arg6->showHelp();
        }
    }

    parser.~ArgsParser();
    delete arg;
    delete arg2;
    delete arg3;
    delete arg4;
    delete arg5;
    delete arg6;


}

