#include <iostream>
#include <scc/scc.h>
int main() {
    using namespace scc;
    {
        std::vector<std::string> nodes{
                "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L"
        };
        Graph<std::string, AssocMapType> graph{nodes.begin(), nodes.end()};
        graph.connect("A", "B");
        graph.connect("B", "D");
        graph.connect("B", "E");
        graph.connect("B", "C");
        graph.connect("C", "F");
        graph.connect("E", "B");
        graph.connect("E", "F");
        graph.connect("E", "G");
        graph.connect("F", "C");
        graph.connect("F", "H");
        graph.connect("G", "H");
        graph.connect("G", "J");
        graph.connect("H", "K");
        graph.connect("I", "G");
        graph.connect("J", "I");
        graph.connect("K", "L");
        graph.connect("L", "J");
        auto scc = graph.scc();
        for (auto &i: scc) {
            for (auto &j: i) {
                std::cout << j << " ";
            }
            std::cout << std::endl;
        }
    }
}
