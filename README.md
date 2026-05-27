# analisador-rotas-rede
Trabalho final da matéria de Estruturas de Dados 2, com grafos.

Integrantes: Henrique Catani e Mateus Roque

A análise de topologia e diagnóstico de rotas são essenciais no gerenciamento de redes.
Ferramentas como o traceroute mapeiam sequencialmente os roteadores (saltos) pelos quais
um pacote trafega até alcançar um destino final. Esse conjunto de dados pode ser modelado e
interpretado através de um Grafo, onde cada roteador com um endereço IP válido é tratado como
um vértice e cada enlace de comunicação direta atua como uma aresta direcionada. Este projeto
visa desenvolver uma aplicação que, a partir de logs de rede, construa essa topologia
dinamicamente em memória e aplique algoritmos para responder a consultas, consolidando
conceitos fundamentais da disciplina.
