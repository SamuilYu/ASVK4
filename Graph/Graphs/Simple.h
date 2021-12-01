#ifndef SASVK4_SIMPLE_H
#define SASVK4_SIMPLE_H
#include "TGraph.h"
#include <string>
#include <vector>
#include <set>
#include <memory>
using namespace std;

class Simple: public TGraph {
protected:
    std::set<char> vertices;
    std::set<std::pair<char, char>> edges;
    virtual void insideString(ostringstream&) const;
public:
    Simple();
    explicit Simple(set<char>, set<pair<char, char>>);
    Simple(const Simple&) = default;

    [[nodiscard]] std::string toString() const override;
    [[nodiscard]] std::vector<char> getVertices() const override;
    [[nodiscard]] std::vector<std::pair<char, char>> getEdges() const override;

    [[nodiscard]] shared_ptr<TGraph> copy() const override;
};


#endif //SASVK4_SIMPLE_H
