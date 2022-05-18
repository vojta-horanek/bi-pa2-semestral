#ifndef TPOHB_RESULT_H
#define TPOHB_RESULT_H

#include <string>

/**
 * A result class. A result can either be success, without the error text,
 * or error, with the error text.
 */
struct Result {
    bool m_isError;
    std::string m_ErrorText;

    Result() = delete;

    static Result error(const std::string &errorText = "");

    static Result success();
};

#endif // TPOHB_RESULT_H
