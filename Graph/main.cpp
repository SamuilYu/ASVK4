#include "Graphs/Simple.h"
#include "Graphs/Complete.h"
#include "Graphs/Bipartite.h"
#include "iostream"

int main() {
    auto g = Bipartite({'A', 'B'}, {'C', 'D', 'E'},
                       {{'A', 'C'}, {'A', 'D'},
                        {'B', 'D'}, {'B', 'E'}}).copy();
    std::cout << g -> toString();
}