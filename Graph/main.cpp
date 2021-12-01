#include "Graphs/Simple.h"
#include "iostream"

int main() {
    auto g = Simple({'A', 'B', 'C'}, {{'A', 'B'}, {'B', 'C'}});
    std::cout << g.toString();
}