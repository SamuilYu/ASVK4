//
// Created by samuil on 01.12.2021.
//

#include <algorithm>
#include "Bipartite.h"
#include "set"
#include "stdexcept"
#include "sstream"

Bipartite::Bipartite(): Simple() {
    upper = {};
    lower = {};
}

Bipartite::Bipartite(
        set<char> v1,
        set<char> v2,
        set<pair<char, char>> e) {
    std::set<char> intersect;
    set_intersection(v1.begin(), v1.end(), v2.begin(), v2.end(),
                     std::inserter(intersect, intersect.begin()));
    if (!intersect.empty()) {
        throw logic_error("Upper and lower vertice sets intersect.");
    }
    upper = v1;
    lower = v2;
    v1.merge(v2);
    vertices = v1;

    edges = {};
    for (auto& edge : e) {
        if (vertices.find(edge.first) == vertices.end() ||
            vertices.find(edge.second) == vertices.end()) {
            throw std::logic_error("Cannot add edge with non-existent vertice.");
        } else if ((upper.find(edge.first) != upper.end() &&
                upper.find(edge.second) != upper.end()) ||
                (lower.find(edge.first) != lower.end() &&
                lower.find(edge.second) != lower.end())) {
            throw std::logic_error("Cannot connect vertices from the same parts.");
        } else {
            char first = edge.first > edge.second ? edge.first : edge.second;
            char second = edge.first > edge.second ? edge.second : edge.first;
            edges.insert({first, second});
        }
    }
}

shared_ptr<TGraph> Bipartite::copy() const {
    return make_shared<Bipartite>(*this);
}

std::string Bipartite::toString() const {
    std::ostringstream stream;
    stream << "===Bipartite===" << endl;
    this->insideString(stream);
    stream << endl << "===============";
    return stream.str();
}

void Bipartite::insideString(ostringstream &stream) const {
    stream << "Upper part:";
    for (auto& v: upper) {
        stream << " " << v;
    }
    stream << endl << "Lower part:";
    for (auto& v: lower) {
        stream << " " << v;
    }
    stream << endl << "Edges:";
    for (auto& e: edges) {
        stream << " " << e.first << e.second;
    }
}
