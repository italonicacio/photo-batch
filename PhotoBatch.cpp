#include <iostream>
#include <iomanip>
#include <array>

#include "Args.h"
#include "ArgumentParser.h"
#include "Mode.h"
#include "ModesFactory.h"

static constexpr const char* HelpMessage = 
R"(PhotoBatch Help
[USO]: ./PhotoBatch --[Modo] [Opções...]
    Nessa Versão o PhotoBatch tem 4 modos de operação. Somente um modo pode estar ativo.
    Modos:
       --Rename  : Ativa o modo de renomear arquivos
       --Scale   : Ativa o modo de converter arquivos
       --Convert : Ativa o modo de redimensionar arquivos
       --Resize  : Ativa o modo de escalar 
       

As seguintes opções são comuns a todos os modos:
    --Folder : Especifica a pasta onde o PhotoBatch irá atuar
    --Filter : Especifica o filtro usado para selecionar arquivos

Opções do modo Rename:
    
    No modo Rename, cada arquivo selecionado será renomeado o formato 
    <Prefix>_<N>.<ext>, onde <Prefix> e <N> são especificados através de opções.
    <ext> é a extensão do arquivo que permanece inalterada.
    
    --Prefix=<Prefix> : Prefixo usado para renomear os arquivos
    --StartNumber=<N> : Número inicial a ser adicionado em cada arquivo que for renomeado

Opções do modo Convert:
    
    No modo Convert, cada arquivo selecionado será convertido do formato <form> para o formato <to>. 
    <form> e <to> não podem ser iguais. O nome do arquivo permanece inalterado.

    --From=<jpg|png> : Extensão de origem para conversão
    --To=<jpg|png>   : Extensão de destino para conversão

Opções do modo Resize:
    
    No modo Resize, cada arquivo selecionado será redimensionado para as dimensões
    especifficadas nas seguintes opções. Note que N >= 1.

    --Width=<N>  : Novo comprimento da imagem
    --Height=<N> : Nova altura da imagem

Opções do modo Scale:
    
    No modo Scale, cada arquivo selecionado será escalado uniformimente pelo
    fator especificado pelas seguintes opções. Note que N > 0 e será interpretado como um número real.

    --Amount=<N> : Fator de escala a ser aplicado em cada imagem selecionada.
    
Exemplos de uso:
    
    Renomear todos os arquivos da pasta "C:\Viagem" com a extens�o ".png" para Viagem_N.png, onde N come�a do 0

	    PhotoBatch --Rename --Folder="C:\Viagem" --Filter=".png" --StartNumber=0

    Redimensionar todos os arquivos na pasta "C:\Viagem" com a extens�o ".jpg" para o tamanho 500x500

        PhotoBatch --Resize --Folder="C:\Viagem" --Filter=".jpg" --Width=500 --Height=500

    Converter todos os arquivos da pasta "C:\Viagem" de "png" para "jpg"

        PhotoBatch --Convert --Folder="C:\Viagem" --From=png --To=jpg

    Reduzir o pela metade o tamanho de todos os arquivos "png" da pasta "C:\Viagem"

        PhotoBatch --Scale --Folder="C:\Viagem" --Filter=".png" --Amount=0.5

)";





// void ValidadeArguments(const ArgumentParser& argParser)
// {
    
// }

int main(int argc, const char* argv[])
{
    setlocale(LC_ALL, "pt_BR");
    setlocale(LC_NUMERIC, "en_US");

    ArgumentParser argParser;

    argParser.RegisterFlag(Args::Flags::Rename);
    argParser.RegisterFlag(Args::Flags::Convert);
    argParser.RegisterFlag(Args::Flags::Resize);
    argParser.RegisterFlag(Args::Flags::Scale);
    argParser.RegisterFlag(Args::Flags::Help);


    argParser.RegisterOption(Args::Options::Folder);
    argParser.RegisterOption(Args::Options::Filter);
    argParser.RegisterOption(Args::Options::Width);
    argParser.RegisterOption(Args::Options::Height);
    argParser.RegisterOption(Args::Options::Amount);
    argParser.RegisterOption(Args::Options::Prefix);
    argParser.RegisterOption(Args::Options::StartNumber);
    argParser.RegisterOption(Args::Options::From);
    argParser.RegisterOption(Args::Options::To);
    argParser.RegisterOption(Args::Options::Quality);

    argParser.SetHelpMessage(HelpMessage);

    argParser.Parse(argc, argv);

    if(argParser.GetFlag(Args::Flags::Help))
    {
        std::cout << argParser.GetHelpMessage() << std::endl;
    }else{
        try
        {
            if(std::unique_ptr<Mode> PhotoBatchMode = CreateModeFactory(argParser))
            {
                PhotoBatchMode->Run();
            }
        }
        catch(const std::exception& exception)
        {
            std::cerr << "Erro: " << exception.what() << std::endl;
            std::cerr << "Para mais informações rode o PhotoBatch com a flag --help!" << std::endl;

        } 
    }

   
    

    return 0;
}

