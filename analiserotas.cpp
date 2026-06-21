// Trabalho Final ED2
// Henrique Catani e Mateus Roque

#include <iostream>
// #include "graph.cpp" // - ja incluido no parser
#include "parser.cpp"
#include <vector>
using namespace std;

string filename;

void exportarGrafo (graph::digraph& graph, const std::optional<std::vector<std::string>> &path_vector = std::nullopt);
void encontraMenorCaminho (graph::digraph& graph);

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        cerr << "Erro: Arquivo de log não fornecido.\n";
        cerr << "Uso: " << argv[0] << " <path_logfile>\n";
        return 1;
    }

    filename = argv[1];

    graph::digraph graph;
    if (!readLog(argv[1], graph)) {
        cerr << "Erro ao ler arquivo " << argv[1] << std::endl;
        return 1;
    }

    cout << "Grafo de roteamento inicializado!" << endl;
    cout << "Vértices únicos (IPS) " << graph.size() << " | " << "Arestas: " << graph.totalArestas() << endl;

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
        cout << "Opção: ";
        cin >> opcao;

        switch (opcao)
        {
        case 1:
            exportarGrafo(graph);
            break;
        case 2:
            encontraMenorCaminho(graph);
            break;
        case 3:
        {
            int diametro;
            diametro = graph.calc_diametro();
            cout << "Diâmetro do Grafo: " << diametro << endl;
            break;
        }
        case 4:
        {
            vector<string> vetor5IPs = graph.roteadoresCriticos();
            cout << "\nTop 5 endereços com maior Grau de Entrada(In-degree).\n";

            for (size_t i = 0; i < vetor5IPs.size(); i++)
            {
                cout << vetor5IPs[i];
                if (i + 1 < vetor5IPs.size()) // para n imprimir virgula no final
                    cout << ", ";
            }
            cout << endl;
            break;
        }
        case 0:
            break;
        }
    }
}

void exportarGrafo (
    graph::digraph &graph, const std::optional<std::vector<std::string>> &path_vector)
{
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
        graph.draw(graph::digraph::output_format::SCREEN, filename, path_vector);
        break;
    case 2:
        graph.draw(graph::digraph::output_format::PNG, filename, path_vector);
        break;
    case 3:
        graph.draw(graph::digraph::output_format::PDF, filename, path_vector);
        break;
    default:
        break;
    }
}

void encontraMenorCaminho(graph::digraph &graph)
{
    string origem, destino;

    cout << "Digite o IP de Origem: ";
    cin >> origem;
    cout << "Digite o IP de Destino: ";
    cin >> destino;

    vector<string> vetorMenorCaminho;
    vetorMenorCaminho = graph.shortest_path(origem, destino);
    cout << "\nMenor Caminho: ";

    for (size_t i = 0; i < vetorMenorCaminho.size(); i++)
    {
        cout << vetorMenorCaminho[i];
        if (i + 1 < vetorMenorCaminho.size())
            cout << " >> ";
    }
    cout << endl;
    exportarGrafo(graph, vetorMenorCaminho);
}
