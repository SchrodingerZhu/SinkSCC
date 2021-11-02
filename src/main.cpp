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

    {
        std::vector<size_t> nodes{
               0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12
        };
        Graph<size_t , VectorType> graph{nodes.begin(), nodes.end()};
        graph.connect(1, 2);
        graph.connect(2, 4);
        graph.connect(2, 5);
        graph.connect(2, 3);
        graph.connect(3, 6);
        graph.connect(5, 2);
        graph.connect(5, 6);
        graph.connect(5, 7);
        graph.connect(6, 3);
        graph.connect(6, 8);
        graph.connect(7, 8);
        graph.connect(7, 10);
        graph.connect(8, 11);
        graph.connect(9, 7);
        graph.connect(10, 9);
        graph.connect(11, 12);
        graph.connect(12, 10);
        auto scc = graph.scc();
        for (auto &i: scc) {
            for (auto &j: i) {
                std::cout << j << " ";
            }
            std::cout << std::endl;
        }
    }
    return 0;
}
