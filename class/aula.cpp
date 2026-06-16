#ifndef AULA
#define AULA

#include "turmas.cpp"
#include "professores.cpp"
#include "salas.cpp"

using namespace std;

class Aula {
    // TODO::DIFICULDADES::Seg fault??
    Aula(int i, Professor &p, Turma &t, Sala &s) {
        id = i;
        prof = &p;
        turma = &t;
        sala = &s;
    }
    int id;
    int horario{-1};
    Professor *prof;
    Turma *turma;
    Sala *sala;
};

#endif
