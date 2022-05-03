#include "Result.h"

Result Result::error(const std::string &errorText) {
    return {true, errorText};
}

Result Result::success() {
    return {false};
}
