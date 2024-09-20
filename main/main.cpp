#include "main.hpp"
#include "argument.hpp"
#include "cmdline.hpp"
#include "debug.hpp"
#include "error.hpp"
#include "json.hpp"

#include <fstream>
#include <signal.h>
#include <sys/wait.h>
#include <unistd.h>

/* using namespace */
using namespace std;
using namespace cmdline;
using namespace configor;
using namespace service;

static void signal_handle(int signal) { Debug_Notice("switch process successfully"); }

int main(const int arguments_count, char **const arguments_value)
{
    signal(SIGINT, signal_handle);

    /* parse arguments */
    parser arguments_parser;
    arguments_parser.add<string>(Argument_Pipe, Argument_Pipe_Short, Argument_Pipe_Refer, Argument_Pipe_Need, Argument_Pipe_Default); /* add pipe */
    arguments_parser.parse_check(arguments_count, arguments_value); /* execute checking */
    Debug_Log("--" Argument_Pipe "=" << arguments_parser.get<string>(Argument_Pipe));

    while (true)
    {
        static int status = 0;
        int fork_id = fork();
        if (0 == fork_id)
        {
            switch (status)
            {
            case 0:
            {
                Debug_Log("desktop process");
                if (0 != execlp("./desktop", "desktop", nullptr))
                {
                    perror("./desktop");
                    exit(-1);
                }
                break;
            }
            case 1:
            {
                Debug_Log("app process");

                /* get pipe */
                ifstream file_stream(arguments_parser.get<string>(Argument_Pipe)); /* open pipe json */
                if (false == file_stream.is_open())
                {
                    Debug_Error(file_stream.rdstate());
                    exit(-1);
                }

                json::value pipe_json;                /* configor of desktop */
                file_stream >> json::wrap(pipe_json); /* read json file */
                Debug_Log(pipe_json["app"].get<string>());
                file_stream.close();

                if (0 != execlp(pipe_json["app"].get<string>().data(), "app", pipe_json["argument"].get<string>().data(), nullptr))
                {
                    perror("app");
                    exit(-1);
                }
                break;
            }
            }
        }
        else
        {
            Debug_Notice("child process id " << fork_id);
            int childprocess_return_value;
            wait(&childprocess_return_value);
            Debug_Notice("child process return " << childprocess_return_value);

            switch (status)
            {
            case 0:
            {
                status = 1;
                break;
            }
            case 1:
            {
                status = 0;
                break;
            }
            }
        }
    }
}