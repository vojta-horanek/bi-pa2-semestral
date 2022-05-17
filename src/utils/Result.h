#ifndef TPOHB_RESULT_H
#define TPOHB_RESULT_H

#include <string>

struct Result {
    bool isError;
    std::string errorText;

    Result() = delete;

    static Result error(const std::string &errorText = "");

    static Result success();
};

#endif // TPOHB_RESULT_H
