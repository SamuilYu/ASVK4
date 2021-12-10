#ifndef GRAPHS_FACTORY_H
#define GRAPHS_FACTORY_H

#include <string>
#include <map>
#include <utility>
#include <vector>
#include "TGraph.h"
#include "Simple.h"
#include "Complete.h"
#include "Bipartite.h"
#include "Weighted.h"

using vertices = set<char>;
using edges = set<pair<char, char>>;
using weightedEdges = set<triple<char, char, double>>;

class GraphFactory {
private:
    class ICreator {
    public:
        virtual shared_ptr<TGraph> create(vertices) = 0;
        virtual shared_ptr<TGraph> create(vertices, edges) = 0;
        virtual shared_ptr<TGraph> create(vertices, vertices) = 0;
        virtual shared_ptr<TGraph> create(vertices, weightedEdges) = 0;
        virtual shared_ptr<TGraph> create() = 0;
    };

    template<class T>
    class Creator: public ICreator{
    public:
        shared_ptr<TGraph> create(vertices v) override {
            if constexpr(is_constructible_v<T, vertices>) {
                return make_shared<T>(T(v));
            }
            return nullptr;
        }

        shared_ptr<TGraph> create() override {
            if constexpr (is_constructible_v<T>) {
                return make_shared<T>(T());
            }
            return nullptr;

        }

        shared_ptr<TGraph> create(vertices v, edges e) override {
            if constexpr (is_constructible_v<T, vertices, edges>) {
                return make_shared<T>(T(v, e));
            }
            return nullptr;
        }

        shared_ptr<TGraph> create(vertices v1, vertices v2) override {
            if constexpr (is_constructible_v<T, vertices, vertices>) {
                return make_shared<T>(T(v1, v2));
            }
            return nullptr;
        }

        shared_ptr<TGraph> create(vertices v, weightedEdges e) override {
            if constexpr (is_constructible_v<T, vertices, weightedEdges>) {
                return make_shared<T>(T(v, e));
            }
            return nullptr;
        }
    };

    map<string, shared_ptr<ICreator>> registered;

    void registerAll() {
        registered["simple"] = make_shared<Creator<Simple>>();
        registered["complete"] = make_shared<Creator<Complete>>();
        registered["bipartite"] = make_shared<Creator<Bipartite>>();
        registered["weighted"] = make_shared<Creator<Weighted>>();
    }

public:
    GraphFactory() {
        registerAll();
    }

    shared_ptr<TGraph> create(const string& type, vertices v) {
        return registered[type]->create(v);
    }

    shared_ptr<TGraph> create(const string& type) {
        return registered[type]->create();
    }

    shared_ptr<TGraph> create(const string& type, vertices v, edges e) {
        return registered[type]->create(v, e);
    }

    shared_ptr<TGraph> create(const string& type, vertices v1, vertices v2) {
        return registered[type]->create(v1, v2);
    }

    shared_ptr<TGraph> create(const string& type, vertices v, weightedEdges e) {
        return registered[type]->create(v, e);
    }

};


#endif //GRAPHS_FACTORY_H
