/// biblioteca para grafos
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <queue>
#include <optional>

namespace graph
{

    class digraph
    {
    private:
        // nodos do grafo - VERTÍCES
        struct node
        {
            std::string value;
            std::vector<node *> links;
        };

        std::unordered_map<std::string, node> nodes;
        std::unordered_set<node *> visited;

    public:
        void insert_nodo(const std::string &s)
        {
            node aux;
            aux.value = s;
            nodes[s] = aux;
        }

        size_t size()
        {
            return nodes.size();
        }

        node *find(const std::string &s)
        {
            auto it = nodes.find(s); // find do unnorderedmap
            return it == nodes.end() ? nullptr : &it->second;
        }
        // Ja alterei para q verifique se ja tem link antes de linkar
        bool insert_link(const std::string &from, const std::string &to)
        {
            auto pfrom = find(from);
            if (pfrom == nullptr)
                return false;
            auto pto = find(to);
            if (pto == nullptr)
                return false;
            for (auto link : pfrom->links)
            {
                if (link == pto)
                {
                    return false;
                }
            }
            pfrom->links.push_back(pto); // Adiciona a aresta na lista de adjacencia
            return true;
        }

        size_t degree(const std::string &n)
        {
            auto p = find(n);
            if (p == nullptr)
            {
                return 0;
            }
            return indegree(n) + outdegree(n);
        }
        // usar o find para ser mais efetivo
        size_t indegree(const std::string &n)
        {
            auto p = find(n);
            if (p == nullptr)
            {
                return 0;
            }

            size_t qtd = 0;
            for (auto vertices : nodes)
            {
                for (auto link : vertices.second.links)
                {
                    if (link->value == n)
                    {
                        qtd++;
                    }
                }
            }
            return qtd;
        }

        // Caso nao exista retorna nullptr, deveria retornar 0
        size_t outdegree2(const std::string &n)
        {
            // return nodes.find(n)->second.links.size();
            auto p = find(n);
            return p == nullptr ? 0 : p->links.size();
        }

        size_t outdegree(const std::string &n)
        {
            auto node = find(n);
            if (node->value == n)
            {
                return node->links.size();
            }

            return 0;
        }

        int totalArestas(){
          int arestas = 0;
          for (auto nd : nodes)
              arestas += outdegree(nd.first);

          return arestas;
        }

        void export2dot(const std::string &filename)
        {
            std::ofstream dot(filename); // cria o arquivo
            dot << "digraph{\n";

            for (auto nd : nodes)
            {                                      // Percorre todos os nodos
                dot << "\t\"" << nd.first << "\""; // escreve o rotulo do nodo entre aspas
                if (nd.second.links.size() > 0)
                {
                    dot << " -> {";
                    for (auto vizinho : nd.second.links)
                    {
                        dot << "\"" << vizinho->value << "\" ";
                    }
                    dot << "}"; // Fecha chaves da lista dos vizinho
                }
                dot << ";\n";
            }
            dot << "}\n"; // Fecha chaves do digraph
        }

        // Pintando o nodo se o nodo estiver em path_vector
        void export2dot_visual (
            const std::string &filename, const std::vector<std::string> &path_vector)
        {
            std::ofstream dot(filename); // cria o arquivo
            dot << "digraph{\n";

            // dois loops pois eh necessario dizer a cor do nodo antes
            for (auto nd : nodes)
                if (std::find(path_vector.begin(), path_vector.end(), nd.first) != path_vector.end())
                    dot << "\t\"" << nd.first << "\" [style=filled, fillcolor=\"lightblue\"];\n";

            for (auto nd : nodes)
            {
                dot << "\t\"" << nd.first << "\"";
                if (nd.second.links.size() > 0)
                {
                    dot << " -> {";
                    for (auto vizinho : nd.second.links)
                        dot << "\"" << vizinho->value << "\" ";

                    dot << "};\n";
                }
            }
            dot << "}\n";
        }


        size_t calc_diametro()
        {
            size_t diametroMax = 0;
            for (auto nd : nodes)
            {
                size_t current_diameter = BFS_max_distance(nd.first);
                diametroMax = std::max(diametroMax, current_diameter);
            }
            return diametroMax;
        }

        size_t BFS_max_distance(const std::string &s)
        {
            auto p = find(s);
            if (!p)
                return 0;
            visited.clear();
            std::queue<node *> fila;

            fila.push(p);
            visited.insert(p);

            size_t maxDistance = 0;
 
            while (!fila.empty())
            {
                auto size = fila.size();
                bool achou = false;
                for (auto i = 0; i < size; i++)
                {
                    auto current = fila.front();
                    fila.pop();

                    for (auto vizinho : current->links)
                    {
                        if (visited.find(vizinho) == visited.end())
                        {
                            visited.insert(vizinho);
                            fila.push(vizinho);
                            achou = true;
                        }
                    }
                }
                if (achou)
                {
                    maxDistance++;
                }
            }
            return maxDistance;
        }

        enum class output_format
        {
            SCREEN,
            PNG,
            PDF
        };

        void draw (
            output_format format, std::string filename,
            const std::optional<std::vector<std::string>> &path_vector = std::nullopt)
        {
            // usando optionals para não colorir se o vetor for nulo

            filename.append(".dot");

            if (path_vector)
                export2dot_visual(filename, *path_vector);
            else
                export2dot(filename);

            std::string command;

            switch (format)
            {
            case output_format::SCREEN:
                command = "dot -Tx11 ";
                command.append(filename);
                break;
            case output_format::PNG:
                command = "dot -Tpng ";
                command.append(filename);
                command.append(" -o ");
                command.append(filename);
                command.append(".png");
                break;
            case output_format::PDF:
                command = "dot -Tpdf ";
                command.append(filename);
                command.append(" -o ");
                command.append(filename);
                command.append(".pdf");
                break;
            default:
                break;
            }

            const char *c_command = command.c_str();
            std::system(c_command);
        }
        

        std::vector<std::string> roteadoresCriticos()
        {
            // std pair pra dar push back em 2 parametros
            std::vector<std::pair<std::string, size_t>> vetor;
            std::vector<std::string> vetorRetorno;
            for (auto nd : nodes)
            {
                size_t ind = indegree(nd.second.value);

                if (vetor.size())
                {
                    int i = 0;  
                    bool achou = false;
                    for (auto p : vetor) {
                        // ordenando somente os 5 primeiros na inserção
                        if ((i < 5) && (p.second <= ind)) {
                            vetor.insert(vetor.begin() + i, {nd.second.value, ind});
                            achou = true;
                            break;
                        }
                        i++;
                    }
                    if(!achou) vetor.push_back({nd.second.value, ind});
                }
                else // insere a primeira vez
                    vetor.push_back({nd.second.value, ind});
            }
            
            // passa o a string(ip) do vetor
            int i = 0;
            for (auto v : vetor)
            {
                if (i < 5) vetorRetorno.push_back(v.first);
                i++;
            }
            return vetorRetorno;
        }

        void remove_link(const std::string &from, const std::string &to)
        {
            auto pfrom = find(from);
            if (!pfrom)
                return;
            auto pto = find(to);
            if (!pto)
                return;
            // Verifica se o destine esta na lista dos vizinhos da origem
            auto it = std::find(pfrom->links.begin(), pfrom->links.end(), pto);
            if (it == pfrom->links.end())
                return;             // Não é vizinho da origem
            pfrom->links.erase(it); // É vizinho será excluído
        }

        void remove_node(const std::string &key)
        {
            auto pkey = find(key);
            if (!pkey)
                return;
            for (auto vertice : nodes)
            { // for auto &[k,nd] : nodes ja pega o first e second
                remove_link(vertice.second.value, key);
            }
            nodes.erase(key);
            return;
        }
        
        void recursive_DFS(node *p, int level = 0)
        {
            if (visited.count(p)) // Já foi visited
                return;
            std::cout << std::string(level, '\t') << p->value << std::endl;
            visited.insert(p);
            for (auto in : p->links)
            {
                recursive_DFS(in, level + 1);
            }
        }

        void DFS_from(const std::string &s)
        {
            auto p = find(s); // Our find
            if (!p)
                return;
            visited.clear();
            recursive_DFS(p);
        }

        void BFS_from(const std::string &s)
        {
            auto p = find(s);
            if (!p)
                return;
            visited.clear();
            std::queue<node *> q;
            q.push(p);
            visited.insert(p);
            while (!q.empty())
            {
                auto current = q.front();
                q.pop();
                std::cout << current->value << " ";
                for (auto vizi : current->links)
                {
                    if (visited.count(vizi) == 0)
                    {
                        q.push(vizi);
                        visited.insert(vizi);
                    }
                }
            }
            std::cout << "\n";
        }

        std::vector<std::string> shortest_path(const std::string &from, const std::string &to)
        {
            std::vector<std::string> path;
            auto pfrom = find(from); // Our find
            if (pfrom == nullptr)
                return path;
            auto pto = find(to);
            if (pto == nullptr)
                return path;
            // node pointer
            std::unordered_map<node *, node *> source;
            std::queue<node *> queue;
            queue.push(pfrom);
            source[pfrom] = nullptr;
            bool found_path = false;
            while (!queue.empty())
            {
                auto current = queue.front();
                queue.pop();
                if (current == pto)
                {
                    found_path = true;
                    break;
                }
                for (auto &vizi : current->links)
                {
                    // Count how many times vizi is in source
                    if (source.count(vizi) == 0)
                    {
                        queue.push(vizi);
                        source[vizi] = current;
                    }
                }
            }
            if (found_path)
            {
                auto p = pto;
                while (p != nullptr)
                {
                    path.push_back(p->value);
                    p = source[p];
                }
                std::reverse(path.begin(), path.end());
            }
            return path;
        }

        bool existe_link(const std::string &from, const std::string &to)
        {
            auto pfrom = find(from); // Our find
            if (pfrom == nullptr)
                return false;
            auto pto = find(to);
            if (pto == nullptr)
                return false;

            for (auto link : pfrom->links)
            {
                if (link == pto)
                {
                    return true;
                }
            }
            return false;
        }

    }; /// fim da classe digraph

} // fim do namespace
