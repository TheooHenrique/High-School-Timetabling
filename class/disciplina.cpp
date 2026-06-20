#ifndef DISCIPLINA
#define DISCIPLINA

#include <string>
using namespace std;

class Disciplina {
public:

    int id;
    string nome;
    
    Disciplina(int id, string nome) {
        this->id = id;
        this->nome = nome;
    }

};

#endif
