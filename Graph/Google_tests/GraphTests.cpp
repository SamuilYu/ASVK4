#include "gtest/gtest.h"
#include "../Graphs/GraphFactory.h"
#include "stdexcept"
#include <iostream>

class GraphTests : public ::testing::Test {
public:
    GraphFactory factory;
    std::shared_ptr<TGraph> a, b;
};


TEST_F(GraphTests, Simple) {
    a = factory.create("simple", {'A', 'B', 'C', 'D'},
                       {{'A', 'B'}, {'B', 'C'}, {'B', 'D'}});
    auto vertices1 = a->getVertices();
    auto edges1 = a->getEdges();
    decltype(vertices1) vertices2 = {'A', 'B', 'C', 'D'};
    decltype(edges1) edges2 = {{'B', 'A'}, {'C', 'B'}, {'D', 'B'}};
    EXPECT_EQ(vertices1, vertices2);
    EXPECT_EQ(edges1, edges2);
}

TEST_F(GraphTests, Complete) {
    a = factory.create("complete", {'A', 'B', 'C', 'D'});
    auto vertices1 = a->getVertices();
    auto edges1 = a->getEdges();
    decltype(vertices1) vertices2 = {'A', 'B', 'C', 'D'};
    decltype(edges1) edges2 = {{'B', 'A'}, {'C', 'A'}, {'D', 'A'},
                               {'C', 'B'}, {'D', 'B'}, {'D', 'C'}};
    EXPECT_EQ(vertices1, vertices2);
    EXPECT_EQ(edges1, edges2);
}

TEST_F(GraphTests, Bipartite) {
    a = factory.create("bipartite", {'A', 'B', 'C'}, {'D', 'E', 'F', 'G'});
    auto vertices1 = a->getVertices();
    auto edges1 = a->getEdges();
    decltype(vertices1) vertices2 = {'A', 'B', 'C', 'D', 'E', 'F', 'G'};
    decltype(edges1) edges2 = {{'D', 'A'}, {'E', 'A'}, {'F', 'A'}, {'G', 'A'},
                               {'D', 'B'}, {'E', 'B'}, {'F', 'B'}, {'G', 'B'},
                               {'D', 'C'}, {'E', 'C'}, {'F', 'C'}, {'G', 'C'}};
    EXPECT_EQ(vertices1, vertices2);
    EXPECT_EQ(edges1, edges2);
}

TEST_F(GraphTests, Weighted) {
    a = factory.create("weighted", {'A', 'C', 'D', 'E', 'M', 'Z'},
                      {{'A', 'C', 1.0}, {'A', 'E', 1.0}, {'A', 'D', 2.0},
                       {'A', 'Z', 5.0}, {'C', 'M', 2.0}, {'M', 'Z', 1.0},
                       {'D', 'Z', 2.0}, {'E', 'Z', 3.0}, {'E', 'M', 1.0}});
    auto vertices1 = a->getVertices();
    auto edges1 = a->getEdges();
    decltype(vertices1) vertices2 = {'A', 'C', 'D', 'E', 'M', 'Z'};
    decltype(edges1) edges2 = {{'C', 'A'}, {'E', 'A'}, {'D', 'A'},
                               {'Z', 'A'}, {'M', 'C'}, {'Z', 'M'},
                               {'Z', 'D'}, {'Z', 'E'}, {'M', 'E'}};
    EXPECT_EQ(vertices1, vertices2);
    EXPECT_EQ(edges1, edges2);

    // test the weights are correct
    ostringstream  stream1;
    stream1 << "===Weighted===" << endl
            << "Vertices: A C D E M Z" << endl
            << "Edges: CA-1 DA-2 EA-1 MC-2 ME-1 ZA-5 ZD-2 ZE-3 ZM-1" << endl
            << "==============";
    string actual = a->toString();
    string expected = stream1.str();
    EXPECT_EQ(actual, expected);

    // test asWeighted(double)
    b = factory.create("simple", {'A', 'B', 'C', 'D'},
                     {{'A', 'B'}, {'B', 'C'}, {'B', 'D'}});
    ostringstream  stream2;
    stream2 << "===Weighted===" << endl
            << "Vertices: A B C D" << endl
            << "Edges: BA-7 CB-7 DB-7" << endl
            << "==============";
    string actual2 = b->asWeighted(7.0)->toString();
    string expected2 = stream2.str();
    EXPECT_EQ(actual2, expected2);
}

TEST_F(GraphTests, Exceptions) {
    EXPECT_ANY_THROW(factory.create("simple", {'A', 'B', 'C', 'D'},{{'A', 'E'}, {'A', 'B'}}));
    EXPECT_ANY_THROW(factory.create("simple", {'A', 'B', 'C', 'D'},{{'A', 'C', 1.0}, {'A', 'B', 1.2}}));
    set<char> lower = {'E', 'F'};
    EXPECT_ANY_THROW(factory.create("simple", {'A', 'B', 'C', 'D'},lower));

}