# Photo Batch
 
Photo Batch é um software de manipulação de imagens em lote que foi desenvolvido durante o curso de [Desenvolvimento de Projetos em C++](https://www.udemy.com/course/desenvolvimento-de-projetos-com-cpp/).
 
## Funcionalidades
 
Toda funcionalidade do Photo Batch tem duas opções padrão, um filtro e o diretório.
O filtro pode ser qualquer coisa, por exemplo:
Temos uma pasta com fotos de diversos animais e você apenas quer renomear as fotos com nome "gato", “gato” é o filtro.
 
 
Estrutura básica:
```bash
        ./PhotoBatch --<functionality> --Filter=<filter> --Folder=<path to your images> args<depends of functionality>
```
 
Abaixo temos as funcionalidades que atualmente estão implementadas no Photo Batch:
 
* Renomear:
   * Renomeia vários arquivos com base no filtro.
      ```bash
        ./PhotoBatch --Rename --Filter=<filter> --Folder=<folder> --Prefix=<new_name> --StartNumber=<integer>
      ```
* Converter:
   * Converte arquivos de uma extensão para outra
   Formatos aceitos: jpg png
     ```bash
        ./PhotoBatch --Convert --Filter=<filter> --Folder=<folder> --From=<.extension> --To=<.extension> --Quality<Optional: Number between 1 and 100>
     ```
 
* Redimensionar:
   * Redimensiona várias imagens a partir da altura e largura.
     ```bash
        ./PhotoBatch --Resize --Filter=<filter> --Folder=<folder> --Width=<integer> --Height=<integer> --Quality<Optional: Number between 1 and 100>
     ```
 
* Escalar:
   * Escala imagens a partir de um único número.
     ```bash
        ./PhotoBatch --Scale --Filter=<filter> --Folder=<folder> --Amount<number greater than 0>
     ```
 
## Adições Futuras
 
* Testes unitários para todas as classes.
* Paralelismo.
* Novos modos.
  
 

