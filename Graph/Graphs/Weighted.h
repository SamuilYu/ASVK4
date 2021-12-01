#ifndef GRAPHS_WEIGHTED_H
#define GRAPHS_WEIGHTED_H
#include "tuple"
#include "map"
#include "Simple.h"


class Weighted: public Simple {
private:
    std::map<std::pair<char, char>, double> weights;
    void insideString(ostringstream &) const override;
public:
    Weighted();
    explicit Weighted(set<char>, set<triple<char, char, double>>);
    explicit Weighted(set<char>, set<std::pair<char, char>>, double);
    Weighted(const Weighted&) = default;

    explicit Weighted(set<char> v, set<pair<char, char>> e) {
        Weighted(v, e, 1.0);
    }
    explicit Weighted(set<char>, set<char>, set<pair<char, char>>) {
        throw invalid_argument("Does not support these constructor arguments");
    }
    explicit Weighted(set<char> v) { vertices = v; }

    [[nodiscard]] std::string toString() const override;

    [[nodiscard]] shared_ptr<TGraph> copy() const override;
};


#endif //GRAPHS_WEIGHTED_H
