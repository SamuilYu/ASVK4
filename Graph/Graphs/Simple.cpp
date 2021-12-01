#include "Simple.h"

#include "sstream"
#include <utility>
#include <stdexcept>

Simple::Simple(set<char> v, set<pair<char, char>> e) {
    vertices = std::move(v);
    edges = {};
    for (auto& edge : e) {
        if (vertices.find(edge.first) == vertices.end() ||
        vertices.find(edge.second) == vertices.end()) {
            std::ostringstream stream;
            stream << "Cannot add edge with non-existent vertice.";
            throw std::logic_error(stream.str());
        } else {
            char first = edge.first > edge.second ? edge.first : edge.second;
            char second = edge.first > edge.second ? edge.second : edge.first;
            edges.insert({first, second});
        }
    }
}

Simple::Simple() {
    vertices = {};
    edges = {};
}

std::vector<char> Simple::getVertices() const {
    return {vertices.begin(), vertices.end()};
}

std::vector<std::pair<char, char>> Simple::getEdges() const {
    return {edges.begin(), edges.end()};
}

std::string Simple::toString() const {
    std::ostringstream stream;
    stream << "===Simple===" << endl << "Vertices:";
    for (auto& v: vertices) {
        stream << " " << v;
    }
    stream << endl << "Edges:";
    for (auto& e: edges) {
        stream << " " << e.first << e.second;
    }
    stream << endl << "============";
    return stream.str();
}

shared_ptr<TGraph> Simple::copy() const {
    return make_shared<Simple>(*this);
}
