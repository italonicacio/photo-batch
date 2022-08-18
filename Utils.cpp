#include "Utils.h"

#include <algorithm>


namespace Utils
{
    std::string ToLower(std::string str)
    {
        std::transform(std::begin(str), std::end(str), std::begin(str), 
                        [](unsigned char c) { return std::tolower(c); });

        return str;

    }
   

    bool HasWhiteSpaces(const std::string& str)
    {
        return str.find(' ') != std::string::npos;
    }

    const std::string& GetInvalidChars()
    {
        static const std::string invalidCharacters = "\\/*?\"<>|:";
        return invalidCharacters;
    }

    bool HasInvalidChars(const std::string& str)
    {
        const bool bHasInvalidChars = (str.find_first_of(GetInvalidChars()) != std::string::npos);
        return bHasInvalidChars;
    }
}

