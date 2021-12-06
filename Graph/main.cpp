#include "Graphs/GraphFactory.h"
#include "Arithmetic/NewOperators.h"
#include "iostream"

int main() {
    auto gf = GraphFactory();
    auto g = gf.create("bipartite",{'A', 'B'}, {'E', 'D'},
                       {{'A', 'E'}, {'B', 'E'}});
    auto h = gf.create("complete",{'W', 'V', 'U'});
    std::cout << g->toString() << endl << h->toString() << endl;
    shared_ptr<TGraph> v = h + g;
    std::cout << v->toString() << endl;
}