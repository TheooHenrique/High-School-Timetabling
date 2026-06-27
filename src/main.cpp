#include "../include/ano.hpp"
#include "../include/aula.hpp"
#include "../include/disciplina.hpp"
#include "../include/professores.hpp"
#include "../include/salas.hpp"
#include "../include/turmas.hpp"

#include <iostream>
#include <string>
#include <vector>
#include <set>
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

vector<int> calcularGrau(vector<vector<shared_ptr<Aula>>> listaDeAdjacencia) {
    vector<int> listaDeGrau(listaDeAdjacencia.size());

    // Calcular o grau, que será o tamanho do nó referente ao vértice i
    // na lista de adjacência.
    for (size_t i = 0; i < listaDeAdjacencia.size(); i++)
        listaDeGrau[i] = listaDeAdjacencia[i].size();

    return listaDeGrau;
}

vector<int> dsatur(
        const vector<shared_ptr<Aula>>& aulas,
        const vector<vector<shared_ptr<Aula>>>& listaDeAdjacencia)
{
    int n = aulas.size();

    //====== Etapa 0) Estabelecer estruturas de dados representantes

    // A posição i corresponde ao vértice i e armazena sua cor:
    vector<int> cor(n, -1); // (-1 significa não colorido)
    // Grau de cada vértice:
    vector<int> grau = calcularGrau(listaDeAdjacencia);
    // Nível de saturação (cores vizinhas distintas) de cada vértice:
    vector<int> saturacao(n, 0);
    // O set é utilizado para a adição de apenas cores novas, sem repetição,
    // além de que para calcular a saturação, é só olhar o tamanho do set.
    vector<set<int>> coresVizinhas(n);

    //====== Etapa 1) Colorir o vértice de maior grau:

    int primeiro = 0;

    // Começar com o vértice de maior grau:
    for (int i = 1; i < n; i++)
        if (grau[primeiro] < grau[i])
            primeiro = i;
    cor[primeiro] = 0;

    // Atualizar os vizinhos que agora existe uma cor 0 adjacente.
    for (auto vizinho : listaDeAdjacencia[primeiro]) {
        int id = vizinho->id;
        coresVizinhas[id].insert(0);
        saturacao[id] = 1;
    }

    //====== Etapa 2) Processar todos os outros vértices
    for (int qtdColoridos = 1; qtdColoridos < n; qtdColoridos++) {

        //====== Etapa 2a) Escolher, de acordo com a lógica de saturação ou
        // de desempate do DSatur, o melhor vértice:

        int melhor = -1;
        // Percorrer todos os vértices não coloridos para
        // encontrar o "melhor" vértice 
        for (int i = 0; i < n; i++) {

            // Ignorar os vértices já coloridos:
            if (cor[i] != -1)
            {
                continue;
            }

            // O que seria escolher o "melhor":
            //   → 1° O mais saturado, de acordo com a lista de saturação.
            //   → 2° Em caso de empate, o de maior grau.
            //
            // OBS: como o loop pode estar na primeira iteração,
            // é preciso também tratar esse primeiro caso antes de tentar
            // acessar saturacao[melhor], onde o valor default de melhor
            // pode ser -1.

            if (melhor == -1)
            {
                melhor = i;
            }
            else if (saturacao[i] > saturacao[melhor])
            {
                melhor = i;
            }
            else if (saturacao[i] == saturacao[melhor])
            {
                if (grau[i] > grau[melhor])
                    melhor = i;
            }
        }

        //====== Etapa 2b) Escolher cor, preferencialmente sem "criar" uma nova.

        // Para cada vértice, temos cores que não podemos escolher.
        // Este set mantém apenas cores únicas (sem repetição),
        // com a busca e inserção O(log n)
        set<int> proibidas;

        // Olhar a cor do vizinho e "anotar" como cor proibida:
        for (auto vizinho : listaDeAdjacencia[melhor]) {

            int id = vizinho->id;

            if (cor[id] != -1)
                proibidas.insert(cor[id]);
        }

        // Escolher, finalmente, uma cor:
        //     Como a cor não pode ser igual a do vizinho, procura-se
        // a menor cor que não aparece entre os vizinhos. A menor cor,
        // é geralmente uma cor já existente, mas nem sempre.
        // Por exemplo:
        //     - Supondo um nó onde seus 3 vizinhos possuem cores 0, 2 e 4,
        // a "menor cor" seria a cor 1, que é uma cor já utilizada.
        //     - Considerando outro nó onde seus 4 vizinhos possuem cores 0,
        // 1, 2 e 3, a "menor cor" seria a cor 4, pois ela é a única diferente
        // dos seus vizinhos.

        int talvezCor = 0;
        const int MAX_AULAS_POR_TURMA_NO_DIA = 4;
        //essa é a magica (gambiarrenta) que pensei pra garantir que todos os dias sejam preenchidos.
        //Até que funciona bem pra inputs grandes, em combinação com a regra de que cada turma só pode ter 3 aulas da mesma matéria por dia.
        if (n >= 5 && qtdColoridos < 5) {
            talvezCor = qtdColoridos * 12; //são 12 horarios por dia, preguica  de botar como variavel
        }

        while (true) {
            // Se a cor já é usada por um vizinho, pula.
            if (proibidas.count(talvezCor)) {
                talvezCor++;
                continue;
            }

            int diaAlvo = talvezCor / 12;
            int aulasMesmaDisciplinaNoDia = 0;
            int totalAulasDaTurmaNoDia = 0;

            // Varre as aulas já coloridas
            for (int i = 0; i < n; i++) {
                if (cor[i] != -1 && (cor[i] / 12) == diaAlvo) {
                    //se é mesma aula e mesmo prof, conta pra limitar as aulas por dias em 3
                    if (aulas[i]->turma == aulas[melhor]->turma) {
                        totalAulasDaTurmaNoDia++;
                        if (aulas[i]->prof->materiaLecionada == aulas[melhor]->prof->materiaLecionada){
                            aulasMesmaDisciplinaNoDia++;
                        }
                        
                    }
                }
            }

            //limita de fato as aulas por dia em 3
            if (aulasMesmaDisciplinaNoDia >= 3) {
                talvezCor++;
                continue; 
            }

            if (totalAulasDaTurmaNoDia >= MAX_AULAS_POR_TURMA_NO_DIA) {
                // Pula direto para o primeiro horário do próximo dia para acelerar o algoritmo
                talvezCor = (diaAlvo + 1) * 12;
                continue;
            }

            //se passou por todas as validações, é a cor ótima
            break;
        }

        // Finalmente, colorir o melhor vértice com a menor cor
        cor[melhor] = talvezCor;

        //====== Etapa 2c) Atualizar a lista de saturação e a lista
        // de cores vizinhas com a nova cor.
        for (auto vizinho : listaDeAdjacencia[melhor]) {

            int id = vizinho->id;

            if (cor[id] == -1) {
                coresVizinhas[id].insert(talvezCor);
                saturacao[id] = coresVizinhas[id].size();
            }
        }
}

return cor;
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

    vector<vector<shared_ptr<Aula>>> listaDeAdjacencia;

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
    for (int i = 0; i < qtdMaterias1; ++i) {
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
    for (const auto& i : obrigatoriasPrimeiro) {
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
    for (size_t i = 0; i < disciplinas.size(); ++i) {
        cout << "-> Professor de " << disciplinas[i]->nome << ": "; 
        cin >> nomeProf;
        professores.push_back(make_shared<Professor>(++ctProf, nomeProf, disciplinas[i]));
    }

    // Lógica para adicionar salas
    cout << "Quantas salas tem na escola? ";
    cin >> qtdSalas;
    for (int i = 0; i < qtdSalas; ++i) {
        salas.push_back(make_shared<Sala>(++ctSala));
    }

    // Instanciar as classes 'aula'
    size_t salaUsada = 0;
    for (auto &t : turmas) {
        for (size_t i = 0; i < t->disciplinasObrigatorias.size(); ++i) {
            auto &d = t->disciplinasObrigatorias[i];
            for (int j = 0; j < t->cargaHorariaPorDisciplina[i]; ++j) {
                aulas.push_back(make_shared<Aula>(
                            ctAula++,
                            buscarProfessorPorDisciplina(professores, d),
                            t,
                            salas[salaUsada]
                            ));
                salaUsada = (salaUsada + 1) % qtdSalas ;
            }
        }
    }

    // Criando a lista de adjacência
    for (size_t aula = 0; aula < aulas.size(); ++aula) {
        vector<shared_ptr<Aula>> conflitos;
        for (auto &outra_aula : aulas) {
            if (aulas[aula] != outra_aula) {
                if (conflito(aulas[aula], outra_aula)) {
                    conflitos.push_back(outra_aula);
                }
            }
        }
        listaDeAdjacencia.push_back(conflitos);
    }

    vector<int> cores = dsatur(aulas, listaDeAdjacencia);

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

    cout
        << "----------------------------------------"
        << endl
        << "Listando adjacências:"
        << endl
        << "----------------------------------------"
        << endl << endl;

    for (size_t vert = 0; vert < listaDeAdjacencia.size(); ++vert) {
        cout << "Vértice " << vert << ": ";
        if (listaDeAdjacencia[vert].size() == 0) cout << endl;
        for (auto &adjacente : listaDeAdjacencia[vert]) {
            if (adjacente == listaDeAdjacencia[vert].back()) {
                cout << adjacente->id << endl;
            } else {
                cout << adjacente->id << ", ";
            }
        }
    }

    cout
        << "----------------------------------------"
        << endl
        << "DSatur:"
        << endl
        << "----------------------------------------"
        << endl << endl;


    vector<string> dias = {"Segunda", "Terça", "Quarta", "Quinta", "Sexta"};
    vector<string> turnos = {"07:00 - 07:50", "07:50 - 08:40", "08:50 - 9:40", "09:40 - 10:30", "10:40 - 11:30", "11:30 - 12:20", "13:00 - 13:50", "13:50 - 14:40", "14:50 - 15:40", "15h40 - 16:30", "16:40 - 17:30", "17:30 - 18:20"};
    
    int aulasPorDia = 12; 
    //vou deixar isso aqui variável ao invés de deixar 60 hardcoded
    int totalHorariosDisponiveis = dias.size() * aulasPorDia;

    bool alcancouLimite = false;
    for (int c : cores) {
        if (c >= totalHorariosDisponiveis) {
            alcancouLimite = true;
            break;
        }
    }

    if (alcancouLimite) {
        cout << "\n====================================================\n";
        cout << "   AVISO: IMPOSSÍVEL CALCULAR O CRONOGRAMA!\n";
        cout << "====================================================\n";
        cout << "O problema inserido possui restrições severas demais ou\n"
             << "uma carga horária que ultrapassa os " << totalHorariosDisponiveis << " slots disponíveis.\n"
             << "Reduza o número de aulas ou aumente a grade da escola.\n";
        cout << "====================================================\n\n";
        return 0; 
    }

    cout << "\n================ CRONOGRAMA ESCOLAR ================\n";
    set<int> coresUnicasUtilizadas;

    for (size_t i = 0; i < aulas.size(); ++i) {
        int corAlocada = cores[i];
        
        if (corAlocada == -1) {
            cout << "Aula " << aulas[i]->id << " [" << aulas[i]->prof->materiaLecionada->nome << "] -> NÃO ALOCADA" << endl;
            continue;
        }
        coresUnicasUtilizadas.insert(corAlocada);
        //aquele mesmo esquema que a gente fez pra a logica de salas usadas
        int indiceDia = corAlocada / aulasPorDia;
        int indiceTurno = corAlocada % aulasPorDia;

        cout << "Aula " << aulas[i]->id << " | "
             << "Turma: " << static_cast<int>(aulas[i]->turma->serie) << "º Ano | "
             << "Prof: " << aulas[i]->prof->nome << " (" << aulas[i]->prof->materiaLecionada->nome << ") | "
             << "Sala: " << aulas[i]->sala->id << " | "
             << "Data: " << dias[indiceDia] << " às " << turnos[indiceTurno] << endl;
    }

    cout << endl
        << "Total de horarios necessarios: "
        << coresUnicasUtilizadas.size()
        << endl;
}
