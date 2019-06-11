#include "Publicacao.hpp"

const int SEGUNDOS_POR_SEMANA = 60*60*24*7;
unsigned int Publicacao::id_count;

Publicacao::Publicacao(std::string nome, int frequencia, tm primeira_edicao) {
    this->id = Publicacao::id_count;
    this->nome = nome;
    this->frequencia = frequencia;
    this->primeira_edicao = primeira_edicao;
    Publicacao::id_count++;
}

Publicacao::~Publicacao() {}

int Publicacao::semanas_entre_data(tm inicio, tm fim){
    time_t t_incio = mktime(&inicio);
    time_t t_fim = mktime(&fim);
    return (t_fim-t_incio)/SEGUNDOS_POR_SEMANA;
}

int Publicacao::meses_entre_data(tm inicio, tm fim){
    int dy = fim.tm_year-inicio.tm_year;
    int dm = fim.tm_mon-inicio.tm_mon;
    int dd = fim.tm_mday-inicio.tm_mday;
    int meses = dy*12+dm;
    if (dd <= 0) meses--;
    return meses;
}


struct tm Publicacao::get_data(int d, int m, int y){
    time_t now = time(NULL);
    tm data = *localtime(&now);
    data.tm_mday = d;
    data.tm_mon = m-1;
    data.tm_year = y-1900;
    mktime(&data);
    return data;
}

unsigned int Publicacao::get_id(){
    return this->id;
}

std::string Publicacao::get_nome(){
    return this->nome;
}

int Publicacao::get_numero_edicao(tm data){
    if (frequencia == MENSAL) return meses_entre_data(primeira_edicao, data);
    return semanas_entre_data(primeira_edicao, data);
}

int Publicacao::get_ultima_edicao(){
    time_t now = time(NULL);
    tm data = *localtime(&now);
    if (frequencia == MENSAL) return meses_entre_data(primeira_edicao, data);
    return semanas_entre_data(primeira_edicao, data);
}

int Publicacao::get_frequencia(){
    return this->frequencia;
}

tm Publicacao::get_data_edicao(int numero){
    time_t now = time(NULL);
    tm data = *localtime(&now);
    data.tm_year = primeira_edicao.tm_year;
    data.tm_mon = primeira_edicao.tm_mon;
    data.tm_mday = primeira_edicao.tm_mday;
    if (frequencia == MENSAL){
        data.tm_mon += numero-1;
    }else{
        data.tm_mday += (numero-1)*7;
    }
    mktime(&data);
    return data;
}

std::string Publicacao::to_string(){
    int ultima_ed = get_ultima_edicao();
    tm data_ultima_ed = get_data_edicao(ultima_ed);
    std::string s;
    s =  "    Nome: "+nome+"\n";
    s += "    Frequencia: ";
    if (frequencia == MENSAL) s += "Mensal\n";
    else s += "Semanal\n";
    s += "    Ultima edicao: "+std::to_string(ultima_ed)+"\n";
    char buffer[30];
    strftime(buffer, 30, "    Data: %d/%m/%Y", &data_ultima_ed);
    s += buffer;
    return s+"\n";
}

void Publicacao::print(){
    std::cout << this->to_string() << std::endl << std::endl;
}