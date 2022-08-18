#pragma once

#include <map>
#include <string>

template<typename T>
struct tag { using type = T; };

/** 
 * Classe usada para ler os argumentos da linha de comando
 * 
 * Exemplo:
 *  ArgumentParser argParser;
 *  argParser.RegisterFlag("rename");
 *  argParser.Parser(argc, argv);
 *  argParser.GetFlag("rename")
 */ 
class ArgumentParser
{
public:

    //Registra um flag usada durante o parser
    void RegisterFlag(const std::string& flag);

    // Registra uma opção usada durante o parse
    void RegisterOption(const std::string& option);

    // Retornar se a flag está ou não registrada
    bool IsFlagRegistered(const std::string& flag) const;

    // Retornar se a opção está ou não registrada
    bool IsOptionRegistered(const std::string& option) const;

    // Obtem o valor de uma flag obtida durante o parse
    bool GetFlag(const std::string& flag) const;

    // O Codigo abaixo é apenas para padronizar o GetOption
    template<typename T>
    T GetOptionAs(const std::string& option) const { return GetOptionAs(option, tag<T>{}); }

    const std::string& GetOptionAs(const std::string& option, tag<std::string>) const { return GetOption(option); }

    float GetOptionAs(const std::string& option, tag<float>) const { return GetOptionAsFloat(option); }

    int GetOptionAs(const std::string& option, tag<int>) const { return GetOptionAsInt(option); }
    
    // Faz o parse da lista de argumento em argv
    void Parse(int argc, const char* argv[]);

    void SetHelpMessage(const std::string& helpMessage);

    const std::string& GetHelpMessage() const; 

private:
    std::map<std::string, bool> m_Flags;
    std::map<std::string, std::string> m_Options;
    std::string m_HelpMessage;

     // Obter o valor de uma opção lida durante o parse
    const std::string& GetOption(const std::string& option) const;

    // Obter o valor de uma opção convertida para float
    float GetOptionAsFloat(const std::string& option) const;

    // Obter o valor de uma opção convertida para int
    int GetOptionAsInt(const std::string& option) const;
};