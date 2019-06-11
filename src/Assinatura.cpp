#include "Assinatura.hpp"

unsigned int Assinatura::id_counter;

Assinatura::Assinatura(Cliente& cliente, Publicacao& publicacao, int numero_de_edicoes){
    this->id = Assinatura::id_counter;
	this->cliente = &cliente;
	this->publicacao = &publicacao;
	this->edicao_inicial = publicacao.get_ultima_edicao()+1;
	this->edicao_final = this->edicao_inicial + numero_de_edicoes-1;
	Assinatura::id_counter++;
}

Assinatura::~Assinatura(){
}

unsigned int Assinatura::get_id(){
	return this->id;
}

int Assinatura::get_edicao_inicial(){
	return this->edicao_inicial;
}

int Assinatura::get_edicao_final(){
	return this->edicao_final;
}

int Assinatura::get_edicoes_restantes(){
	return this->edicao_final - this->publicacao->get_ultima_edicao();
}

Cliente* Assinatura::get_cliente(){
	return this->cliente;
}

Publicacao* Assinatura::get_publicacao(){
	return this->publicacao;
}

std::string Assinatura::to_string(){
	std::string s = "    Assinatura\n";
	s += "    Cliente id: "+std::to_string(this->cliente->get_id())+", nome: "+this->cliente->get_nome()+"\n";
	s += "    Publicacao: "+this->publicacao->get_nome()+"\n";
	s += "    Edicao n"+std::to_string(this->edicao_inicial)+" a n"+std::to_string(this->edicao_final)+"\n";
	return s;
}

void Assinatura::print(){
	std::cout<<this->to_string()<<std::endl;
}