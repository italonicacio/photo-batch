#pragma once

#include <string>

namespace Utils
{

    std::string ToLower(std::string str);
    bool HasWhiteSpaces(const std::string& str);

    const std::string& GetInvalidChars();

    bool HasInvalidChars(const std::string& str);

}




