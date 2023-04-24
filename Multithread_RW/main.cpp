/*
 * main.cpp
 *
 * Descrição: Arquivo principal para a execução da atividade de multithread dos escritores/leitores.
 *
 * Autores: José Antônio Cidral, Vinícius de Carvalho Monteiro Longo
 * Data: 18/04/2023
 *
 */
#include "includes/classes.hpp"

int main()
{
    Biblioteca bib;
    std::vector<std::thread> escritores;
    std::vector<std::thread> leitores;

    for (int i = 0; i < NUM_ESCRITORES; i++)
    {
        escritores.emplace_back(&Biblioteca::escritor, &bib, randStrRowFromTxt("txtFiles/escritores.txt"), i + 1);
    }
    for (int i = 0; i < NUM_LEITORES; i++)
        escritores.emplace_back(&Biblioteca::leitor, &bib, randStrRowFromTxt("txtFiles/nomes.txt"), i + 1);

    for (auto &thread : escritores)
        thread.join();
    for (auto &thread : leitores)
        thread.join();

    return 0;
}