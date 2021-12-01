#include "Graphs/GraphFactory.h"
#include "iostream"

int main() {
    auto gf = GraphFactory();
    auto g = gf.create("complete", {'A', 'B', 'C', 'D', 'E'}, {{'A', 'B'}});
    std::cout << g -> asWeighted(1.2) -> toString();
}