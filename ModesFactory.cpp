#include <iostream>
#include <filesystem>
#include <algorithm>


#include "ModesFactory.h"
#include "Args.h"
#include "ArgumentParser.h"
#include "RenameMode.h"
#include "ConvertMode.h"
#include "ResizeMode.h"
#include "ScaleMode.h"
#include "Utils.h"


std::unique_ptr<Mode> CreateModeFactory(const ArgumentParser& argParser)
{
    // Ler as flags que o ArgumentParser identificou
    const bool bRenameMode = argParser.GetFlag(Args::Flags::Rename);
    const bool bConvertMode = argParser.GetFlag(Args::Flags::Convert);
    const bool bResizeMode = argParser.GetFlag(Args::Flags::Resize);
    const bool bScaleMode = argParser.GetFlag(Args::Flags::Scale);

    
    // Verificar se somente um modo do PhotoBatch está ativo

    // Posso utilizar o if abaixo, porem não é escalavel
    // if (! (bRenameMode ^ bConvertMode ^ bResizeMode ^ bScaleMode))

    // Está forma é mais escalavel, pois https://www.realtimerendering.com/raytracing/Ray%20Tracing%20in%20a%20Weekend.pdfa medida que for adicionando novos modos ele não tem problema como o if
    const std::array<bool, 4> modes = {bRenameMode, bConvertMode, bResizeMode, bScaleMode};
    const std::ptrdiff_t numActiveModes = std::count(std::begin(modes), std::end(modes), true);

    if(numActiveModes != 1)
    {
        throw std::invalid_argument("Somente um modo pode estar ativo!");
    }

    // Validar a pasta passada como a opção Folder
    const std::string folder = argParser.GetOptionAs<std::string>(Args::Options::Folder);

    if(folder.empty())
    {
        throw std::invalid_argument("A pasta não pode estar em branco! ");
    }

    if(!std::filesystem::exists(folder))
    {
        throw std::invalid_argument("A pasta informada não existe!");
    }

    // Validar se o filtro é uma string valida
    const std::string filter = argParser.GetOptionAs<std::string>(Args::Options::Filter);

    if(!filter.empty() && Utils::HasInvalidChars(filter))
    {
        throw std::invalid_argument("O filtro não pode conter " + Utils::GetInvalidChars());
    }

    // Validar o modo resize
    if(bResizeMode)
    {
        int width = 0;
        int height = 0;
        const int quality = argParser.GetOptionAs<int>(Args::Options::Quality);
        
        try
        {
            width = argParser.GetOptionAs<int>(Args::Options::Width);
            height = argParser.GetOptionAs<int>(Args::Options::Height);


        }catch(const std::invalid_argument&)
        {
            throw std::invalid_argument("O valor informado para Width ou Height não são números válidos!");
        }


        // No modo resize o comprimento e altura devem ser >0

        if(width <= 0 || height <= 0)
        {
            throw std::invalid_argument("Width e Height devem ser maiores que zero!");
        }

        if(filter.empty())
        {
            throw std::invalid_argument("Filter não pode estar em branco no modo Resize!");
        }

        if(quality > 100 || quality == 0)
        {
            throw std::invalid_argument("Quality deve ser um número entre 1 e 100!");
        }

        if(quality > 0)
        {
            return std::make_unique<ResizeMode>(filter, folder, width, height, quality);
        }

        return std::make_unique<ResizeMode>(filter, folder, width, height);

    }

    // Validar o modo scale
    if(bScaleMode)
    {
        float amount  = 0.0f;

        try
        {
            amount  = argParser.GetOptionAs<float>(Args::Options::Amount);
        }
        catch(const std::invalid_argument&)
        {
            throw std::invalid_argument("O valor informado para Amount não é um número válido!");
        }
        

        // No modo scala o amount deve ser maior que zero

        if(amount <= 0.0f)
        {
            throw std::invalid_argument("Amount deve ser maior que zero!");
        }

        if(filter.empty())
        {
            throw std::invalid_argument("Filter não pode estar em branco no modo Scale!");
        }

        return std::make_unique<ScaleMode>(filter, folder, amount);
    }

    // Validar o nome Rename
    if(bRenameMode)
    {

        int startNumber = -1;
        
        try
        {
            startNumber = argParser.GetOptionAs<int>(Args::Options::StartNumber);
        }
        catch(const std::invalid_argument)
        {
            throw std::invalid_argument("O valor informado para StartNumber não é um número válido!");
        }
        
        std::string prefix = argParser.GetOptionAs<std::string>(Args::Options::Prefix);

        if(startNumber < 0)
        {
            throw std::invalid_argument("StartNumber deve ser maior ou igual a zero!");
        }

        
        if(prefix.empty() || Utils::HasInvalidChars(prefix) )
        {
            throw std::invalid_argument("Prefix não pode estar em branco e não pode conter os caracters " + Utils::GetInvalidChars());
        }

        return std::make_unique<RenameMode>(filter, folder, prefix, startNumber);
    }

    // Validar o modo Convert
    if(bConvertMode)
    {
        const std::string from = argParser.GetOptionAs<std::string>(Args::Options::From);
        const std::string to = argParser.GetOptionAs<std::string>(Args::Options::To);
        const int quality = argParser.GetOptionAs<int>(Args::Options::Quality);

        const std::map<std::string, ConvertMode::Format> convertOptions = {
            {"jpg", ConvertMode::Format::JPG},
            {"png", ConvertMode::Format::PNG}
        };

        if(from.empty())
        {
            throw std::invalid_argument("From não pode estar em branco!");
        }

        if(to.empty())
        {
            throw std::invalid_argument("To não pode estar em branco!");
        }

        if(quality > 100 || quality == 0)
        {
            throw std::invalid_argument("Quality deve ser um número entre 1 e 100!");
        }


        
        

        const bool bIsFromValid = convertOptions.find(from) != convertOptions.end(); 
        const bool bIsToValid = convertOptions.find(to) != convertOptions.end();  

        if(!bIsFromValid || !bIsToValid)
        {
            throw std::invalid_argument("From e To devem ser jpg ou png!");
        }

        if(from == to)
        {
            throw std::invalid_argument("From e To devem ser diferentes!");
        }

        if(quality > 0)
        {
            return std::make_unique<ConvertMode>(filter, folder, convertOptions.at(from), convertOptions.at(to), quality); 
        }

        return std::make_unique<ConvertMode>(filter, folder, convertOptions.at(from), convertOptions.at(to));

    }

    return nullptr;
}