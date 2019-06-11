#ifndef SISTEMA_H
#define SISTEMA_H

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <typeinfo>
#include <limits>
#include "DB.hpp"
#include "Usuario.hpp"
#include "Administrador.hpp"
#include "Cliente.hpp"


class Sistema {
    
private:
	bool running;
	int rotina;
	Usuario *usuario_logado = NULL;
	
	//AUXILIAR UI 
	std::string string_cabecalho();
	std::string string_titulo(std::string titulo);
	int get_input_numerico(int start, int end);
	int display_menu(std::string prefix, std::vector<std::string> opcoes, std::vector<int> retorno);

	//ROTINAS
	int ui_cotrole_etiquetas();
	int ui_login();
	int ui_menu();
	int ui_nova_assinatura();
	int ui_minhas_assinaturas();
	int ui_lista_de_publicacoes();
	int ui_lista_de_clientes();
	int ui_cad_cliente();
	int ui_gerar_etiquetas();
	void ui_edit_cliente(Cliente* cliente);
	int ui_sair();

	bool login(std::string username, std::string senha);
	void logout();

public:
	enum ROTINAS{
		MAIN, LOGIN, MENU, NOVA_ASSINATURA,
		MINHAS_ASSINATURAS, GERAR_ETIQUETAS,
		PUBLICACOES, CLIENTES, CAD_CLIENTE,
		SAIR, FECHAR
	};

	Sistema();
	~Sistema();

	bool is_running();

	Usuario *get_usuario_logado();

	void ui_main();

};

#endif /* SISTEMA_H */

