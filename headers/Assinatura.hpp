#ifndef ASSINATURA_H
#define ASSINATURA_H

#include <iostream>
#include <string>
#include "Cliente.hpp"
#include "Publicacao.hpp"

class Assinatura{

private:
	static unsigned int id_counter;
    unsigned int id;
	Cliente* cliente;
	Publicacao* publicacao;
	int edicao_inicial;
	int edicao_final;

public:
	Assinatura(Cliente& cliente, Publicacao& publicacao, int numero_de_edicoes);
	virtual ~Assinatura();

	unsigned int get_id();
	int get_edicao_inicial();
	int get_edicao_final();
	int get_edicoes_restantes();
	Cliente* get_cliente();
	Publicacao* get_publicacao();
	
	std::string to_string();
	void print();
	
};


#endif