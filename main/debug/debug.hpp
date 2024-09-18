#ifndef DEBUG_H
#define DEBUG_H

#include <string.h>
#define GET_FILE_NAME(x) (strrchr(x, '/') ? strrchr(x, '/') + 1 : x)
#define COLON            " "

#ifdef __cplusplus

#include <iostream>
using namespace std;
#define LOG_MESSAGE(...)                                                                                                                             \
    while (DEBUG)                                                                                                                                    \
    {                                                                                                                                                \
        clog << "[" << GET_FILE_NAME(__FILE__) << COLON << __LINE__ << "] " << __VA_ARGS__ << endl;                                                  \
        break;                                                                                                                                       \
    }
#define LOG_COMMAND(...)                                                                                                                             \
    while (DEBUG)                                                                                                                                    \
    {                                                                                                                                                \
        LOG_MESSAGE("command" COLON "\"" << __VA_ARGS__ << "\"");                                                                                    \
        break;                                                                                                                                       \
    }
#define LOG_COMMAND_RESULT(...)                                                                                                                      \
    while (DEBUG)                                                                                                                                    \
    {                                                                                                                                                \
        LOG_MESSAGE("command result" COLON << __VA_ARGS__);                                                                                          \
        break;                                                                                                                                       \
    }

#elif /* __cplusplus */

#include <stdio.h>
#define LOG_MESSAGE(message)                                                                                                                         \
    while (DEBUG)                                                                                                                                    \
    {                                                                                                                                                \
        printf("[%s" COLON "%d]%s\n", GET_FILE_NAME(__FILE__), __LINE__, message);                                                                   \
        break;                                                                                                                                       \
    }

#endif /* __cplusplus */

#endif /* DEBUG_H */