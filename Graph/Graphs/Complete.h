#ifndef GRAPHS_COMPLETE_H
#define GRAPHS_COMPLETE_H
#include "Simple.h"

class Complete: public Simple {
public:
    Complete();
    explicit Complete(set<char>);
    explicit Complete(set<char> v, set<triple<char, char, double>> e) {
        throw invalid_argument("Does not support these constructor arguments");
    }
    explicit Complete(set<char>, set<pair<char, char>>) {
        throw invalid_argument("Does not support these constructor arguments");
    }
    explicit Complete(set<char>, set<char>, set<pair<char, char>>) {
        throw invalid_argument("Does not support these constructor arguments");
    }
    Complete(const Complete&) = default;

    [[nodiscard]] std::string toString() const override;

    [[nodiscard]] shared_ptr<TGraph> copy() const override;

    Complete operator+(const Complete& other) {
        auto newVertices = this->vertices;
        newVertices.insert(other.vertices.begin(), other.vertices.end());
        return Complete(newVertices);
    }

    Complete operator-(const Complete& other) {
        decltype(vertices) newVertices = {};
        for (auto& vertex: this->vertices) {
            if (other.vertices.find(vertex) == other.vertices.end()) {
                newVertices.insert(vertex);
            }
        }
        return Complete(newVertices);
    }
};


#endif //GRAPHS_COMPLETE_H
