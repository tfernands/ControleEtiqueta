#ifndef USUARIO_H
#define USUARIO_H

#include <iostream>
#include <string>

class Usuario{

private:
	static unsigned int id_counter;
    unsigned int id;
	std::string senha;

protected:
	std::string username;

public:
	Usuario(std::string username, std::string senha);
	virtual ~Usuario();
	
	void set_senha(std::string senha);

    unsigned int get_id();
    std::string get_username();
    std::string get_senha();
   
	bool check_crendenciais(std::string username, std::string senha);

	virtual std::string to_string();
    virtual void print();

};


#endif