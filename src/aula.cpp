#include "../include/aula.hpp"
using namespace std;

Aula::Aula(int i, shared_ptr<Professor> p, shared_ptr<Turma> t, shared_ptr<Sala> s) {
    id = i;
    prof = p;
    turma = t;
    sala = s;
}