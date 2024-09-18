#include "error.hpp"
#include "debug.hpp"
#include "main.hpp"

using namespace std;

namespace NAMESPACE
{
    error::~error() {}

    const char *error::what() { return this->message.data(); }

    const error_type_enum error::get_type_enum(void) { return this->type_enum; }

    const string &error::get_type_name(void) { return this->type_name; }

    const string &error::get_message() { return this->message; }
} // namespace NAMESPACE
