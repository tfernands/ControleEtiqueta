#include "Cliente.hpp"

Cliente::Cliente(std::string username, std::string senha):
	Usuario(username, senha){ }

Cliente::Cliente(std::string username, std::string senha, std::string nome, std::string endereco, std::string telefone):
	Usuario(username, senha){
    this->nome = nome;
	this->endereco = endereco;
	this->telefone = telefone;
}

Cliente::~Cliente(){}

void Cliente::set_nome(std::string nome){
    this->nome = nome;
}

void Cliente::set_endereco(std::string endereco){
    this->endereco = endereco;
}

void Cliente::set_telefone(std::string telefone){
    this->telefone = telefone;
}

std::string Cliente::get_nome(){
    return this->nome;
}

std::string Cliente::get_endereco(){
    return this->endereco;
}

std::string Cliente::get_telefone(){
    return this->telefone;
}

std::string Cliente::to_string(){
    std::string s = 
         "    ID: "+std::to_string(this->get_id())+"\n";
    s += "    Username: "+this->username+"\n";
    s += "    Nome: "+this->nome+"\n";
    s += "    Endereco: "+this->endereco+"\n";
    s += "    Telefone: "+this->telefone+"\n";
    return s;
}

void Cliente::print(){
    std::cout << this->to_string() << std::endl;
}
