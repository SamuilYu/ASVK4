#ifndef GRAPHS_NEWOPERATORS_H
#define GRAPHS_NEWOPERATORS_H

#include "../Graphs/GraphFactory.h"
#include "stdexcept"

template <class A, class B,
        enable_if_t<!is_base_of_v<shared_ptr<TGraph>, A> ||
                !is_base_of_v<shared_ptr<TGraph>, B>, bool> = true>
shared_ptr<TGraph> operator+(const A&, const B&) {
    throw logic_error("Invalid operands for sum.");
}

template <class A, class B,
        enable_if_t<is_base_of_v<shared_ptr<TGraph>, A>
                && is_base_of_v<shared_ptr<TGraph>, B>, bool> = true>
shared_ptr<TGraph> operator+(A first, B second) {
    if (auto f = dynamic_pointer_cast<Bipartite>(first)) {
        if (auto s = dynamic_pointer_cast<Bipartite>(second)) {
            return make_shared<Bipartite>(*f + *s);
        }
    }
    if (auto f = dynamic_pointer_cast<Complete>(first)) {
        if (auto s = dynamic_pointer_cast<Complete>(second)) {
            return make_shared<Complete>(*f + *s);
        }
    }
    if (auto f = dynamic_pointer_cast<Weighted>(first)) {
        if (auto s = dynamic_pointer_cast<Weighted>(second)) {
            return make_shared<Weighted>(*f + *s);
        }
    }
}

#endif //GRAPHS_NEWOPERATORS_H
