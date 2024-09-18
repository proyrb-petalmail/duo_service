#include "main.hpp"
#include "cmdline.hpp"
#include "debug.hpp"
#include "error.hpp"
#include "json.hpp"

#include <fstream>
#include <sys/wait.h>
#include <unistd.h>

/* using namespace */
using namespace cmdline;
using namespace configor;
using namespace NAMESPACE;

/* pipe argument */
#define ARGUMENT_CONFIG         "pipe"
#define ARGUMENT_CONFIG_SHORT   'p'
#define ARGUMENT_CONFIG_REFER   "load pipe"
#define ARGUMENT_CONFIG_NEED    false
#define ARGUMENT_CONFIG_DEFAULT "pipe.json"

int main(int arguments_count, char *arguments_value[])
{
    /* parse arguments */
    parser arguments_parser;
    arguments_parser.add<string>(ARGUMENT_CONFIG, ARGUMENT_CONFIG_SHORT, ARGUMENT_CONFIG_REFER, ARGUMENT_CONFIG_NEED,
                                 ARGUMENT_CONFIG_DEFAULT);                               /* add config argument */
    arguments_parser.parse_check(arguments_count, arguments_value);                      /* check arguments */
    LOG_MESSAGE(ARGUMENT_CONFIG COLON << arguments_parser.get<string>(ARGUMENT_CONFIG)); /* output config value */

    while (true)
    {
        static int status = 0;
        if (fork() == 0)
        {
            switch (status)
            {
            case 0:
            {
                clog << "desktop process" << endl;

                execlp("./desktop", "", nullptr);
                perror("./desktop");
                exit(-1);
                break;
            }
            case 1:
            {
                clog << "app process" << endl;

                /* get configor */
                ifstream file_stream(arguments_parser.get<string>(ARGUMENT_CONFIG)); /* open config json */
                if (false == file_stream.is_open())
                {
                    LOG_COMMAND_RESULT(file_stream.rdstate()); /* output command result value */
                    return false;
                }

                configor::json::value pipe_json;                           /* configor of desktop */
                file_stream >> json::wrap(pipe_json);                      /* read json file */
                LOG_MESSAGE(pipe_json["app_relative_path"].get<string>()); /* output json content */

                execlp(pipe_json["app_relative_path"].get<string>().data(), "", nullptr);
                perror("app_relative_path");
                exit(-1);
                break;
            }
            }
        }
        else
        {
            clog << "parent process" << endl;

            int childprocess_return_value;
            wait(&childprocess_return_value);
            printf("child process return %d\n", childprocess_return_value);

            if (0 != childprocess_return_value)
            {
                exit(-1);
            }

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