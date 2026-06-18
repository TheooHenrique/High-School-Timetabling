/*
 * Quantidade de turmas de 1° ano:
 >>> n
 * Quantidade de turmas de 2° ano:
 >>> n
 * Quantidade de turmas de 3° ano:
 >>> n

 * Insira disciplinas obrigatorias para 1° ano (0 para término):
 >>> [Disciplina, quantidade]
 * Insira disciplinas obrigatorias para 2° ano (0 para término):
 >>> [...]
 * Insira disciplinas obrigatorias para 3° ano (0 para término):
 >>> [...]

 * Quantos professores [Tem que bater o número de professores e disciplinas diferentes]:
 >>> m
     * Nome do professor 1:
     >>> [...]
     * Disciplina lecionada:
     >>> [...]
     ...
     * Nome do professor m:
     >>> [...]
     * Disciplina lecionada:
     >>> [...]
    
  * Quantas salas:
  >>> i

*/

#include "ano.cpp"
#include "aula.cpp"
#include "disciplina.cpp"
#include "professores.cpp"
#include "salas.cpp"
#include "turmas.cpp"
#include <iostream>
#include <memory>

using namespace std;
int main() {
    int qtd1, qtd2, qtd3, ctDisc = 0;
    std::vector<std::shared_ptr<Disciplina>> disciplinas;
    std::vector<std::shared_ptr<Professor>> professores;
    std::vector<std::shared_ptr<Turma>> turmas;
    std::vector<std::shared_ptr<Aula>> aulas;

    vector<shared_ptr<Disciplina>> obrigatoriasPrimeiro;
    vector<shared_ptr<Disciplina>> obrigatoriasSegundo;
    vector<shared_ptr<Disciplina>> obrigatoriasTerceiro;
    
    cout << "Insira aqui a quantidade de turmas de primeiro ano";
    cin >> qtd1;

    cout << "Insira aqui a quantidade de turmas de segundo ano";
    cin >> qtd2;

    cout << "Insira aqui a quantidade de turmas de terceiro ano";
    cin >> qtd3;

    string nomeDisc;
    int ch;

    int qtdMaterias1;
    cout << "Insira aqui a quantidade de matérias obrigatórias para os primeiros anos: ";
    cin >> qtdMaterias1;
    cout << "Insira aqui as matérias obrigatórias para os primeiros anos, seguido pela carga horária semanal: ";
    for (int i = 0; i < qtdMaterias1; ++i){
        cin >> nomeDisc;
        cin >> ch;
        auto disc = make_shared<Disciplina>(ctDisc++, nomeDisc, ch);
        obrigatoriasPrimeiro.push_back(disc);
        disciplinas.push_back(disc);
    }

    int qtdMaterias2;
    cout << "Insira aqui a quantidade de matérias obrigatórias para os segundos anos: ";
    cin >> qtdMaterias2;
    cout << "Insira aqui as matérias obrigatórias para os segundos anos, seguido pela carga horária semanal: ";
    for (int i = 0; i < qtdMaterias2; ++i){
        cin >> nomeDisc;
        cin >> ch;
        auto disc = make_shared<Disciplina>(ctDisc++, nomeDisc, ch);
        obrigatoriasSegundo.push_back(disc);
        disciplinas.push_back(disc);
    }

    int qtdMaterias3;
    cout << "Insira aqui a quantidade de matérias obrigatórias para os terceiros anos: ";
    cin >> qtdMaterias3;
    cout << "Insira aqui as matérias obrigatórias para os terceiros anos, seguido pela carga horária semanal: ";
    for (int i = 0; i < qtd3; ++i){
        cin >> nomeDisc;
        cin >> ch;
        auto disc = make_shared<Disciplina>(ctDisc++, nomeDisc, ch);
        obrigatoriasTerceiro.push_back(disc);
        disciplinas.push_back(disc);
    }

    //Lógica de adicionar professores
    cout << "Agora adicione o nome dos professores, associados a suas respectivas disciplinas (Coloque um professor para cada matéria): ";
    string nomeProf;
    for (int i = 0; i < disciplinas.size(); ++i){
        cin >> nomeProf;
        
    }

}
