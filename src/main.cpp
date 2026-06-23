#include "../include/ano.hpp"
#include "../include/aula.hpp"
#include "../include/disciplina.hpp"
#include "../include/professores.hpp"
#include "../include/salas.hpp"
#include "../include/turmas.hpp"
#include <iostream>
using namespace std;

bool conflito(shared_ptr<Aula>a, shared_ptr<Aula>b) {
    if (a->prof == b->prof || a->turma == b->turma || a->sala == b->sala) {
        return true;
    }
    return false;
}

shared_ptr<Disciplina> buscarDisciplinaPorNome(
        const vector<shared_ptr<Disciplina>>& listaDisciplinas, 
        const string& nomeBuscado
        ) 
{
    for (const auto& disc : listaDisciplinas) {
        if (disc->nome == nomeBuscado) {
            return disc; 
        }
    }
    return nullptr;
}

shared_ptr<Professor> buscarProfessorPorDisciplina(
        const vector<shared_ptr<Professor>>& listaProfessores, 
        shared_ptr<Disciplina>& disciplina
        ) 
{
    for (const auto& prof : listaProfessores) {
        if (prof->materiaLecionada == disciplina) {
            return prof; 
        }
    }
    return nullptr;
}
int main() {
    int qtd1, qtd2, qtd3, ctDisc = 0, ctProf = 0, ctSala = 0, ctTurma = 0, ctAula = 0, qtdSalas;
    vector<shared_ptr<Disciplina>> disciplinas;
    vector<shared_ptr<Professor>> professores;
    vector<shared_ptr<Turma>> turmas;
    vector<shared_ptr<Aula>> aulas;
    vector<shared_ptr<Sala>> salas;

    vector<shared_ptr<Disciplina>> obrigatoriasPrimeiro;
    vector<shared_ptr<Disciplina>> obrigatoriasSegundo;
    vector<shared_ptr<Disciplina>> obrigatoriasTerceiro;
    
    //GIGANTESCA CONSTRUCAO DE TURMAS:
    cout << "Insira aqui a quantidade de turmas de primeiro ano: ";
    cin >> qtd1;

    cout << "Insira aqui a quantidade de turmas de segundo ano: ";
    cin >> qtd2;

    cout << "Insira aqui a quantidade de turmas de terceiro ano: ";
    cin >> qtd3;

    string nomeDisc;

    // ==================== PRIMEIRO ANO ====================
    int qtdMaterias1;
    cout << "Insira aqui a quantidade de matérias obrigatórias para o primeiro ano: ";
    cin >> qtdMaterias1;
    cout << "Insira aqui as matérias obrigatórias para o primeiro ano: ";
    for (int i = 0; i < qtdMaterias1; ++i){
        cin >> nomeDisc;
        auto disc = buscarDisciplinaPorNome(disciplinas, nomeDisc);
        if ( disc == nullptr){
            disc = make_shared<Disciplina>(++ctDisc, nomeDisc);
            disciplinas.push_back(disc);
        }
        obrigatoriasPrimeiro.push_back(disc);
    }
    int ch;
    vector<int> cargaHorariaPrimeiro;
    for (const auto& i : obrigatoriasPrimeiro){
        cout << "Insira a carga Horária da disciplina " << i->nome << " para o Primeiro ano: ";
        cin >>  ch;
        cargaHorariaPrimeiro.push_back(ch);
    }

    // ==================== SEGUNDO ANO ====================
    int qtdMaterias2;
    cout << "Insira aqui a quantidade de matérias obrigatórias para o segundo ano: ";
    cin >> qtdMaterias2;
    cout << "Insira aqui as matérias obrigatórias para os segundo ano: ";
    for (int i = 0; i < qtdMaterias2; ++i){
        cin >> nomeDisc;
        auto disc = buscarDisciplinaPorNome(disciplinas, nomeDisc);
        if ( disc == nullptr ){
            disc = make_shared<Disciplina>(++ctDisc, nomeDisc);
            disciplinas.push_back(disc);
        }
        obrigatoriasSegundo.push_back(disc);
    }
    vector<int> cargaHorariaSegundo;
    for (const auto& i : obrigatoriasSegundo){
        cout << "Insira a carga Horária da disciplina " << i->nome << " para o Segundo ano: ";
        cin >>  ch;
        cargaHorariaSegundo.push_back(ch);
    }

    // ==================== TERCEIRO ANO ====================
    int qtdMaterias3;
    cout << "Insira aqui a quantidade de matérias obrigatórias para o terceiro ano: ";
    cin >> qtdMaterias3;
    cout << "Insira aqui as matérias obrigatórias para o terceiro ano: ";
    for (int i = 0; i < qtdMaterias3; ++i) {
        cin >> nomeDisc;
        auto disc = buscarDisciplinaPorNome(disciplinas, nomeDisc);
        if ( disc == nullptr ){
            disc = make_shared<Disciplina>(++ctDisc, nomeDisc);
            disciplinas.push_back(disc);
        }
        obrigatoriasTerceiro.push_back(disc);
    }
    vector<int> cargaHorariaTerceiro;
    for (const auto& i : obrigatoriasTerceiro){
        cout << "Insira a carga Horária da disciplina " << i->nome << " para o Terceiro ano: ";
        cin >>  ch;
        cargaHorariaTerceiro.push_back(ch);
    }

    // Lógica final da criação de turmas depois de coletar todos os dados
    for (int i = 0; i < qtd1; ++i) {
        turmas.push_back(make_shared<Turma>(
                    anoEscolar::PRIMEIRO_ANO,
                    ++ctTurma,
                    obrigatoriasPrimeiro,
                    cargaHorariaPrimeiro
                    )
                );
    }
    for (int i = 0; i < qtd2; ++i) {
        turmas.push_back(make_shared<Turma>(anoEscolar::SEGUNDO_ANO,
                    ++ctTurma,
                    obrigatoriasSegundo,
                    cargaHorariaSegundo
                    )
                );
    }
    for (int i = 0; i < qtd3; ++i) {
        turmas.push_back(make_shared<Turma>(anoEscolar::TERCEIRO_ANO,
                    ++ctTurma,
                    obrigatoriasTerceiro,
                    cargaHorariaTerceiro
                    )
                );
    }

    // Lógica de adicionar professores
    cout << "Agora adicione o nome dos professores, associados a suas respectivas disciplinas:\n ";
    string nomeProf;
    for (size_t i = 0; i < disciplinas.size(); ++i){
        cout << "-> Professor de " << disciplinas[i]->nome << ": "; 
        cin >> nomeProf;
        professores.push_back(make_shared<Professor>(++ctProf, nomeProf, disciplinas[i]));
    }

    // Lógica para adicionar salas
    cout << "Quantas salas tem na escola? ";
    cin >> qtdSalas;
    for (int i = 0; i < qtdSalas; ++i){
        salas.push_back(make_shared<Sala>(++ctSala));
    }

    // Instanciar as classes 'aula'
    size_t salaUsada = 0;
    for (auto &t : turmas) {
        for (size_t i = 0; i < t->disciplinasObrigatorias.size(); ++i) {
            auto &d = t->disciplinasObrigatorias[i];
            for (size_t j = 0; j < t->cargaHorariaPorDisciplina[i]; ++j) {
                aulas.push_back(make_shared<Aula>(
                            ++ctAula,
                            buscarProfessorPorDisciplina(professores, d),
                            t,
                            salas[salaUsada]
                            ));
                salaUsada = (salaUsada + 1) % qtdSalas ;
            }
        }
    }

    // TESTANDO NOSSOS CASOS DE TESTE:
    cout << "\n\n\n=-=-=-=-=-=TESTANDO OS CASOS DE TESTE =-=-=-=-=-=" << endl;
    cout << endl << "LISTANDO TODAS AS DISCIPLINAS: " << endl;
    for (auto i : disciplinas){
        cout << "Id: " << i->id << " | Nome: " << i->nome << endl;
    }
    cout << endl;
    cout << endl << "LISTANDO TODOS OS PROFS: " << endl;
    for (auto i : professores){
        cout << "Id: " << i->id << " | Nome: " << i->nome << " | Disciplina: " << i->materiaLecionada->nome << endl;
    }
    cout << endl;
    cout << endl << "LISTANDO TODAS AS TURMAS: " << endl;
    for (const auto& i : turmas){
        cout << "----------------------------------------" << endl;
        cout << "Turma ID: " << i->id << " | Ano Escolar: ";

        // Convertendo o enum para um texto legível na tela
        switch(i->serie) {
            case anoEscolar::PRIMEIRO_ANO: cout << "1o Ano"; break;
            case anoEscolar::SEGUNDO_ANO:  cout << "2o Ano"; break;
            case anoEscolar::TERCEIRO_ANO: cout << "3o Ano"; break;
            default:                       cout << "Desconhecido"; break;
        }
        cout << endl;

        cout << "  Grade Curricular desta Turma:" << endl;

        for (size_t j = 0; j < i->disciplinasObrigatorias.size(); ++j) {
            cout << "    -> " << i->disciplinasObrigatorias[j]->nome 
                << " | Carga Horaria: " << i->cargaHorariaPorDisciplina[j] << " aulas" << endl;
        }
    }
    cout << "----------------------------------------" << endl;

    cout << endl << "LISTANDO TODAS AS SALAS: " << endl;
    for (const auto& i : salas){
        cout << "Sala ID: " << i->id << endl;
    }

    cout << endl << "LISTANDO TODAS AS AULAS: " << endl;
    for (auto& i : aulas){
        cout << "Aula ID: "
            << i->id
            << endl
            << "├── "
            << "Turma ID: " << i->turma->id
            << endl
            << "├── "
            << "Professor: "
            << i->prof->nome
            << endl
            << "├── "
            << "Matéria: "
            << i->prof->materiaLecionada->nome
            << endl
            << "└── "
            << "Sala: "
            << i->sala->id
            << endl;
    }

    size_t a = 0;
    size_t b = 10;

    cout
        << endl << endl
        << "----------------------------------------"
        << endl
        << "Teste de Conflito:"
        << endl
        << "----------------------------------------"
        << endl << endl;


    if (conflito(aulas[a], aulas[b])) {
        cout
            << "Conflito: Aula " << aulas[a]->id << " e Aula " << aulas[b]->id
            << endl
            << "├── Sala " << aulas[a]->sala->id << " e Sala " << aulas[b]->sala->id
            << endl
            << "├── Turma " << aulas[a]->turma->id << " e Turma " << aulas[b]->turma->id
            << endl
            << "└── Prof. " << aulas[a]->prof->nome << " e Prof. " << aulas[b]->prof->nome
            << endl;
    }
}
