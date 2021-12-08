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
    explicit Bipartite(set<char>, set<char>);
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
        newUpper.insert(other.upper.begin(), other.upper.end());
        newLower.insert(other.lower.begin(), other.lower.end());
        return Bipartite(newUpper, newLower);
    }

    Bipartite operator-(const Bipartite& other) {
        decltype(upper) newUpper;
        decltype(lower) newLower;
        decltype(edges) newEdges;
        for (auto& vertex: this->upper) {
            if (other.upper.find(vertex) == other.upper.end()) {
                newUpper.insert(vertex);
            }
        }
        for (auto& vertex: this->lower) {
            if (other.lower.find(vertex) == other.lower.end()) {
                newLower.insert(vertex);
            }
        }
        return Bipartite(newUpper, newLower);
    }
};


#endif //GRAPHS_BIPARTITE_H
