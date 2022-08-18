#pragma once

#include "Mode.h"

class ConvertMode final : public Mode
{

public:

    enum class Format
    {
        JPG,
        PNG
    };

    ConvertMode(const std::string& filter, const std::string& folder, Format fromFormat, Format toFormat, int quality = 50);

    const std::string& GetModeName() const override;

protected:
    void RunImpl() override;

private:
    Format m_FromFormat;
    Format m_ToFormat;
    int m_Quality;

};