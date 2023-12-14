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

    std::string TimeConverter(const ClockT::duration& elapsedTime)
    {
        std::chrono::hours hr = std::chrono::duration_cast<std::chrono::hours>(elapsedTime);
        std::chrono::minutes min = std::chrono::duration_cast<std::chrono::minutes>(elapsedTime - hr);
        std::chrono::seconds sec = std::chrono::duration_cast<std::chrono::seconds>(elapsedTime - hr - min);
        std::chrono::milliseconds ms = std::chrono::duration_cast<std::chrono::milliseconds>(elapsedTime - hr - min - sec);

        std::string time =  (hr.count() < 1 ? "" : std::to_string(hr.count()) + "hr ")      // Hour
                            + (min.count() < 1 ? "" : std::to_string(min.count()) + "min ") // Minutes
                            + (sec.count() < 1 ? "" : std::to_string(sec.count()) + "sec ") // Seconds
                            + std::to_string(ms.count()) + "ms";                            // Milliseconds
        
        return time;
    }

}

