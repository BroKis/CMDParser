#include "args_parse/args.hpp"
#include "args_parse/utils.hpp"
#include "args_parse/single_arg.hpp"
#include "directory_and_pool/thread_pool.hpp"
#include "directory_and_pool/directory_file.hpp"
#include "directory_and_pool/executor.hpp"


int main(int argc, const char** argv)
{
    args_parser::ArgsParser parser;
    args_validator::NormalParserValidator<std::string> validator;
    parser.SetValidator(&validator);

    single_arg::SingleArgument<int, int> threadArg = { 't', "thread", true };
    args_validator::InRangeValidator<int> validator1{ 0,26 };
    threadArg.setValidator(&validator1);

    single_arg::SingleArgument<std::string> pathArg = { 'p', "path", true };
    args_validator::NormalPathValidator<std::string> validator2{};
    pathArg.setValidator(&validator2);

    single_arg::SingleArgument<user_types::ChronoCloack, std::string> debugSleep{ 'd',"debug-sleep",true };
    args_validator::NormalChronoValidator<std::string> chronoValidator{};
    debugSleep.setValidator(&chronoValidator);

    parser.add(&threadArg);
    parser.add(&pathArg);
    parser.add(&debugSleep);

    if (const auto result = parser.parse(argc, argv); result.isOk())
    {
        thread_pool::ThreadPool pool(threadArg.GetValue());
        pool.setDebugSleep(debugSleep.GetValue().GetMicroseconds());
        directory::Directory directory{ pathArg.GetValue()};
        pool.enqueue([&pool, &directory]() {
            executor::execution_function(pool, directory);
            });
        pool.waitFinishTasks();
        directory.Show();

    

    }
}