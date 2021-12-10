#ifndef GRAPHS_COMPLETE_H
#define GRAPHS_COMPLETE_H
#include "Simple.h"

class Complete: public Simple {
public:
    Complete();
    explicit Complete(set<char>);
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
