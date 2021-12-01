#include "Graphs/Simple.h"
#include "Graphs/Complete.h"
#include "Graphs/Bipartite.h"
#include "Graphs/Weighted.h"
#include "iostream"

int main() {
    auto g = Complete({'A', 'B', 'C', 'D', 'E'}).copy();
    std::cout << g ->asWeighted(1.2) -> toString();
}