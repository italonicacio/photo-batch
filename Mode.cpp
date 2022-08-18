#include <iostream>
#include <chrono>

#include "Mode.h"
#include "Utils.h"
#include "Args.h"



Mode::Mode(const std::string& filter, const std::string& folder)
    : m_Filter{filter}
    , m_Folder{folder}
{}

const std::string& Mode::GetFilter() const
{
    return m_Filter;
}

const std::string& Mode::GetFolder() const
{
    return m_Folder;
}

void Mode::Run()
{
    using ClockT = std::chrono::high_resolution_clock;

    ClockT::time_point starTime = ClockT::now();
    RunImpl();

    ClockT::time_point endTime = ClockT::now();
    
    ClockT::duration elapsedTime = endTime - starTime;
    std::chrono::milliseconds elapsedTimeMs = std::chrono::duration_cast<std::chrono::milliseconds>(elapsedTime);

    std::cout << GetModeName() << "Operação finalizada em " << elapsedTimeMs.count() << " ms."<< std::endl;
    
}

std::vector<std::filesystem::path> Mode::GetFiles(const std::filesystem::path& extension) const
{
    std::vector<std::filesystem::path> files;
    int numSkippedFiles = 0;

    // Coletar todos os arquivos que correspondem ao filtro especificado

    for(const std::filesystem::directory_entry& entry : std::filesystem::directory_iterator(GetFolder()))
    {
        const bool bIsFile = std::filesystem::is_regular_file(entry.path());
        const bool bMatchFilter = GetFilter().empty() 
                                || (Utils::ToLower(entry.path().string()).find(GetFilter()) != std::string::npos);

        const bool bMatchExtension = extension.empty() 
                                   || (Utils::ToLower(entry.path().extension().string()) == Utils::ToLower(extension.string()));

        if (bIsFile && bMatchFilter && bMatchExtension)
        {
            files.push_back(entry.path());
        }else{
            numSkippedFiles++;
        }
    
    }

    std::cout << GetModeName() << "Número de arquivos encontrados: " << files.size() << std::endl;
    std::cout << GetModeName() << "Número de arquivos ignorados  : " << numSkippedFiles << std::endl;

    return files;
}






// void ValidadeArguments(const ArgumentParser& argParser)
// {
//     // Ler as flags que o ArgumentParser identificou
//     const bool bRenameMode = argParser.GetFlag(Args::Flags::Rename);
//     const bool bConvertMode = argParser.GetFlag(Args::Flags::Convert);
//     const bool bResizeMode = argParser.GetFlag(Args::Flags::Resize);
//     const bool bScaleMode = argParser.GetFlag(Args::Flags::Scale);

    
//     // Verificar se somente um modo do PhotoBatch está ativo

//     // Posso utilizar o if abaixo, porem não é escalavel
//     // if (! (bRenameMode ^ bConvertMode ^ bResizeMode ^ bScaleMode))

//     // Está forma é mais escalavel, pois a medida que for adicionando novos modos ele não tem problema como o if
//     const std::array<bool, 4> modes = {bRenameMode, bConvertMode, bResizeMode, bScaleMode};
//     const std::ptrdiff_t numActiveModes = std::count(std::begin(modes), std::end(modes), true);

//     if(numActiveModes != 1)
//     {
//         throw std::invalid_argument("Somente um modo pode estar ativo!");
//     }

//     // Validar a pasta passada como a opção Folder
//     const std::string folder = argParser.GetOptionAs<std::string>(Args::Options::Folder);

//     if(folder.empty())
//     {
//         throw std::invalid_argument("A pasta não pode estar em branco! ");
//     }

//     if(!std::filesystem::exists(folder))
//     {
//         throw std::invalid_argument("A pasta informada não existe!");
//     }

//     // Validar se o filtro é uma string valida
//     const std::string filter = argParser.GetOptionAs<std::string>(Args::Options::Filter);

//     if(!filter.empty() && HasInvalidChars(filter))
//     {
//         throw std::invalid_argument("O filtro não pode conter " + GetInvalidChars());
//     }

//     // Validar o modo resize
//     if(bResizeMode)
//     {
//         int width = 0;
//         int height = 0;

//         try
//         {
//             width = argParser.GetOptionAs<int>(Args::Options::Width);
//             height = argParser.GetOptionAs<int>(Args::Options::Height);

//         }catch(const std::invalid_argument&)
//         {
//             throw std::invalid_argument("O valor informado para Width ou Height não são números válidos!");
//         }


//         // No modo resize o comprimento e altura devem ser >0

//         if(width <= 0 || height <= 0)
//         {
//             throw std::invalid_argument("Width e Height devem ser maiores que zero!");
//         }

//         if(filter.empty())
//         {
//             throw std::invalid_argument("Filter não pode estar em branco no modo Resize!");
//         }

//     }

//     // Validar o modo scale
//     if(bScaleMode)
//     {
//         float amount  = 0.0f;

//         try
//         {
//             amount  = argParser.GetOptionAs<float>(Args::Options::Amount);
//         }
//         catch(const std::invalid_argument&)
//         {
//             throw std::invalid_argument("O valor informado para Amount não é um número válido!");
//         }
        

//         // No modo scala o amount deve ser maior que zero

//         if(amount <= 0.0f)
//         {
//             throw std::invalid_argument("Amount deve ser maior que zero!");
//         }

//         if(filter.empty())
//         {
//             throw std::invalid_argument("Filter não pode estar em branco no modo Scale!");
//         }
//     }

//     // Validar o nome Rename
//     if(bRenameMode)
//     {

//         int startNumber = -1;
        
//         try
//         {
//             startNumber = argParser.GetOptionAs<int>(Args::Options::StartNumber);
//         }
//         catch(const std::invalid_argument)
//         {
//             throw std::invalid_argument("O valor informado para StartNumber não é um número válido!");
//         }
        
//         std::string prefix = argParser.GetOptionAs<std::string>(Args::Options::Prefix);

//         if(startNumber < 0)
//         {
//             throw std::invalid_argument("StartNumber deve ser maior ou igual a zero!");
//         }

        
//         if(prefix.empty() || HasInvalidChars(prefix) )
//         {
//             throw std::invalid_argument("Prefix não pode estar em branco e não pode conter os caracters " + GetInvalidChars());
//         }

//         return std::make_unique<RenameMode>(filter, folder, prefix, startNumber);
//     }

//     // Validar o modo Convert
//     if(bConvertMode)
//     {
//         const std::string from = argParser.GetOptionAs<std::string>(Args::Options::From);
//         const std::string to = argParser.GetOptionAs<std::string>(Args::Options::To);

//         if(from.empty())
//         {
//             throw std::invalid_argument("From não pode estar em branco!");
//         }

//         if(to.empty())
//         {
//             throw std::invalid_argument("To não pode estar em branco!");
//         }


//         const std::array<std::string, 2> convertOptions = {"jpg", "png"};

//         const bool bIsFromValid = std::find(std::begin(convertOptions), std::end(convertOptions), from) != std::end(convertOptions); 
//         const bool bIsToValid = std::find(std::begin(convertOptions), std::end(convertOptions), to) != std::end(convertOptions);  

//         if(!bIsFromValid || !bIsToValid)
//         {
//             throw std::invalid_argument("From e To devem ser jpg ou png!");
//         }

//         if(from == to)
//         {
//             throw std::invalid_argument("From e To devem ser diferentes!");
//         }

//     }
// }