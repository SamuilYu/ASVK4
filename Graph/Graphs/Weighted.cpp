//
// Created by samuil on 01.12.2021.
//

#include "Weighted.h"
#include "sstream"

Weighted::Weighted(): Simple() {
    weights = {};
}

Weighted::Weighted(
        set<char> v, set<triple<char, char, double>> e) {
    vertices = std::move(v);
    edges = {};
    weights = {};
    for (auto& edge : e) {
        if (vertices.find(get<0>(edge)) == vertices.end() ||
            vertices.find(get<1>(edge)) == vertices.end()) {
            throw std::invalid_argument("Cannot add edge with non-existent vertex.");
        }

        char first = get<0>(edge) > get<1>(edge) ? get<0>(edge) : get<1>(edge);
        char second = get<0>(edge) > get<1>(edge) ? get<1>(edge) : get<0>(edge);
        pair<char, char> current = {first, second};
        if (edges.find(current) != edges.end()) {
            throw invalid_argument("Duplicated edge.");
        }
        edges.insert(current);
        weights[current] = get<2>(edge);
    }
}

Weighted::Weighted(set<char> v, set<pair<char, char>> e, double defaultValue) {
    vertices = std::move(v);
    edges = {};
    weights = {};
    for (auto& edge : e) {
        if (vertices.find(get<0>(edge)) == vertices.end() ||
            vertices.find(get<1>(edge)) == vertices.end()) {
            throw std::invalid_argument("Cannot add edge with non-existent vertex.");
        }

        char first = get<0>(edge) > get<1>(edge) ? get<0>(edge) : get<1>(edge);
        char second = get<0>(edge) > get<1>(edge) ? get<1>(edge) : get<0>(edge);
        pair<char, char> current = {first, second};
        edges.insert(current);
        weights[current] = defaultValue;
    }
}

std::string Weighted::toString() const {
    std::ostringstream stream;
    stream << "===Weighted===" << endl;
    this->insideString(stream);
    stream << endl << "==============";
    return stream.str();
}

void Weighted::insideString(ostringstream &stream) const {
    stream << "Vertices:";
    for (auto& v: vertices) {
        stream << " " << v;
    }
    stream << endl << "Edges:";
    for (auto& e: edges) {
        stream << " " << e.first << e.second << "-" << weights.at(e);
    }
}

shared_ptr<TGraph> Weighted::copy() const {
    return make_shared<Weighted>(*this);
}

shared_ptr<Weighted> asWeightedFriend(const Simple& simple, double defaultValue) {
    auto w = Weighted(simple.vertices, simple.edges, defaultValue);
    return make_shared<Weighted>(w);
}
