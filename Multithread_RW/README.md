
# Readme

Esse é um código voltado para disciplina de Sistemas em Tempo Real. 
Autores: José Antônio Cidral, Vinícius de Carvalho Monteiro Longo
Data: 18/04/2023

Enunciado:
O problema clássico, chamado problema do leitor/escritor, diz respeito a qualquer situação em que uma estrutura de dados, banco de dados ou sistema de arquivos é lido e modificado de maneira concorrente. Enquanto a estrutura de dados está sendo escrita ou modificada é frequentemente necessário barrar a leitura de outros, a fim de evitar um leitor de interromper uma modificação em andamento e ler de forma inconsistente ou dados inválidos. Como no problema produtor/consumidor, a solução é assimétrica. Leitores e os escritores executam códigos diferentes antes de entrar na seção crítica. O restrições de sincronização são: 1. Qualquer número de leitores pode estar na seção crítica simultaneamente. 2. Os escritores devem ter acesso exclusivo à seção crítica. Em outras palavras, um escritor não pode entrar na seção crítica enquanto qualquer outra (leitor ou escritor) está lá, e enquanto o escritor estiver lá, nenhuma outra tarefa pode entrar. Resolva essa atividade para 3 escritores e 5 leitores.

## Requirements

-   CMake version 3.0 or higher
-   C++ compiler (supporting C++11 standard)
-   pthread library

## Building and running

1.  Download or clone the source code from the repository.
2.  Open the terminal or command prompt and navigate to the root directory of the project.
3.  Create a build directory and navigate to it.
4.  Run the command `cmake ..` to generate the build files.
5.  Run the command `make` to build the executable.
6.  To run the program, execute the command `./run_library`.

Before running the program, make sure that the `txtFiles` directory is present in the root directory of the project. If it is not present, copy it manually to the root directory.


