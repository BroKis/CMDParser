#include <args_parse/args.hpp>

int main(int argc, const char ** argv)
{
    args_parse::EatParams(argc, argv);
    args_parse::ArgsParser parser;
    Arg* arg = new args_types::IntArg('a', "append");
    Arg* arg2 = new args_types::BoolArg('v', "verbose");
    Arg* arg3 = new args_types::StringArg('i', "input-file");
    Arg* arg4 = new args_types::StringArg('o', "output-file");

    parser.add(arg);
    parser.add(arg2);
    parser.add(arg3);
    parser.add(arg4);

    parser.parse(argc, argv);

}

