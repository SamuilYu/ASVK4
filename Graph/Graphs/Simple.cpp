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
            stream << "Cannot add edge with non-existent vertex.";
            throw std::invalid_argument(stream.str());
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

set<char> Simple::getVertices() const {
    return vertices;
}

set<pair<char, char>> Simple::getEdges() const {
    return edges;
}

std::string Simple::toString() const {
    std::ostringstream stream;
    stream << "===Simple===" << endl;
    this->insideString(stream);
    stream << endl << "============";
    return stream.str();
}

shared_ptr<TGraph> Simple::copy() const {
    return make_shared<Simple>(*this);
}

void Simple::insideString(ostringstream& stream) const {
    stream << "Vertices:";
    for (auto& v: vertices) {
        stream << " " << v;
    }
    stream << endl << "Edges:";
    for (auto& e: edges) {
        stream << " " << e.first << e.second;
    }
}

shared_ptr<Weighted> Simple::asWeighted(double d) {
     return asWeightedFriend(*this, d);
}

vector<char> Simple::shortestPath(char i, char i1) {
    throw logic_error("Cannot find shortest path in un-weighted graph");
}
