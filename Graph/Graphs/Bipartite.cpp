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

Bipartite::Bipartite(set<char> v1, set<char> v2) {
    std::set<char> intersect;
    set_intersection(v1.begin(), v1.end(), v2.begin(), v2.end(),
                     std::inserter(intersect, intersect.begin()));
    if (!intersect.empty()) {
        throw invalid_argument("Upper and lower vertex sets intersect.");
    }
    upper = v1;
    lower = v2;
    v1.merge(v2);
    vertices = v1;

    edges = {};
    for (auto& vv1: upper) {
        for (auto &vv2: lower) {
            char first = vv1 > vv2 ? vv1 : vv2;
            char second = vv1 > vv2 ? vv2 : vv1;
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
