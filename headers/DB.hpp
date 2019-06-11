#ifndef _DB_H
#define _DB_H

#include <iostream>
#include <string>
#include <vector>
#include "Usuario.hpp"
#include "Publicacao.hpp"
#include "Assinatura.hpp"

class DB{
	private:
	static std::vector<Usuario*> usuarios;
	static std::vector<Publicacao*> publicacoes;
	static std::vector<Assinatura*> assinaturas;

	public:
	static Usuario* get_usuario(unsigned int id);
	static Usuario* get_usuario(std::string username);
	static std::vector<Usuario*> get_usuarios();
	static void salvar_usuario(Usuario* usuario);
	static void apagar_usuario(unsigned int id);

	static Publicacao* get_publicacao(unsigned int id);
	static std::vector<Publicacao*> get_publicacoes();
	static void salvar_publicacao(Publicacao* publicacao);
	static void apagar_publicacao(unsigned int id);

	static Assinatura* get_assinatura(unsigned int id);
	static std::vector<Assinatura*> get_assinaturas();
	static std::vector<Assinatura*> get_assinaturas_where_cliente_id(unsigned int client_id);
	static std::vector<Assinatura*> get_assinaturas_where_publicacao_id(unsigned int publicacao_id);
	static void salvar_assinatura(Assinatura* publicacao);
	static void apagar_assinatura(unsigned int id);

	static void print();

	static void free_memory();
};

#endif