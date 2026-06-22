#pragma once
#include "professores.hpp"
#include "turmas.hpp"
#include "salas.hpp"
#include <memory>
class Aula {

    int id;
    int horario{-1};
    shared_ptr<Professor> prof;
    shared_ptr<Turma> turma;
    shared_ptr<Sala> sala;
    
    Aula(int i, shared_ptr<Professor> p, shared_ptr<Turma> t, shared_ptr<Sala> s);

};