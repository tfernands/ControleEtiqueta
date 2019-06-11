#ifndef PUBLICACAO_H
#define PUBLICACAO_H

#include <iostream>
#include <vector>
#include <ctime>

class Publicacao {

private:
    static unsigned int id_count;
    unsigned int id;
    tm primeira_edicao;
    std::string nome;
    int frequencia;

    static int semanas_entre_data(tm inicio, tm fim);
    static int meses_entre_data(tm inicio, tm fim);
    
public:
    static const int SEMANAL = 0;
    static const int MENSAL = 1;
    
    Publicacao(std::string nome, int frequencia, tm primeira_edicao);
    virtual ~Publicacao();

    static tm get_data(int d, int m, int y);
    
    unsigned int get_id();
    std::string get_nome();
    int get_numero_edicao(tm data);
    int get_ultima_edicao();
    int get_frequencia();
    tm get_data_edicao(int numero);


    std::string to_string();
    void print();
    
};

#endif

