#ifndef GRAPHS_WEIGHTED_H
#define GRAPHS_WEIGHTED_H
#include "tuple"
#include "map"
#include "algorithm"
#include "Simple.h"


class Weighted: public Simple {
private:
    std::map<std::pair<char, char>, double> weights;
    void insideString(ostringstream &) const override;
    set<triple<char, char, double>> toTripleSet(map<pair<char, char>, double> map1) {
        set<triple<char, char, double>> set1 = {};
        for (auto pair: map1) {
            set1.insert({pair.first.first, pair.first.second, pair.second});
        }
        return set1;
    }
    set<char> getNeighbors(char);
    static char getUnvisitedMinimum(map<char, pair<double, vector<char>>> map1, set<char> set1);
public:
    Weighted();
    explicit Weighted(set<char>, set<triple<char, char, double>>);
    explicit Weighted(set<char>, set<std::pair<char, char>>, double);
    Weighted(const Weighted&) = default;

    explicit Weighted(set<char> v, set<pair<char, char>> e) {
        Weighted(v, e, 1.0);
    }
    explicit Weighted(set<char>, set<char>) {
        throw invalid_argument("Does not support these constructor arguments");
    }
    explicit Weighted(set<char> v) { vertices = v; }

    [[nodiscard]] std::string toString() const override;

    [[nodiscard]] shared_ptr<TGraph> copy() const override;

    vector<char> shortestPath(char, char) override;

    Weighted operator+(const Weighted& other) {
        auto newVertices = this->vertices;
        auto newWeights = this->weights;
        newVertices.insert(other.vertices.begin(), other.vertices.end());
        newWeights.insert(other.weights.begin(), other.weights.end());
        return Weighted(newVertices, toTripleSet(newWeights));
    }

    Weighted operator-(const Simple& other) {
        decltype(vertices) newVertices;
        decltype(weights) newWeights = {};
        auto otherEdges = other.getEdges();
        auto otherVertices = other.getVertices();
        decltype(vertices) verticesSet = {otherVertices.begin(), otherVertices.end()};
        for (auto& vertex: this->vertices) {
            if (verticesSet.find(vertex) == verticesSet.end()) {
                newVertices.insert(vertex);
            }
        }
        for (auto weight: this->weights) {
            if (newVertices.find(weight.first.first) != newVertices.end()
                && newVertices.find(weight.first.second) != newVertices.end()
                && std::find(otherEdges.begin(), otherEdges.end(), weight.first) == otherEdges.end()) {
                newWeights.insert(weight);
            }
        }
        return Weighted(newVertices, toTripleSet(newWeights));
    }
};


#endif //GRAPHS_WEIGHTED_H
