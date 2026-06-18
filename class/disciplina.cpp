#ifndef DISCIPLINA
#define DISCIPLINA

#include <string>
using namespace std;

class Disciplina {
public:

    int id;
    string nome;
    int cargaHorariaSemanal;
    
    Disciplina(int id, string nome, int cargaHorariaSemanal) {
        this->id = id;
        this->nome = nome;
        this->cargaHorariaSemanal = cargaHorariaSemanal;
    }

};

#endif
