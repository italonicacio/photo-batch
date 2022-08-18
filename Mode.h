#pragma once

#include <string>
#include <memory>
#include <filesystem>
#include <vector>

class Mode
{
public:
    Mode(const std::string& filter, const std::string& folder);

    const std::string& GetFilter() const;
    const std::string& GetFolder() const;

    virtual const std::string& GetModeName() const = 0;

    void Run();

protected:
    virtual void RunImpl() = 0;

    std::vector<std::filesystem::path> GetFiles(const std::filesystem::path& extension = "") const;


private:
    std::string m_Filter;
    std::string m_Folder;
};




