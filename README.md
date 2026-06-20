# analisador-rotas-rede
Trabalho final da matéria de Estruturas de Dados 2, com grafos.

Integrantes: Henrique Catani e Mateus Roque

Esse programa reconstrói e analisa uma rede com logs de traceroute, com grafo direcionado não ponderado e lista de adjacência.

```main.cpp```: recebe os argumentos (argc/argv), instancia o grafo, chama a função de leitura e o menu  

```parser.cpp```: abrir o arquivo .log, ler as linhas e inserir os dados no grafo  

```graph.cpp```: biblioteca, mudanças: não duplicar arestas, graphviz com destaques, calculo do diametro e roteadores criticos (maior indegree)


## Build

#### Requisitos
Linux: ```g++``` (compilador c++), ```graphviz``` (visualizador dos grafos)

Ex., no Debian e derivados:
~~~
sudo apt install build-essential graphviz
~~~

### Compilar 
~~~
make
~~~
Isso irá gerar um executável chamado ```graphroute```.  

  
#### Alternativa
~~~
g++ -o graphroute analiserotas.cpp graph.cpp parser.cpp -Wl,--allow-multiple-definition
~~~


## Executar
O programa recebe um argumento na linha de comando, o caminho do arquivo de log. Exemplo:
~~~
./graphroute input_1.log
~~~