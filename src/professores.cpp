#include "../include/professores.hpp"
#include "../include/disciplina.hpp"
#include <memory>
using namespace std;

Professor::Professor(int id, string nome, shared_ptr<Disciplina> materiaLecionada) {
    this->id = id;
    this->nome = nome;
    this->materiaLecionada = materiaLecionada;
}