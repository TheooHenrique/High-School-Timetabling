#ifndef TURMA
#define TURMA
#include <memory>
#include <vector>
#include "disciplina.cpp"
#include "ano.cpp"
using namespace std;

class Turma {
    public:

        anoEscolar serie;
        int id;
        vector<shared_ptr<Disciplina>> disciplinasObrigatorias;
        vector<int> cargaHorariaPorDisciplina;

        Turma(anoEscolar serie, int id, vector<shared_ptr<Disciplina>> disciplinasObrigatoriasPorTurma, vector<int> CargaHorariaPorDisciplina) {
            this->serie = serie;
            this->id = id;
            this->disciplinasObrigatorias = disciplinasObrigatoriasPorTurma;
            this->cargaHorariaPorDisciplina = CargaHorariaPorDisciplina;
        }

};
#endif