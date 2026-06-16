#ifndef PROFESSORES
#define PROFESSORES

#include "disciplina.cpp"
using namespace std;
class Professor {
public:
    // TODO::DIFICULDADES::This WILL cause segfaults
    Professor(string id, string nome, Disciplina &materiaLecionada) {
        this->id = id;
        this->nome = nome;
        this->materiaLecionada = &materiaLecionada;
        // Disciplina *d = new Disciplina(materiaLecionada.id, materiaLecionada.nome, materiaLecionada.cargaHorariaSemanal);
        // this->materiaLecionada = materiaLecionada;
    }
    string id;
    string nome;
    Disciplina *materiaLecionada; 
};

#endif
