#ifndef AULA
#define AULA

#include "turmas.cpp"
#include "professores.cpp"
#include "salas.cpp"
#include <memory>

using namespace std;

class Aula {

    int id;
    int horario{-1};
    shared_ptr<Professor> prof;
    shared_ptr<Turma> turma;
    shared_ptr<Sala> sala;
    
    Aula(int i, shared_ptr<Professor> p, shared_ptr<Turma> t, shared_ptr<Sala> s) {
        id = i;
        prof = p;
        turma = t;
        sala = s;
    }

};

#endif
