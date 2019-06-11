#include "DB.hpp"

std::vector<Usuario*> DB::usuarios;
std::vector<Publicacao*> DB::publicacoes;
std::vector<Assinatura*> DB::assinaturas;

Usuario* DB::get_usuario(unsigned int id){
	std::vector<Usuario*> resposta;
	for (unsigned int i = 0; i < DB::usuarios.size(); i++){
		if (DB::usuarios[i]->get_id() == id){
			return DB::usuarios[i];
		}
	}
	return NULL;
}

Usuario* DB::get_usuario(std::string username){
	std::vector<Usuario*> resposta;
	for (unsigned int i = 0; i < DB::usuarios.size(); i++){
		if (DB::usuarios[i]->get_username() == username){
			return DB::usuarios[i];
		}
	}
	return NULL;
}

std::vector<Usuario*> DB::get_usuarios(){
	return DB::usuarios;
}

void DB::salvar_usuario(Usuario* usuario){
	DB::usuarios.push_back(usuario);
}

void DB::apagar_usuario(unsigned int id){
	for (unsigned int i = 0; i < DB::usuarios.size(); i++){
		if (DB::usuarios[i]->get_id() == id){

			//deletar assinaturas
			for (unsigned int j = 0; j < DB::assinaturas.size(); j++){
				if (assinaturas[j]->get_cliente()->get_id() == id){
					delete DB::assinaturas[j];
					DB::assinaturas.erase(DB::assinaturas.begin() + j);
					j--;
				}
			}

			delete DB::usuarios[i];
			DB::usuarios.erase(DB::usuarios.begin() + i);
			break;
		}
	}
}

Publicacao* DB::get_publicacao(unsigned int id){
	for (unsigned int i = 0; i < DB::publicacoes.size(); i++){
		if (DB::publicacoes[i]->get_id() == id){
			return DB::publicacoes[i];
		}
	}
	return NULL;
}

std::vector<Publicacao*>  DB::get_publicacoes(){
	return DB::publicacoes;
}

void DB::salvar_publicacao(Publicacao* publicacao){
	DB::publicacoes.push_back(publicacao);
}

void DB::apagar_publicacao(unsigned int id){
	for (unsigned int i = 0; i < DB::publicacoes.size(); i++){
		if (DB::publicacoes[i]->get_id() == id){
			delete DB::publicacoes[i];
			DB::publicacoes.erase(DB::publicacoes.begin() + i);
			break;
		}
	}
}

Assinatura* DB::get_assinatura(unsigned int id){
	for (unsigned int i = 0; i < DB::assinaturas.size(); i++){
		if (DB::assinaturas[i]->get_id() == id){
			return DB::assinaturas[i];
		}
	}
	return NULL;
}

std::vector<Assinatura*> DB::get_assinaturas(){
	return DB::assinaturas;
}

std::vector<Assinatura*> DB::get_assinaturas_where_cliente_id(unsigned int client_id){
	std::vector<Assinatura*> cliente_assinaturas;
	for (unsigned int i = 0; i < DB::assinaturas.size(); i++){
		if (DB::assinaturas[i]->get_cliente()->get_id() == client_id){
			cliente_assinaturas.push_back(DB::assinaturas[i]);
		}
	}
	return cliente_assinaturas;
}

std::vector<Assinatura*> DB::get_assinaturas_where_publicacao_id(unsigned int publicacao_id){
	std::vector<Assinatura*> publicacao_assinaturas;
	for (unsigned int i = 0; i < DB::assinaturas.size(); i++){
		if (DB::assinaturas[i]->get_publicacao()->get_id() == publicacao_id){
			publicacao_assinaturas.push_back(DB::assinaturas[i]);
		}
	}
	return publicacao_assinaturas;
}

void DB::salvar_assinatura(Assinatura* assinatura){
	DB::assinaturas.push_back(assinatura);
}

void DB::apagar_assinatura(unsigned int id){
	for (unsigned int i = 0; i < DB::assinaturas.size(); i++){
		if (DB::assinaturas[i]->get_id() == id){
			delete DB::assinaturas[i];
			DB::assinaturas.erase(DB::assinaturas.begin() + i);
			break;
		}
	}
}

void DB::print(){
	std::cout<<std::endl<<"Publicações:"<<std::endl;
	for (unsigned int i = 0; i < DB::publicacoes.size(); i++){
		std::cout<<DB::publicacoes[i]->to_string()<<std::endl<<std::endl;
	}
	std::cout<<std::endl;

	std::cout<<std::endl<<"Clientes:"<<std::endl;
	for (unsigned int i = 0; i < DB::usuarios.size(); i++){
		std::cout<<DB::usuarios[i]->to_string()<<std::endl<<std::endl;
	}
	std::cout<<std::endl;

	std::cout<<std::endl<<"Assinaturas:"<<std::endl;
	for (unsigned int i = 0; i < DB::assinaturas.size(); i++){
		std::cout<<DB::assinaturas[i]->to_string()<<std::endl<<std::endl;
	}
	std::cout<<std::endl;
}

void DB::free_memory(){
	for (unsigned int i = 0; i < DB::usuarios.size(); i++){
		delete DB::usuarios[i];
    }
	for (unsigned int i = 0; i < DB::publicacoes.size(); i++){
		delete DB::publicacoes[i];
	}
    for (unsigned int i = 0; i < DB::assinaturas.size(); i++){
		delete DB::assinaturas[i];
	}
}