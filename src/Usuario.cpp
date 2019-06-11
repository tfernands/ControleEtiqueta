#include "Usuario.hpp"

unsigned int Usuario::id_counter = 0;

Usuario::Usuario(std::string username, std::string senha){
	this->username = username;
	this->senha = senha;
	this->id = Usuario::id_counter++;
}

Usuario::~Usuario(){}

unsigned int Usuario::get_id(){
    return this->id;
}

void Usuario::set_senha(std::string senha){
	this->senha = senha;
}

std::string Usuario::get_username(){
	return this->username;
}

std::string Usuario::get_senha(){
	return this->senha;
}

bool Usuario::check_crendenciais(std::string username, std::string senha){
	return this->username == username && this->senha == senha;
}

std::string Usuario::to_string(){
    std::string s = "Usuario\n";
    s += this->username+"\n";
    return s;
}

void Usuario::print(){
    std::cout << this->to_string() << std::endl;
}