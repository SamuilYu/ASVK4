#ifndef GRAPHS_WEIGHTED_H
#define GRAPHS_WEIGHTED_H
#include "tuple"
#include "map"
#include "Simple.h"

template<typename T1, typename T2, typename T3>
using triple = std::tuple<T1, T2, T3>;

class Weighted: public Simple {
private:
    std::map<std::pair<char, char>, double> weights;
    void insideString(ostringstream &) const override;
public:
    Weighted();
    explicit Weighted(set<char>, set<triple<char, char, double>>);
    explicit Weighted(set<char>, set<std::pair<char, char>>, double);
    Weighted(const Weighted&) = default;

    [[nodiscard]] std::string toString() const override;

    [[nodiscard]] shared_ptr<TGraph> copy() const override;
};


#endif //GRAPHS_WEIGHTED_H
