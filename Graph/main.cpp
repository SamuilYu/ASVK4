#include "Graphs/GraphFactory.h"
#include "Arithmetic/NewOperators.h"
#include "iostream"

int main() {
    auto gf = GraphFactory();
    auto g = gf.create("weighted",{'A', 'B'}, {{'A', 'B', 3.5}});
    auto h = gf.create("weighted",{'W', 'V', 'U'}, {{'W', 'U', 2.5}});
    std::cout << g->toString() << endl << h->toString() << endl;
    shared_ptr<TGraph> v = g + h;
    std::cout << v->toString() << endl;
}