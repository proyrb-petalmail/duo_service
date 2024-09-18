#pragma once

#include "debug.hpp"
#include "main.hpp"

#include <exception>
#include <string>

#define ERROR_INFORMATION(information) string("[") + GET_FILE_NAME(__FILE__) + COLON + to_string(__LINE__) + "] " + information

namespace NAMESPACE
{
    typedef enum
    {
        NONE_ERROR = 0,
        OPEN_ERROR = 1L << 0,
        READ_ERROR = 1L << 1,
        COPY_ERROR = 1L << 2,
        JSON_ERROR = 1L << 3,
        FIND_ERROR = 1L << 4,
        RANGE_ERROR = 1L << 5,
        CREATE_ERROR = 1L << 6,
    } error_type_enum;

    class error : public std::exception
    {
    private:
        error_type_enum type_enum;
        std::string type_name;
        std::string message;

    public:
        template <typename _message_type> error(const error_type_enum type, _message_type message);
        ~error();
        const char *what(void);
        const error_type_enum get_type_enum(void);
        const std::string &get_type_name(void);
        const std::string &get_message(void);
    };

    template <typename _message_type> error::error(const error_type_enum type_enum, _message_type message)
    {
        this->type_enum = type_enum;
        switch (this->type_enum)
        {
        case OPEN_ERROR:
        {
            this->type_name = "open_error";
        }
        break;
        case READ_ERROR:
        {
            this->type_name = "read_error";
        }
        break;
        case COPY_ERROR:
        {
            this->type_name = "copy_error";
        }
        break;
        case JSON_ERROR:
        {
            this->type_name = "json_error";
        }
        break;
        case FIND_ERROR:
        {
            this->type_name = "find_error";
        }
        break;
        case RANGE_ERROR:
        {
            this->type_name = "range_error";
        }
        break;
        case CREATE_ERROR:
        {
            this->type_name = "create_error";
        }
        break;
        default:
        {
            this->type_name = "null";
        }
        break;
        }
        this->message = message;
    }
} // namespace NAMESPACE
