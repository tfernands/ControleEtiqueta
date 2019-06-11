#include "Administrador.hpp"

Administrador::Administrador(std::string username, std::string senha):
	Usuario(username, senha){ }

Administrador::~Administrador(){}

std::string Administrador::to_string(){
    std::string s = "Administrador\n";
    s += "ID: "+std::to_string(this->get_id())+"\n";
    s += "Username: "+this->username+"\n";
    return s;
}

void Administrador::print(){
    std::cout << this->to_string() << std::endl;
}
