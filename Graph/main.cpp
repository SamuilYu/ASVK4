#include "Graphs/GraphFactory.h"
#include "Arithmetic/NewOperators.h"
#include "iostream"

int main() {
    auto gf = GraphFactory();
    auto w = gf.create("weighted", {'A', 'C', 'D', 'E', 'M', 'Z'},
                       {{'A', 'C', 1.0}, {'A', 'E', 1.0}, {'A', 'D', 2.0},
                        {'A', 'Z', 5.0}, {'C', 'M', 2.0}, {'M', 'Z', 1.0},
                        {'D', 'Z', 2.0}, {'E', 'Z', 3.0}, {'E', 'M', 1.0}});
//    auto g = gf.create("bipartite",{'A', 'B', 'C'}, {'E', 'D'},
//                       {{'A', 'E'}, {'B', 'E'}, {'C', 'D'}});
//    auto h = gf.create("bipartite",{'A', 'X', 'Y'}, {'N', 'D'},
//                       {{'A', 'N'}, {'N', 'X'}, {'X', 'D'}});
//    auto g = gf.create("complete",{'A', 'B', 'C', 'F', 'H'});
//    auto h = gf.create("complete",{'A', 'B', 'E'});
    std::cout << w->toString() << endl;
    auto path = w->shortestPath('A', 'Z');
    for (auto node: path) {
        std::cout << node;
    }
}