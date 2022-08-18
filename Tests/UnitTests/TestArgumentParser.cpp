#include <gtest/gtest.h>

#include <ArgumentParser.h>

#include <array>

// Depois Escrever mais testes unitarios da classe
// Depois de terminado o programa


TEST(TestArgumentParser, RegisterFlag)
{   
    // Criar um objeto ArgumentParser
    ArgumentParser argParser;
    
    std::string flag("MyFlag");

    // Verificar o estado antes da operação
    EXPECT_FALSE(argParser.IsFlagRegistered(flag));

    // Registrar a flag
    // Chamar a função sendo testada
    argParser.RegisterFlag(flag);

    // Verficar o estado depois da operação
    EXPECT_TRUE(argParser.IsFlagRegistered(flag));
}

TEST(TestArgumentParser, RegisterFlag_Whitespace)
{   
    ArgumentParser argParser;
    
    std::string flag("My Flag");

    argParser.RegisterFlag(flag);

    EXPECT_FALSE(argParser.IsFlagRegistered(flag));
}

TEST(TestArgumentParser, RegisterOption)
{
    ArgumentParser argParser;

    std::string option_name("MyOption");

    argParser.RegisterOption(option_name);

    EXPECT_TRUE(argParser.IsOptionRegistered(option_name));
}

TEST(TestArgumentParser, RegisterOption_Whitespace)
{
    ArgumentParser argParser;

    std::string option_name("My Option");

    argParser.RegisterOption(option_name);

    EXPECT_FALSE(argParser.IsOptionRegistered(option_name));
}

TEST(TestArgumentParser, Parse)
{
    ArgumentParser argParser;

    std::array<const char*, 5> args = 
    {
        "TestArgumentParser",
        "--flag",
        "--string=AaBbCcDd",
        "--number=42",
        "--float=4.2"
    };

    argParser.RegisterFlag("flag");
    argParser.RegisterOption("string");
    argParser.RegisterOption("number");
    argParser.RegisterOption("float");

    argParser.Parse(static_cast<int>(args.size()), args.data());

    EXPECT_FALSE(argParser.GetFlag("unregisteredFlag"));
    EXPECT_TRUE(argParser.GetFlag("flag"));

    // Manter tudo como minusculo por hora é algo bom, mas pode e deve ser modificado no futuro de acordo com as necessidades
    EXPECT_EQ(argParser.GetOptionAs<std::string>("string"), "aabbccdd");

    EXPECT_EQ(argParser.GetOptionAs<int>("number"), 42);

    EXPECT_EQ(argParser.GetOptionAs<float>("float"), 4.2f);

}

TEST(TestArgumentParser, Parse_InvalidArguments)
{
    ArgumentParser argParser;

    argParser.Parse(0, nullptr);
    argParser.Parse(42, nullptr);
    argParser.Parse(-1, nullptr);
}