#include "ArgumentParser.h"
#include "Utils.h"

#include <iostream>

// Passagem de string por valor, pq vai ser necessario fazer uma copia
// Então ele deixou para o sistema lidar com isso e alterar da forma que ele achar melhor a string


void ArgumentParser::RegisterFlag(const std::string& flag)
{
    if(!flag.empty() && !Utils::HasWhiteSpaces(flag))
    {
        m_Flags[flag] = false;
    }
}

void ArgumentParser::RegisterOption(const std::string& option)
{
    if(!option.empty() && !Utils::HasWhiteSpaces(option))
    {
        m_Options[option] = "";
    }
}

bool ArgumentParser::IsFlagRegistered(const std::string& flag) const
{
    if(!flag.empty())
    {
        return m_Flags.count(flag) == 1;
    }

    return false;
}

bool ArgumentParser::IsOptionRegistered(const std::string& option) const
{
    if(!option.empty())
    {
        return m_Options.count(option) == 1;
    }

    return false;
}

bool ArgumentParser::GetFlag(const std::string& flag) const
{   
    if(!flag.empty())
    {
        auto flagIt = m_Flags.find(flag);
        if(flagIt != std::end(m_Flags))
        {
            return flagIt->second;
        }
    }

    return false;
}

const std::string& ArgumentParser::GetOption(const std::string& option) const
{

    if(!option.empty())
    {

        auto optionIt = m_Options.find(option);
        if(optionIt != std::end(m_Options))
        {
            return optionIt->second;   
        }
    }

    static std::string EmptyOption = "";
    return EmptyOption;

}

float ArgumentParser::GetOptionAsFloat(const std::string& option) const
{
    const std::string& optionValue = GetOption(option);

    if(!optionValue.empty())
    {
        return std::stof(optionValue);
    }

    return -1;
}

int ArgumentParser::GetOptionAsInt(const std::string& option) const
{
    const std::string& optionValue = GetOption(option);

    if(!optionValue.empty())
    {
        return std::stoi(optionValue);
    }

    return -1;
}

void ArgumentParser::SetHelpMessage(const std::string& helpMessage)
{
    m_HelpMessage = helpMessage;
}

const std::string& ArgumentParser::GetHelpMessage() const
{
    return m_HelpMessage;
}

void ArgumentParser::Parse(int argc, const char* argv[])
{
    if(argc > 1 && argv != nullptr)
    {
        for(int i = 1; i < argc; i++)
        {
            // Diferente do programa original, onde dava problema com o folder   
            std::string arg = argv[i];
            


            if(arg.length() >= 3)
            {
                // Os argumentos tem que ter pelo menos 3 caracteres
                // os "--" e pelo menos um terceiro caracter
                if(arg[0] == '-' && arg[1] == '-')
                {
                    // Primeiro, vamos remover os "--" iniciais

                    arg = arg.substr(2);
                    
                    // Vamos verificar se é uma opção, se sim fazer o ToLower apenas para a parte inicial

                    if(arg.find_first_of('=') != std::string::npos)
                    {
                            // É uma opção
                            const size_t equalSingPos = arg.find('=');
                            if(equalSingPos != std::string::npos)
                            {
                                // Dividir a opção em chave e valor
                                std::string optionName = arg.substr(0, equalSingPos);
                                std::string optionValue = arg.substr(equalSingPos + 1);
                                
                                optionName = Utils::ToLower(optionName);

                                // Modificar isso para Args::Options::Folder
                                if(!(optionName == "folder"))
                                {
                                    optionValue = Utils::ToLower(optionValue);
                                }

                                auto optionIt = m_Options.find(optionName);
                                if(optionIt != std::end(m_Options))
                                {
                                    // Achamos uma opção registrada
                                    optionIt->second = optionValue;
                                }
                            }
                        
                    }else{

                        arg = Utils::ToLower(arg);
                        // É uma flag
                        auto flagIt = m_Flags.find(arg);
                        if(flagIt != std::end(m_Flags))
                        {    
                            flagIt->second = true;
                        }
                    }
                }
            }
        }
    }
}