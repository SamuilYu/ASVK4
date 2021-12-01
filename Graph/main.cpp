#include "Graphs/Simple.h"
#include "Graphs/Complete.h"
#include "iostream"

int main() {
    auto g = Complete({'A', 'B', 'C', 'D'}).copy();
    std::cout << g -> toString();
}