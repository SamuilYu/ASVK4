#ifndef SASVK4_SIMPLE_H
#define SASVK4_SIMPLE_H
#include "TGraph.h"
#include <string>
#include <vector>
#include <set>
#include <memory>
#include "stdexcept"
#include "algorithm"
#include "iostream"
using namespace std;

class Simple: public TGraph {
protected:
    std::set<char> vertices;
    std::set<std::pair<char, char>> edges;
    virtual void insideString(ostringstream&) const;
public:
    Simple();
    explicit Simple(set<char>, set<pair<char, char>>);
    explicit Simple(set<char> v) { vertices = v; }
    explicit Simple(set<char> v, set<triple<char, char, double>> e) {
        throw invalid_argument("Does not support these constructor arguments");
    }
    explicit Simple(set<char>, set<char>, set<pair<char, char>>) {
        throw invalid_argument("Does not support these constructor arguments");
    }

    Simple(const Simple&) = default;

    [[nodiscard]] std::string toString() const override;
    [[nodiscard]] std::vector<char> getVertices() const override;
    [[nodiscard]] std::vector<std::pair<char, char>> getEdges() const override;
    friend shared_ptr<Weighted> asWeightedFriend(const Simple&, double);
    shared_ptr<Weighted> asWeighted(double d) override;

    [[nodiscard]] shared_ptr<TGraph> copy() const override;

    Simple operator+(const Simple& other) {
        auto newVertices = this->vertices;
        auto newEdges = this->edges;
        newVertices.insert(other.vertices.begin(), other.vertices.end());
        newEdges.insert(other.edges.begin(), other.edges.end());
        return Simple(newVertices, newEdges);
    }

    Simple operator-(const Simple& other) {
        decltype(vertices) newVertices = {};
        decltype(edges) newEdges = {};

        for (auto& vertex: this->vertices) {
            if (other.vertices.find(vertex) == other.vertices.end()) {
                newVertices.insert(vertex);
            }
        }
        for (auto& edge: this->edges) {
            if (newVertices.find(edge.first) != newVertices.end()
            && newVertices.find(edge.second) != newVertices.end()
            && other.edges.find(edge) == other.edges.end()) {
                newEdges.insert(edge);
            }
        }
        return Simple(newVertices, newEdges);
    }

};


#endif //SASVK4_SIMPLE_H
