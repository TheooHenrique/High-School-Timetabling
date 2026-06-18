#ifndef PROFESSORES
#define PROFESSORES

#include "disciplina.cpp"
#include <memory>
using namespace std;
class Professor {
public:

    string id;
    string nome;
    shared_ptr<Disciplina> materiaLecionada; 

    Professor(string id, string nome, shared_ptr<Disciplina> materiaLecionada) {
        this->id = id;
        this->nome = nome;
        this->materiaLecionada = materiaLecionada;
    }

};

#endif
