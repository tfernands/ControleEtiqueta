#ifndef ADIMINISTRADOR_H
#define ADIMINISTRADOR_H

#include "Usuario.hpp"

class Administrador : public Usuario{  

private:
    
public:
    Administrador(std::string username, std::string senha);
    virtual ~Administrador();

    std::string to_string() override;
    void print() override;

};

#endif