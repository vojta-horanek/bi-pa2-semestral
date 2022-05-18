#ifndef TPOHB_STRINGUTILS_H
#define TPOHB_STRINGUTILS_H

#include <string>

namespace StringUtils {
    // trim from start (in place)
    void ltrim(std::string &s);

    // trim from end (in place)
    void rtrim(std::string &s);

    // trim from both ends (in place)
    void trim(std::string &s);
}

#endif // TPOHB_STRINGUTILS_H
