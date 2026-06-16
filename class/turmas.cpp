#include <vector>
#include "disciplina.cpp"
using namespace std;

enum ano {
    PRIMEIRO = 0,
    SEGUNDO,
    TERCEIRO
};

class Turma {
    public:
        Turma(ano serie, int id, int numDeAlunos, vector<vector<Disciplina>> disciplinasObrigatoriasPorTurma) {
            this->serie = serie;
            this->id = id;

            switch (serie) {
                case (PRIMEIRO):
                    {
                        disciplinasObrigatorias = disciplinasObrigatoriasPorTurma[PRIMEIRO];
                        break;
                    }
                case (SEGUNDO):
                    {
                        disciplinasObrigatorias = disciplinasObrigatoriasPorTurma[SEGUNDO];
                        break;
                    }
                case (TERCEIRO):
                    {
                        disciplinasObrigatorias = disciplinasObrigatoriasPorTurma[TERCEIRO];
                        break;
                    }
            }

        }

        ano serie;
        int id;
        vector<Disciplina> disciplinasObrigatorias;
};
