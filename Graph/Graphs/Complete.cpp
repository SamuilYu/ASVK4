#include <sstream>
#include "Complete.h"

Complete::Complete(): Simple() {}

Complete::Complete(set<char> v) {
    vertices = v;
    edges = {};
    for (auto& vert1: vertices) {
        for (auto& vert2: vertices) {
            if (vert1 != vert2) {
                char first = vert1 > vert2 ? vert1 : vert2;
                char second = vert1 > vert2 ? vert2 : vert1;
                edges.insert({first, second});
            }
        }
    }
}

shared_ptr<TGraph> Complete::copy() const {
    return make_shared<Complete>(*this);
}

std::string Complete::toString() const {
    std::ostringstream stream;
    stream << "===Complete===" << endl;
    this->insideString(stream);
    stream << endl << "==============";
    return stream.str();
}
