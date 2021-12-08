#ifndef SASVK4_TGRAPH_H
#define SASVK4_TGRAPH_H
#include <string>
#include <vector>
#include <memory>
#include "set"
using namespace std;
class Weighted;

template<typename T1, typename T2, typename T3>
using triple = std::tuple<T1, T2, T3>;

class TGraph {
public:
    virtual std::string toString() const = 0;
    virtual std::set<char> getVertices() const = 0;
    virtual std::set<std::pair<char, char>> getEdges() const = 0;
    virtual shared_ptr<Weighted> asWeighted(double) = 0;
    virtual vector<char> shortestPath(char, char) = 0;

    virtual shared_ptr<TGraph> copy() const = 0;
};

#endif //SASVK4_TGRAPH_H
