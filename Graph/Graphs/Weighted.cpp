//
// Created by samuil on 01.12.2021.
//

#include "Weighted.h"
#include "sstream"
#include "float.h"

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

vector<char> Weighted::shortestPath(char source, char sink) {
    map<char, pair<double, vector<char>>> currentDistance;
    set<char> unvisited = {};
    if (vertices.find(source) == vertices.end()) {
        throw invalid_argument("A source vertex is not present in graph.");
    }
    if (vertices.find(sink) == vertices.end()) {
        throw invalid_argument("A sink vertex is not present in graph.");
    }
    for (auto vertex: vertices) {
        if (vertex == source) {
            currentDistance.insert({vertex, {0.0, {vertex}}});
        } else {
            currentDistance.insert({vertex, {DBL_MAX, {}}});
        }
        unvisited.insert(vertex);
    }

    char current = source;
    set<char> neighbors = {};
    do {
        current = getUnvisitedMinimum(currentDistance, unvisited);
        neighbors = getNeighbors(current);
        for (auto neighbor: neighbors) {
            if (unvisited.find(neighbor) == unvisited.end()) {
                continue;
            }
            char first = current > neighbor ? current : neighbor;
            char second = current > neighbor ? neighbor : current;
            double candidateDist =
                    currentDistance.at(current).first +
                    weights.at({first, second});
            double currentDist  =
                    currentDistance.at(neighbor).first;
            if (candidateDist < currentDist) {
                vector<char> nextPath = currentDistance.at(current).second;
                nextPath.push_back(neighbor);
                currentDistance[neighbor] = {candidateDist, nextPath};
            }
        }
        unvisited.erase(current);
    } while (!unvisited.empty());
    return (currentDistance.at(sink)).second;
}

set<char> Weighted::getNeighbors(char source) {
    set<char> neighbors = {};
    for (auto& edge: edges) {
        if (source == edge.first) {
            neighbors.insert(edge.second);
        }
        if (source == edge.second) {
            neighbors.insert(edge.first);
        }
    }
    return neighbors;
}

char Weighted::getUnvisitedMinimum(map<char, pair<double, vector<char>>> map1, set<char> set1) {
    auto minimum = DBL_MAX;
    char minimumNode;
    for (auto& each: map1) {
        if (set1.find(each.first) == set1.end()) {
            continue;
        }
        if (each.second.first < minimum) {
            minimum = each.second.first;
            minimumNode = each.first;
        }
    }
    return minimumNode;
}

shared_ptr<Weighted> asWeightedFriend(const Simple& simple, double defaultValue) {
    auto w = Weighted(simple.vertices, simple.edges, defaultValue);
    return make_shared<Weighted>(w);
}
