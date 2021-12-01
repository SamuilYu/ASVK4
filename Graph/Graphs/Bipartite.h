#ifndef GRAPHS_BIPARTITE_H
#define GRAPHS_BIPARTITE_H
#include "Simple.h"

class Bipartite: public Simple {
private:
    std::set<char> upper;
    std::set<char> lower;
    void insideString(ostringstream &) const override;
public:
    Bipartite();
    explicit Bipartite(set<char>, set<char>, set<pair<char, char>>);
    Bipartite(const Bipartite&) = default;

    [[nodiscard]] std::string toString() const override;

    [[nodiscard]] shared_ptr<TGraph> copy() const override;

};


#endif //GRAPHS_BIPARTITE_H
