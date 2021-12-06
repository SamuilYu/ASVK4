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
    explicit Bipartite(set<char> v) {
        throw invalid_argument("Does not support these constructor arguments");
    }
    explicit Bipartite(set<char> v, set<triple<char, char, double>> e) {
        throw invalid_argument("Does not support these constructor arguments");
    }

    explicit Bipartite(set<char> v, set<pair<char, char>> e) {
        throw invalid_argument("Does not support these constructor arguments");
    }
    Bipartite(const Bipartite&) = default;

    [[nodiscard]] std::string toString() const override;

    [[nodiscard]] shared_ptr<TGraph> copy() const override;

    Bipartite operator+(const Bipartite& other) {
        auto newUpper = this->upper;
        auto newLower = this->lower;
        auto newEdges = this->edges;
        newUpper.insert(other.upper.begin(), other.upper.end());
        newLower.insert(other.lower.begin(), other.lower.end());
        newEdges.insert(other.edges.begin(), other.edges.end());
        return Bipartite(newUpper, newLower, newEdges);
    }

};


#endif //GRAPHS_BIPARTITE_H
