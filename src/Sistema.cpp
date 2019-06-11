#include "Sistema.hpp"

Sistema::Sistema() {
	running = true;
    rotina = MAIN;

	//Setar dados inciais
    DB::salvar_publicacao(
        new Publicacao("Super", Publicacao::MENSAL, Publicacao::get_data(10, 5, 2002))
    );
    DB::salvar_publicacao(
        new Publicacao("Guia de viagens", Publicacao::MENSAL, Publicacao::get_data(22, 5, 2013))
    );
    DB::salvar_publicacao(
        new Publicacao("Veja", Publicacao::SEMANAL, Publicacao::get_data(4, 2, 1993))
    );
    DB::salvar_publicacao(
        new Publicacao("Titans", Publicacao::SEMANAL, Publicacao::get_data(18, 1, 2017))
    );
    DB::salvar_publicacao(
        new Publicacao("H&H", Publicacao::MENSAL, Publicacao::get_data(8, 8, 2008))
    );

    DB::salvar_usuario(
        new Administrador(
            "admin",
            "admin"
        )
    );
	DB::salvar_usuario(
        new Cliente(
            "thalesfs",
            "1234",
            "Thales Fernandes da Silva",
            "Rua Agenor Goulart Filho, 85, Ouro Preto, Belo Horizonte-MG",
            "(33) 9.9947-4478"
        )
    );
    DB::salvar_usuario(
        new Cliente(
            "eduardo",
            "123",
            "Eduardo Araujo Lima",
            "Rua José Francisco da Silva, 784, João Pessoa-PB",
            "(83) 2713-6243"
        )
    );
    DB::salvar_usuario(
        new Cliente(
            "luan",
            "1111",
            "Luan Barbosa Lima",
            "Rua Estanho, 1687, Uberaba-MG",
            "(34) 8725-5453"
        )
    );
    DB::salvar_usuario(
        new Cliente(
            "agatha",
            "123",
            "Agatha Pereira Fernandes",
            "Rua Quinze, 1129, Jundiaí-SP",
            "(11) 6159-3559"
        )
    );

    DB::salvar_assinatura(
        new Assinatura(
            *dynamic_cast<Cliente*>(DB::get_usuario(1)),
            *DB::get_publicacao(1),
            7
        )
    );
    DB::salvar_assinatura(
        new Assinatura(
            *dynamic_cast<Cliente*>(DB::get_usuario(1)),
            *DB::get_publicacao(0),
            9
        )
    );
    DB::salvar_assinatura(
        new Assinatura(
            *dynamic_cast<Cliente*>(DB::get_usuario(2)),
            *DB::get_publicacao(3),
            8
        )
    );
    DB::salvar_assinatura(
        new Assinatura(
            *dynamic_cast<Cliente*>(DB::get_usuario(2)),
            *DB::get_publicacao(4),
            5
        )
    );
    DB::salvar_assinatura(
        new Assinatura(
            *dynamic_cast<Cliente*>(DB::get_usuario(3)),
            *DB::get_publicacao(1),
            4
        )
    );
    DB::salvar_assinatura(
        new Assinatura(
            *dynamic_cast<Cliente*>(DB::get_usuario(3)),
            *DB::get_publicacao(2),
            12
        )
    );
    DB::salvar_assinatura(
        new Assinatura(
            *dynamic_cast<Cliente*>(DB::get_usuario(3)),
            *DB::get_publicacao(0),
            7
        )
    );
    DB::salvar_assinatura(
        new Assinatura(
            *dynamic_cast<Cliente*>(DB::get_usuario(4)),
            *DB::get_publicacao(0),
            4
        )
    );
    DB::salvar_assinatura(
        new Assinatura(
            *dynamic_cast<Cliente*>(DB::get_usuario(4)),
            *DB::get_publicacao(3),
            5
        )
    );
    DB::salvar_assinatura(
        new Assinatura(
            *dynamic_cast<Cliente*>(DB::get_usuario(4)),
            *DB::get_publicacao(4),
            2
        )
    );
}

Sistema::~Sistema(){
    DB::free_memory();
}

bool Sistema::is_running(){
    return this->running;
}

Usuario *Sistema::get_usuario_logado(){
    return this->usuario_logado;
}

bool Sistema::login(std::string username, std::string senha){
    if (this->usuario_logado != NULL){
        std::cout<<"Faça o logout do usuario "+this->usuario_logado->get_username()+" primeiro."<<std::endl;
        return false;
    }
    Usuario* cliente_found = DB::get_usuario(username);
    //confere credenciais
    if (cliente_found != NULL && cliente_found->check_crendenciais(username, senha)){
        this->usuario_logado = cliente_found;
        return true;
    }
    else{
        return false;
    }
}

void Sistema::logout(){
    if (this->usuario_logado != NULL){
        std::cout<<this->usuario_logado->get_username()+" desconectou."<<std::endl;
        this->usuario_logado = NULL;
    }
    else{
        std::cout<<"Nenhum usuario logado."<<std::endl;
    }
}

//AUXILIAR UI 
std::string Sistema::string_cabecalho(){
    if (this->get_usuario_logado() != NULL)
        return "Usuario "+this->get_usuario_logado()->get_username()+" logado.\n";
    return "";
}

std::string Sistema::string_titulo(std::string titulo){
    return "\n      "+titulo+"\n\n";
}

int Sistema::get_input_numerico(int start, int end){
    int selecao = 0;
    while(!(std::cin >> selecao) || selecao < start || selecao > end){
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout<<"Entrada invalida, deve ser um numero entre "<<start<<" e "<<end<<"."<<std::endl;
    }
    return selecao;
}

int Sistema::display_menu(std::string prefix, std::vector<std::string> opcoes, std::vector<int> retorno){
    unsigned int selecao = 0;
    std::string status = "";
    while(selecao == 0 || selecao > opcoes.size()){
        system("CLS");
        std::cout<<prefix;
        unsigned int opcao_numero = 1;
        for (unsigned int i = 0; i < opcoes.size(); i++){
            if (opcoes[i].size() > 0){
                std::cout<<"    "<<opcao_numero++<<" - "<<opcoes[i]<<std::endl;
            }
            else{
                std::cout<<std::endl;
            }
        }
        std::cout<<std::endl<<status;
        std::cout<<"  Selecione uma opcao: ";

        std::fflush(stdin);
        if(!(std::cin >> selecao) || selecao == 0 || selecao > opcao_numero){
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            status = "Entrada invalida, tente novamente.\n";
        }
    }
    return retorno[selecao-1];
}

//UI
void Sistema::ui_main(){
    switch(rotina){
        case MAIN:               rotina = ui_cotrole_etiquetas();   break;
        case LOGIN:              rotina = ui_login();               break;
        case MENU:               rotina = ui_menu();                break;
        case NOVA_ASSINATURA:    rotina = ui_nova_assinatura();     break;
        case MINHAS_ASSINATURAS: rotina = ui_minhas_assinaturas();  break;
        case GERAR_ETIQUETAS:    rotina = ui_gerar_etiquetas();     break;
        case PUBLICACOES:        rotina = ui_lista_de_publicacoes();break;
        case CLIENTES:           rotina = ui_lista_de_clientes();   break;
        case CAD_CLIENTE:        rotina = ui_cad_cliente();         break;
        case SAIR:               rotina = ui_sair();                break;
        case FECHAR:             running = false;                   break;
    }
}

int Sistema::ui_cotrole_etiquetas(){
    std::string layout = string_titulo("CONTROLE ETIQUETAS");
    std::vector<std::string> opcoes = {
        "Login",
        "Fechar"
    };
    std::vector<int> retornos = {
        LOGIN,
        FECHAR
    };
    return display_menu(layout, opcoes, retornos);
}

int Sistema::ui_login(){
    system("CLS");
    while(get_usuario_logado() == NULL){
        std::string user;
        std::string senha;
        std::fflush(stdin);
        std::cout<<string_titulo("LOGIN");
        std::cout<<"    Usuario: ";
        std::cin>>user;
        std::cout<<std::endl;
        std::cout<<"    Senha: ";
        std::cin>>senha;
        system("CLS");
        if (user == "EXIT" || user == "0"){
            return SAIR;
        }
        else if(!login(user, senha))
            std::cout<<"Usuario ou senha invalidos."<<std::endl;
    }
    return MENU;
}

int Sistema::ui_menu(){
    if (typeid(*get_usuario_logado()).name() == typeid(Cliente).name()){
        std::string layout = string_cabecalho()+string_titulo("MENU");
        std::vector<std::string> opcoes = {
            "Nova assinatura",
            "Minhas assinaturas",
            "Sair"
        };
        std::vector<int> retornos = {
            NOVA_ASSINATURA,
            MINHAS_ASSINATURAS,
            SAIR
        };
        return display_menu(layout, opcoes, retornos);
    }
    else if(typeid(*get_usuario_logado()).name() == typeid(Administrador).name()){
        std::string layout = string_cabecalho()+string_titulo("MENU ADMINISTRADOR");
        std::vector<std::string> opcoes = {
            "Gerar etiquetas",
            "Publicacoes",
            "Clientes",
            "Sair"
        };
        std::vector<int> retornos = {
            GERAR_ETIQUETAS,
            PUBLICACOES,
            CLIENTES,
            SAIR
        };
        return display_menu(layout, opcoes, retornos);
    }
    return SAIR;
}

int Sistema::ui_nova_assinatura(){
    std::string layout = string_cabecalho()+string_titulo("MENU > NOVA ASSINATURA");
    std::string info;
    
    std::vector<Assinatura*> minhas_assinaturas = DB::get_assinaturas_where_cliente_id(usuario_logado->get_id());
    std::vector<Publicacao*> publicacoes_disponiveis = DB::get_publicacoes();
    
    for (unsigned int i = 0; i < minhas_assinaturas.size(); i++){
        for (unsigned int j = 0; j < publicacoes_disponiveis.size(); j++){
            if (minhas_assinaturas[i]->get_publicacao()->get_id() == publicacoes_disponiveis[j]->get_id()){
                publicacoes_disponiveis.erase(publicacoes_disponiveis.begin() + j);
                j--;
            }
        }
    }

    std::vector<std::string> opcoes;
    std::vector<int> retornos;
    if (publicacoes_disponiveis.size() >= 1){
        info = "  Qual publicacao voce deseja assinar?\n\n";
        for (unsigned int i = 0; i < publicacoes_disponiveis.size(); i++){
            opcoes.push_back(publicacoes_disponiveis[i]->get_nome());
            retornos.push_back(i);
        }
    }
    else{
        info = "  Nenhuma publicacao disponivel.\n";
        opcoes.push_back("Voltar");
        retornos.push_back(MENU);
        return display_menu(layout, opcoes, retornos);
    }

    int selecao = display_menu(layout+info, opcoes, retornos);

    system("CLS");
    std::cout<<layout;

    std::cout<<"  Publicacao selecionada: "<<std::endl<<std::endl;
    publicacoes_disponiveis[selecao]->print();

    std::cout<<"  Quantidade de edicoes: ";
    int edicoes = get_input_numerico(1, 100);

    system("CLS");
    std::cout<<layout;

    opcoes.clear();
    retornos.clear();
    opcoes.push_back("Sim"); opcoes.push_back("Nao");
    retornos.push_back(1); retornos.push_back(0);

    info = "  Confirmar assinatura de "+std::to_string(edicoes)+" edicoes da "+publicacoes_disponiveis[selecao]->get_nome()+"?\n";
    int confirmacao = display_menu(layout+info, opcoes, retornos);

    if (confirmacao == 1){
        Assinatura* assinatura = new Assinatura(*dynamic_cast<Cliente*>(get_usuario_logado()), *publicacoes_disponiveis[selecao], edicoes);
        DB::salvar_assinatura(assinatura);
    }

    return MENU;
}

int Sistema::ui_minhas_assinaturas(){
    system("CLS");
    std::string layout = string_cabecalho()+string_titulo("MENU > MINHAS ASSINATURA");
    std::string info;

    std::vector<Assinatura*> minhas_assinaturas = DB::get_assinaturas_where_cliente_id(usuario_logado->get_id());
    info = "  Voce tem "+std::to_string(minhas_assinaturas.size())+" assinaturas.\n\n";
    for (unsigned int i = 0; i < minhas_assinaturas.size(); i++){
        info += minhas_assinaturas[i]->to_string()+"\n";
    }
    std::vector<std::string> opcoes = {
        "Voltar",
        "Sair"
    };
    std::vector<int> retornos = {
        MENU,
        SAIR
    };
    return display_menu(layout+info, opcoes, retornos);
}

int Sistema::ui_lista_de_publicacoes(){
    std::string layout = string_cabecalho()+string_titulo("MENU > LISTA DE PUBLICACOES");
    std::string info;

    std::vector<Publicacao*> publicacoes = DB::get_publicacoes();
    info = "  "+std::to_string(publicacoes.size())+" publicacoes.\n\n";
    for (unsigned int i = 0; i < publicacoes.size(); i++){
        info += publicacoes[i]->to_string();
        info += "    Numero de assinantes: "+std::to_string(DB::get_assinaturas_where_publicacao_id(publicacoes[i]->get_id()).size())+"\n\n";
    }
    std::vector<std::string> opcoes = {
        "Voltar",
        "Sair"
    };
    std::vector<int> retornos = {
        MENU,
        SAIR
    };
    return display_menu(layout+info, opcoes, retornos);
}

int Sistema::ui_lista_de_clientes(){
    std::string layout = string_cabecalho()+string_titulo("MENU > LISTA DE CLIENTES");
    std::string info;

    std::vector<Usuario*> usuarios = DB::get_usuarios();
    std::vector<Cliente*> clientes;

    //inicializar lista de clientes 
    for (unsigned int i = 0; i < usuarios.size(); i++){
        if (typeid(*usuarios[i]).name() == typeid(Cliente).name()){
            clientes.push_back(dynamic_cast<Cliente*>(usuarios[i]));
        }
    }

    std::vector<std::string> opcoes;
    std::vector<int> retornos;

    if (clientes.size() >= 1){
        for (unsigned int i = 0; i < clientes.size(); i++){
            opcoes.push_back(clientes[i]->get_nome());
            retornos.push_back(i);
        }

        opcoes.push_back("");
        opcoes.push_back("Cadastrar Cliente");
        opcoes.push_back("Voltar");
        retornos.push_back(clientes.size());
        retornos.push_back(clientes.size()+1);

        unsigned int selecao = display_menu(layout, opcoes, retornos);

        if (selecao < clientes.size()){
            system("CLS");
            std::cout<<layout;

            info += clientes[selecao]->to_string()+"\n";

            opcoes.clear();
            retornos.clear();
            opcoes.push_back("Editar");
            opcoes.push_back("Excluir");
            opcoes.push_back("Voltar");
            retornos.push_back(0);
            retornos.push_back(1);
            retornos.push_back(2);

            int escolha = display_menu(layout+info, opcoes, retornos);

            if (escolha == 0){
                ui_edit_cliente(clientes[selecao]);
            }
            else if (escolha == 1){
                std::string pergunta = "    Tem certeza que deseja apagar esse cliente?\n\n";
                std::vector<std::string> opcoes = {"Sim","Nao"};
                std::vector<int> retornos = {0, 1};
                int decisao = display_menu(layout+info+pergunta, opcoes, retornos);
                if (decisao == 0){
                    DB::apagar_usuario(clientes[selecao]->get_id());
                    return CLIENTES;
                }
            }
            else{
                return CLIENTES;
            }
        }
        else if (selecao == clientes.size()){
            return CAD_CLIENTE;
        }
    }
    else{
        info = "  Nenhum cliente cadastrado.\n\n";
        opcoes.push_back("Cadastrar cliente");
        opcoes.push_back("Voltar");
        retornos.push_back(CAD_CLIENTE);
        retornos.push_back(MENU);
        return display_menu(layout+info, opcoes, retornos);
    }

    return MENU;
}

int Sistema::ui_cad_cliente(){
    std::string layout = string_cabecalho()+string_titulo("CADASTRO DE CLIENTE");
    std::string info;

    std::cout<<layout;

    std::string temp_username;
    std::string temp_senha;
    std::string temp_nome;
    std::string temp_endereco;
    std::string temp_telefone;

    std::vector<std::string> opcoes ={
        "Confirmar", "Editar"
    };
    std::vector<int> retornos = {0, 1};

    std::vector<Usuario*> usuarios = DB::get_usuarios();

    bool validado = false;
    std::string temp_status;

    //USERNAME
    while(!validado){
        validado = false;
        bool username_disponivel = true;

        system("CLS");
        std::cout<<layout;
        std::cout<<temp_status;
        std::cout<<"    Username: ";

        std::fflush(stdin);
        std::cin>>temp_username;
        for (unsigned int i = 0; i < usuarios.size(); i++){
            if (usuarios[i]->get_username() == temp_username){
                username_disponivel = false;
                temp_status = "    Username ja existe "+temp_username+", escolha outro.\n\n";
                break;
            }
        }
        if (username_disponivel){
            temp_status = "    O username "+temp_username+" esta disponivel.\n\n";
            int selecao = display_menu(layout+info+temp_status, opcoes, retornos);
            if (selecao == 0){
                info = "    Username: "+temp_username+"\n";
                validado = true;
            }
            temp_status = "";

        }
    }
    validado = false;

    //SENHA
    while(!validado){
        validado = false;
        std::string senha_confirma;
        //inserir senha
        system("CLS");
        std::cout<<layout;
        std::cout<<info;
        std::cout<<temp_status;
        std::cout<<std::endl<<"    Senha: ";
        std::fflush(stdin);
        std::cin>>temp_senha;

        //confirmar senha
        system("CLS");
        std::cout<<layout;
        std::cout<<info;
        std::cout<<temp_status;
        std::cout<<std::endl<<"    Confirmar senha: ";
        std::fflush(stdin);
        std::cin>>senha_confirma;
        if (temp_senha == senha_confirma){
            validado = true;
            info += "    Senha: *******\n";
        }
        else{
            temp_senha = "";
            temp_status = "    Senha nao confere, tente novamente.\n";
        }
    }
    validado = false;

    //NOME
    system("CLS");
    std::cout<<layout;
    std::cout<<info;

    std::cout<<std::endl<<"    Nome: ";
    std::fflush(stdin);
    std::getline(std::cin, temp_nome);

    info += "    Nome: "+temp_nome+"\n";


    //ENDERECO
    system("CLS");
    std::cout<<layout;
    std::cout<<info;

    std::cout<<std::endl<<"   Endereco: ";
    std::fflush(stdin);
    std::getline(std::cin, temp_endereco);

    info += "    Endereco: "+temp_endereco+"\n";


    //TELEFONE
    system("CLS");
    std::cout<<layout;
    std::cout<<info;

    std::cout<<std::endl<<"    Telefone: ";
    std::fflush(stdin);
    std::getline(std::cin, temp_telefone);

    info += "    Telefone: "+temp_telefone+"\n";

    Cliente* cliente = new Cliente(
        temp_username,
        temp_senha,
        temp_nome,
        temp_endereco,
        temp_telefone
    );

    opcoes.clear();
    opcoes.push_back("Salvar");
    opcoes.push_back("Editar");
    opcoes.push_back("Cancelar");
    retornos.push_back(2);

    while(!validado){
        info = "    Salvar cliente?\n\n"+cliente->to_string()+"\n";
        int selecao = display_menu(layout+info, opcoes, retornos);
        if (selecao == 0){
            DB::salvar_usuario(cliente);
            validado = true;
        }
        else if (selecao == 1){
            ui_edit_cliente(cliente);
        }
        else{
            delete cliente;
            validado = true;
        }
    }

    return MENU;
}

void Sistema::ui_edit_cliente(Cliente* cliente){
    std::string layout = string_cabecalho()+string_titulo("EDITANDO CLIENTE: "+cliente->get_id());

    std::string temp_nome = cliente->get_nome();
    std::string temp_endereco = cliente->get_endereco();
    std::string temp_telefone = cliente->get_telefone();

    while(true){
        std::vector<std::string> opcoes ={
            "Nome:      "+temp_nome,
            "Endereco:  "+temp_endereco,
            "Telefone:  "+temp_telefone,
            "",
            "Cancelar",
            "Salvar"
        };
        std::vector<int> retornos = {0, 1, 2, 3, 4};
        int selecao = display_menu(layout, opcoes, retornos);

        system("CLS");
        std::cout<<layout;

        if (selecao == 0){
            std::cout<<std::endl<<"   Nome atual: "+temp_nome;
            temp_nome = "";
            std::cout<<std::endl<<"   Novo nome: ";
            std::fflush(stdin);
            std::getline(std::cin, temp_nome);
        }
        else if (selecao == 1){
            std::cout<<std::endl<<"   Endereco atual: "+temp_endereco;
            temp_endereco = "";
            std::cout<<std::endl<<"   Novo endereco: ";
            std::fflush(stdin);
            std::getline(std::cin, temp_endereco);
        }
        else if (selecao == 2){
            std::cout<<std::endl<<"   Telefone atual: "+temp_telefone;
            temp_telefone = "";
            std::cout<<std::endl<<"   Novo telefone: ";
            std::fflush(stdin);
            std::getline(std::cin, temp_telefone);
        }
        else if (selecao == 3){
            return;
        }
        else if (selecao == 4){
            cliente->set_nome(temp_nome);
            cliente->set_endereco(temp_endereco);
            cliente->set_telefone(temp_telefone);
            return;
        }
    }
}

int Sistema::ui_gerar_etiquetas(){
    std::string layout = string_cabecalho()+string_titulo("MENU > GERAR ETIQUETAS");
    std::string info;

    std::multimap<time_t, std::string> etiquetas;

    std::vector<Assinatura*> assinaturas = DB::get_assinaturas();

    info = "   Etiquetas:\n";
    for (unsigned int i = 0; i < assinaturas.size(); i++){
        Cliente* cliente = assinaturas[i]->get_cliente();
        Publicacao* publicacao = assinaturas[i]->get_publicacao();
        std::string nome_cliente = cliente->get_nome();
        std::string nome_endereco = cliente->get_endereco();
        std::string nome_publicacao = publicacao->get_nome();
        for (unsigned int j = assinaturas[i]->get_edicao_inicial(); (int)j <= assinaturas[i]->get_edicao_final(); j++){
            tm data = publicacao->get_data_edicao(j);
            char buffer[30];
            strftime(buffer, 30, "    %d/%m/%Y\n", &data);
            time_t time;
            time = mktime(&data);

            std::string etiqueta = "\n";
            etiqueta += " ------------------------------------------------------------------\n";
            etiqueta += buffer;
            etiqueta += "    "+nome_cliente+"\n";
            etiqueta += "    "+nome_endereco+"\n";
            etiqueta += "    "+nome_publicacao+", edicao n"+std::to_string(j)+"\n";
            etiqueta += " ------------------------------------------------------------------\n\n";

            etiquetas.insert(std::pair<time_t, std::string>(time, etiqueta));

        }

    }

    for (std::multimap<time_t, std::string>::iterator it = etiquetas.begin(); it != etiquetas.end(); it++)
        info += it->second;

    info +="\n    Excluir Assinaturas?\n\n";
    std::vector<std::string> opcoes = {"Sim", "Nao"};
    std::vector<int> retornos = {0, 1};
    unsigned int selecao = display_menu(layout+info, opcoes, retornos);

    if (selecao == 0){
        for (unsigned int i = 0; i < assinaturas.size(); i++)
            DB::apagar_assinatura(assinaturas[i]->get_id());
    }

    return MENU;
}

int Sistema::ui_sair(){
    logout();
    return MAIN;
}