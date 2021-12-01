#ifndef SASVK4_TGRAPH_H
#define SASVK4_TGRAPH_H
#include <string>
#include <vector>
#include <memory>
using namespace std;
class Weighted;

class TGraph {
public:
    virtual std::string toString() const = 0;
    virtual std::vector<char> getVertices() const = 0;
    virtual std::vector<std::pair<char, char>> getEdges() const = 0;
    virtual shared_ptr<Weighted> asWeighted(double) = 0;

    virtual shared_ptr<TGraph> copy() const = 0;
};

#endif //SASVK4_TGRAPH_H
