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

        Turma(anoEscolar serie, int id, int numDeAlunos, vector<shared_ptr<Disciplina>> disciplinasObrigatoriasPorTurma) {
            this->serie = serie;
            this->id = id;
            this->disciplinasObrigatorias = disciplinasObrigatoriasPorTurma;
        }

};
#endif