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
};


#endif //GRAPHS_COMPLETE_H
