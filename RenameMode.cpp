#include <iostream>
#include <filesystem>
#include <vector>

#include "RenameMode.h"
#include "Utils.h"


RenameMode::RenameMode(const std::string& filter, const std::string& folder, const std::string& prefix, int startNumber)
    : Mode{ filter, folder }
    , m_Prefix{ prefix }
    , m_startNumber{ startNumber }
{}

const std::string& RenameMode::GetModeName() const
{
    static const std::string RenameModeName = "[Renomear]: ";
    return RenameModeName;
}

void RenameMode::RunImpl()
{
    std::cout << GetModeName() << "Modo           : Renomear" << std::endl;
    std::cout << GetModeName() << "Pasta          : " << GetFolder() << std::endl;
    std::cout << GetModeName() << "Filtro         : " << GetFilter() << std::endl;
    std::cout << GetModeName() << "Prefixo        : " << m_Prefix << std::endl;
    std::cout << GetModeName() << "Número Inicial : " << m_startNumber << std::endl;

    

    

    // Iniciar o processo de renomear os arquivos


    // "Absolute Zero.jpg" -> "PrefixN,jpg"
    int currentNumber = m_startNumber;
    for(const std::filesystem::path& filepath : GetFiles())
    {
        const std::filesystem::path extension = filepath.extension();
        const std::string newFileName = m_Prefix + std::to_string(currentNumber) + extension.string();

        std::filesystem::path newFilepath = filepath;
        newFilepath.replace_filename(newFileName);

            
        try
        {
             std::filesystem::rename(filepath, newFilepath);

             std::cout << GetModeName() << filepath << " -> " << newFilepath << std::endl;
        }
        catch(const std::exception& exception)
        {
            std::cerr << GetModeName() << "Erro ao renomear " << filepath << ": " << exception.what() << std::endl;
        }
        
       
        // std::cout << GetModeName() << filepath << " -> " << newFilepath << std::endl;

        

        currentNumber++;
    }   
}