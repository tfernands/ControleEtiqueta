#ifndef CLIENTE_H
#define CLIENTE_H

#include "Usuario.hpp"

class Cliente : public Usuario{  

private:
    std::string nome;
    std::string endereco;
    std::string telefone;

public:
    Cliente(std::string username, std::string senha);
    Cliente(std::string username, std::string senha, std::string nome, std::string endereco, std::string telefone);
    virtual ~Cliente();

    void set_nome(std::string nome);
    void set_endereco(std::string endereco);
    void set_telefone(std::string telefone);

	std::string get_nome();
    std::string get_endereco();
    std::string get_telefone();

    std::string to_string() override;
    void print() override;

};

#endif


