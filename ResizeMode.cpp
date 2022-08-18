#include <iostream>

#include "ResizeMode.h"
#include "Utils.h"

// #define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

// #define STB_IMAGE_WRITE_IMPLEMENTATION

#include <stb_image_write.h>

// #define STB_IMAGE_RESIZE_IMPLEMENTATION
#include <stb_image_resize.h>


ResizeMode::ResizeMode(const std::string& filter, const std::string& folder, int width, int height, int quality)
    : Mode{ filter, folder }
    , m_Width{ width }
    , m_Height{ height }
    , m_Quality{ quality }
{}

const std::string& ResizeMode::GetModeName() const
{
    static const std::string ResizeModeName = "[Redimensionar]: ";
    return ResizeModeName;
}

void ResizeMode::ResizeImage(const std::filesystem::path& filepath, int newWidth, int newHeight) const
{
    // Ler a imagem
    // Redimensionar em memória
    // Escrevera imagem

    int inputWidth = 0;
    int inputHeight = 0;
    int inputNumComp = 0;

    const int numCompReq = 4;

    if(unsigned char* inputData = stbi_load(filepath.string().c_str(), &inputWidth, &inputHeight, &inputNumComp, numCompReq))
    {
        const int numOutputPixels = newWidth * newHeight * numCompReq;

        // unsigned char == std::uint8_t
        std::vector<std::uint8_t> outputData(numOutputPixels, 0);

        const int resizeResult = stbir_resize_uint8(    inputData, inputWidth, inputHeight, 0,
                                                        outputData.data(), newWidth, newHeight, 0,
                                                        numCompReq
                                                    );

        if(resizeResult == 1)
        {
            int writeResult = 1;

            const std::filesystem::path extension = filepath.extension();
            if( Utils::ToLower(extension.string()) == ".jpg" )
            {
                
                writeResult = stbi_write_jpg(   filepath.string().c_str(), 
                                                newWidth, newHeight, numCompReq, 
                                                outputData.data(), m_Quality 
                                            );

            } else if( Utils::ToLower(extension.string()) == ".png" ) {
                
                 writeResult = stbi_write_png(   filepath.string().c_str(), 
                                                newWidth, newHeight, numCompReq, 
                                                outputData.data(), 0 
                                            );

            } else {

                std::cerr << GetModeName() << "Formato não suportado " << filepath << std::endl;

            }

            if (writeResult == 0)
            {
                std::cerr << GetModeName() << "Erro ao escrever " << filepath << std::endl;
            }


        } else {   
            std::cerr << GetModeName() << "Erro ao redimensionar " << filepath << std::endl;
        }

        stbi_image_free(inputData);

    } else {
        std::cerr << GetModeName() << "Erro ao carregar " << filepath << std::endl;
    }
}

void ResizeMode::RunImpl()
{
    std::cout << GetModeName() << "Modo        : Redimensionar" << std::endl;
    std::cout << GetModeName() << "Pasta       : " << GetFolder() << std::endl;
    std::cout << GetModeName() << "Filtro      : " << GetFilter() << std::endl;
    std::cout << GetModeName() << "Comprimento : " << m_Width << std::endl;
    std::cout << GetModeName() << "Altura      : " << m_Height << std::endl;

    if(m_Width > 0 && m_Height > 0)
    {

        for(const std::filesystem::path& filepath : GetFiles())
        {
            std::cout << GetModeName() << "Redimensionando " << filepath << std::endl;
            ResizeImage(filepath, m_Width, m_Height);


        }
    }

}

