/*
 * funcoes.hpp
 *
 * Descrição: Este arquivo contém a declaração da função randStrRowFromTxt.
 *
 * Autores: José Antônio Cidral, Vinícius de Carvalho Monteiro Longo
 * Data: 16/04/2023
 *
 */

#ifndef FUNCOES_H
#define FUNCOES_H

#include <iostream>
#include <fstream>
#include <random>

std::string randStrRowFromTxt(std::string txt_filename)
{
    /*
    Lê um arquivo texto e retorna uma std::string contendo uma linha randomica do arquivo texto.
    */

    // Open the file
    std::ifstream file(txt_filename);
    if (!file)
    {
        std::cerr << "Error opening file" << std::endl;
        return "";
    }

    // Get the number of lines in the file
    int num_lines = 0;
    std::string line;
    while (std::getline(file, line))
        num_lines++;

    // Generate a random line number
    std::random_device rd;
    std::mt19937 rng(rd());
    std::uniform_int_distribution<int> uni(1, num_lines);
    int random_line_num = uni(rng);

    // Go back to the beginning of the file
    file.clear();
    file.seekg(0, std::ios::beg);

    // Get the random line
    for (int i = 0; i < random_line_num; ++i)
        std::getline(file, line);

    return line;
}

#endif