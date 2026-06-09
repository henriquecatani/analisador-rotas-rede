// Trabalho Final ED2
#include <iostream>
//#include "graph.cpp"
using namespace std;

// Commit fazendo um esboço de como sera o output do terminal
int main(int argv){
    cout << "Grafo de roteamento inicializado!" << endl;
    cout << "Vértices únicos (IPS) " << "criarVarVertices" << " | " << "Arestas: " << "criarVarArestas" << endl;
    int opcao = 1;
    while(opcao != 0){
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
                //Fazer exibir grafo
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