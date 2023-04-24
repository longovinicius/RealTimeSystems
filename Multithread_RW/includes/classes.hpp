/*
 * classes.hpp
 *
 * Descrição: Este arquivo contém a declaração da classe Biblioteca.
 *
 * Autores: José Antônio Cidral, Vinícius de Carvalho Monteiro Longo
 * Data: 18/04/2023
 *
 */
#ifndef CLASSES_H
#define CLASSES_H

#include "funcoes.hpp"
#include "constantes.hpp"
#include <condition_variable>
#include <thread>
#include <vector>
#include <chrono>
#include <mutex>

class Biblioteca
{
    /*
        A Biblioteca é uma classe que possui em sua estrutura todos os componentes para
        a resolução do problema escritor/leitor.
    */
private:
    std::condition_variable cv_escritores, cv_leitores;
    std::string obra_atual;
    std::mutex mutex;
    bool escritor_on;
    bool livro_lido;
    int num_leitores_on, n_reacts;

public:
    Biblioteca()
    {
        obra_atual = "\0";
        escritor_on = false;
        livro_lido = false;
        num_leitores_on = 0;
    }

    void escritor(std::string nome, int id)
    {
        /*
        Função para as threads de escritor
        */
        while (true)
        {
            // Tenta obter acesso à zona crítica
            std::unique_lock<std::mutex> lock(mutex);
            cv_escritores.wait(lock, [this]()
                               { return num_leitores_on == 0 && !escritor_on; });

            // Entra na zona crítica (biblioteca)
            std::cout << "[Escritor " << id << "] " << nome << ":\n\tEntrou na biblioteca;" << std::endl;
            escritor_on = true;
            std::this_thread::sleep_for(std::chrono::milliseconds(450));

            // Desenvolve um texto novo
            std::string obra_antiga = obra_atual;
            obra_atual = randStrRowFromTxt("txtFiles/citacoes.txt");

            // Compara texto novo com o atual disponível na biblioteca
            // Se o texto desenvolvido é diferente do atual, o escritor substitui
            // Se for igual ao atual, o escritor é expulso da biblioteca por alguns segundos, por plágio
            bool punir = false;
            if (obra_antiga == "")
            {
                std::cout << "\tEscreveu \"" << obra_atual << "\";" << std::endl;
                livro_lido = false;
            }
            else if (obra_antiga == obra_atual)
            {
                std::cout << "\tTentou copiar o texto atual e foi acusado de plágio;" << std::endl;
                punir = true;
            }
            else
            {
                std::cout << "\tApagou \"" << obra_antiga << "\";" << std::endl;
                std::this_thread::sleep_for(std::chrono::milliseconds(450));
                std::cout << "\tEscreveu \"" << obra_atual << "\";" << std::endl;
                livro_lido = false;
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(450));
            std::cout << "\tFoi embora." << std::endl;
            
            // Notifica a galera
            cv_escritores.notify_all();
            cv_leitores.notify_all();

            // Libera zona crítica
            escritor_on = false;
            lock.unlock();
            if (punir)
                std::this_thread::sleep_for(std::chrono::seconds(20));

            // Descansa antes de escrever novamente
            std::this_thread::sleep_for(std::chrono::milliseconds(450));
        }
    }

    void leitor(std::string nome, int id)
    {
        /*
        Função para as threads de leitor
        */
        while (true)
        {
            // Tenta obter acesso à zona crítica
            std::unique_lock<std::mutex> lock(mutex);
            cv_leitores.wait(lock, [this, nome]()
                             { return !escritor_on && !livro_lido; });

            // Entrou na zona crítica (biblioteca)
            std::cout << "[Leitor " << id << "] " << nome << ":\n\tEntrou na biblioteca;" << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(450));

            // Começa a ler o texto disponível
            std::cout << "\tEstá lendo \"" << obra_atual << "\";" << std::endl;
            num_leitores_on++;
            std::this_thread::sleep_for(std::chrono::milliseconds(450));

            // Libera zona crítica (biblioteca) para demais leitores lerem, notificando-os
            lock.unlock();
            cv_leitores.notify_all();

            // Mecanismo de barreira para garantir que os leitores saiam todos juntos, antes do próximo escritor poder entrar
            while (num_leitores_on != NUM_LEITORES) {}

            // Julga o texto lido e vai embora
            lock.lock();
            std::cout << "[Leitor " << id << "] " << nome << std::endl;
            std::cout << "\tAchou o texto " << randStrRowFromTxt("txtFiles/adjetivos.txt") << ";" << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(450));
            std::cout << "\tFoi embora." << std::endl;
            num_leitores_on--;
            livro_lido = true;
            std::this_thread::sleep_for(std::chrono::milliseconds(450));
            lock.unlock();

            // Notifica escritores
            cv_escritores.notify_all();

            // Aguarda um tempo antes de ler novamente
            std::this_thread::sleep_for(std::chrono::milliseconds(450));
        }
    }
};

#endif
