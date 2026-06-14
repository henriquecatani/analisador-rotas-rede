#include <fstream>
#include <string>
#include "graph.cpp"

bool readLog(const std::string& filename, graph::digraph& graph) {
    std::ifstream file;
    file.open(filename);

    if (!file) {
        std::cerr << "Erro ao abrir o arquivo: " << filename << std::endl;
        return false;
    }
    std::string line; 
    std::getline(file, line); // ignore header

    while (std::getline(file, line))
    {
        size_t start = 0;

        for (int i = 0; i < 4; i++)
            start = line.find(',', start) + 1; // jump to hop_from

        size_t end = line.find(',', start);
        std::string hop_from = line.substr(start, end - start);

        start = end + 1;
        end = line.find(',', start);
        std::string hop_to = line.substr(start, end - start);

        if (hop_to != "*" && hop_from != "" && hop_to != "")
        {
            graph.insert_nodo(hop_from);
            graph.insert_nodo(hop_to);
            graph.insert_link(hop_from, hop_to);
        }
    }

    file.close();
    return true;
}