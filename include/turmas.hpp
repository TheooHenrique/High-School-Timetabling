#pragma once
#include <memory>
#include <vector>
#include "disciplina.hpp"
#include "ano.hpp"
using namespace std;

class Turma {
    public:

        anoEscolar serie;
        int id;
        vector<shared_ptr<Disciplina>> disciplinasObrigatorias;
        vector<int> cargaHorariaPorDisciplina;

        Turma(anoEscolar serie, int id, vector<shared_ptr<Disciplina>> disciplinasObrigatoriasPorTurma, vector<int> CargaHorariaPorDisciplina);

};
