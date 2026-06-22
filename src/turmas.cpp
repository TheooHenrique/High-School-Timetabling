#include "../include/disciplina.hpp"
#include "../include/ano.hpp"
#include "../include/turmas.hpp"
using namespace std;

Turma::Turma(anoEscolar serie, int id, vector<shared_ptr<Disciplina>> disciplinasObrigatoriasPorTurma, vector<int> CargaHorariaPorDisciplina) {
    this->serie = serie;
    this->id = id;
    this->disciplinasObrigatorias = disciplinasObrigatoriasPorTurma;
    this->cargaHorariaPorDisciplina = CargaHorariaPorDisciplina;
}