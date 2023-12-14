#pragma once

#include <string>
#include <chrono>

namespace Utils
{
    using ClockT = std::chrono::high_resolution_clock;

    std::string ToLower(std::string str);
    bool HasWhiteSpaces(const std::string& str);

    const std::string& GetInvalidChars();

    bool HasInvalidChars(const std::string& str);

    std::string TimeConverter(const ClockT::duration& elapsedTime);
}




