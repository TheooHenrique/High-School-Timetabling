#pragma once
#include "disciplina.hpp"
#include <memory>
using namespace std;
class Professor {
public:

    int id;
    string nome;
    shared_ptr<Disciplina> materiaLecionada; 

    Professor(int id, string nome, shared_ptr<Disciplina> materiaLecionada);
};
