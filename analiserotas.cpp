// Trabalho Final ED2
#include <iostream>
#include "graph.cpp"
#include "parser.cpp"
using namespace std;

// Commit fazendo um esboço de como sera o output do terminal
int main(int argc, char* argv[]){
    if (argc < 2) {
        cerr << "Erro: Arquivo de log não fornecido.\n";
        cerr << "Uso: " << argv[0] << " <path_logfile>\n";
        return 1;
    }

    graph::digraph graph;
    if (!readLog(argv[1], graph)) {
        cerr << "Erro ao ler arquivo " << argv[1] << std::endl;
        return 1;
    }

    cout << "Grafo de roteamento inicializado!" << endl;
    cout << "Vértices únicos (IPS) " << graph.size() << " | " << "Arestas: " << "graph.num_links()" << endl;

    int opcao = 1;
    while (opcao)
    {
        cout << "================================================" << endl;
        cout << "1. Exibir Grafo Completo" << endl;
        cout << "2. Encontrar Menor Caminho" << endl;
        cout << "3. Calcular o Diâmetro do Grafo" << endl;
        cout << "4. Identificar Roteadores Críticos" << endl;
        cout << "0. Sair" << endl;
        cout << "================================================" << endl;
        cin >> opcao;

        int origem, destino;
        switch (opcao){
            case 1:
                exportarGrafo("grafo_saida", graph);
                break;
            case 2:
                cout << "Digite o IP de Origem: ";
                cin >> origem;
                cout << "Digite o IP de Destino: ";
                cin >> destino;
                //Fazer encontrar menor caminho
            case 3:
                //Fazer calcular o diâmetro do grafo
            case 4:
                //Fazer Identificar Roteadores Críticos
            case 0: 
                break;
        }

    }

}

void exportarGrafo(const std::string& filename, graph::digraph& graph) {
    cout << "Selecione o formato de saída do Graphviz:" << endl;
    cout << "1. Tela" << endl;
    cout << "2. Imagem (PNG)" << endl;
    cout << "3. Documento (PDF)" << endl;

    int opcao;
    cout << "Opção: ";
    cin >> opcao;

    switch (opcao)
    {
    case 1:
        graph.draw(graph::digraph::output_format::SCREEN, filename);
        break;
    case 2:
        graph.draw(graph::digraph::output_format::PNG, filename);
        break;
    case 3:
        graph.draw(graph::digraph::output_format::PDF, filename);
        break;
    default:
        break;
    }
}