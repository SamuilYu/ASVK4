#include "Graphs/GraphFactory.h"
#include "Arithmetic/NewOperators.h"
#include "iostream"

int main() {
    auto gf = GraphFactory();
    auto w = gf.create("weighted", {'A', 'B', 'X', 'Y'},
                       {{'A', 'B', 1.23}, {'A', 'X', 5.53}, {'X', 'Y', 1.13}});
    auto g = gf.create("bipartite",{'A', 'B', 'C'}, {'E', 'D'},
                       {{'A', 'E'}, {'B', 'E'}, {'C', 'D'}});
    auto h = gf.create("bipartite",{'A', 'X', 'Y'}, {'B', 'D'},
                       {{'A', 'B'}, {'B', 'X'}, {'X', 'D'}});
//    auto g = gf.create("complete",{'A', 'B', 'C', 'F', 'H'});
//    auto h = gf.create("complete",{'A', 'B', 'E'});
    std::cout << g->toString() << endl << w->toString() << endl;
    shared_ptr<TGraph> v = g - w;
    std::cout << v->toString() << endl;
}