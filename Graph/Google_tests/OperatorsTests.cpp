#include "gtest/gtest.h"
#include "../Graphs/GraphFactory.h"
#include "../Arithmetic/NewOperators.h"
#include "stdexcept"
#include <iostream>

class OperatorsTests : public ::testing::Test {
public:
    GraphFactory factory;
    std::shared_ptr<TGraph> a, b, c, d, e, f, g, h;
protected:
    void SetUp() override {
        a = factory.create("simple", {'A','B', 'C', 'D'},
                           {{'A', 'C'}, {'B', 'C'}, {'B', 'D'}});
        b = factory.create("simple", {'A', 'C', 'E', 'F'},
                           {{'A', 'C'}, {'E', 'F'}});

        c = factory.create("weighted", {'A', 'B', 'C', 'D'},
                           {{'A', 'C', 1.0}, {'B', 'C', 1.2}, {'B', 'D', 2.1}});
        d = factory.create("weighted", {'A', 'C', 'E', 'F'},
                           {{'A', 'C', 3.2}, {'E', 'F', 1.4}});

        e = factory.create("complete", {'A', 'B', 'C', 'D'});
        f = factory.create("complete", {'A', 'E', 'F'});

        g = factory.create("bipartite", {'A', 'B'}, set<char>{'C', 'D'});
        h = factory.create("bipartite", {'A', 'E'}, {'F'});
    }
};

TEST_F(OperatorsTests, SumSameArguments) {
    auto sum1 = a + b;
    set<char> expVert1 = {'A', 'B', 'C', 'D', 'E', 'F'};
    set<pair<char, char>> expEdge1 = {{'C', 'B'}, {'C', 'A'}, {'D', 'B'}, {'F', 'E'}};
    EXPECT_EQ(sum1->getVertices(), expVert1);
    EXPECT_EQ(sum1->getEdges(), expEdge1);

    auto sum2 = c + d;
    set<char> expVert2 = {'A', 'B', 'C', 'D', 'E', 'F'};
    set<pair<char, char>> expEdge2 = {{'C', 'B'}, {'C', 'A'}, {'D', 'B'}, {'F', 'E'}};
    EXPECT_EQ(sum2->getVertices(), expVert2);
    EXPECT_EQ(sum2->getEdges(), expEdge2);
    ostringstream  stream;
    stream << "===Weighted===" << endl
            << "Vertices: A B C D E F" << endl
            << "Edges: CA-1 CB-1.2 DB-2.1 FE-1.4" << endl
            << "==============";
    string actual2 = sum2->toString();
    string expected2 = stream.str();
    EXPECT_EQ(actual2, expected2);

    auto sum3 = e + f;
    set<char> expVert3 = {'A', 'B', 'C', 'D', 'E', 'F'};
    set<pair<char, char>> expEdge3 = {{'B', 'A'}, {'C', 'A'}, {'D', 'A'}, {'E', 'A'}, {'F', 'A'},
                                      {'C', 'B'}, {'D', 'B'}, {'E', 'B'}, {'F', 'B'},
                                      {'D', 'C'}, {'E', 'C'}, {'F', 'C'},
                                      {'E', 'D'}, {'F', 'D'},
                                      {'F', 'E'}};
    EXPECT_EQ(sum3->getVertices(), expVert3);
    EXPECT_EQ(sum3->getEdges(), expEdge3);

    auto sum4 = g + h;
    set<char> expVert4 = {'A', 'B', 'C', 'D', 'E', 'F'};
    set<pair<char, char>> expEdge4 = {{'C', 'A'}, {'D', 'A'}, {'F', 'A'},
                                      {'C', 'B'}, {'D', 'B'}, {'F', 'B'},
                                      {'E', 'C'}, {'E', 'D'}, {'F', 'E'}};
    EXPECT_EQ(sum4->getVertices(), expVert4);
    EXPECT_EQ(sum4->getEdges(), expEdge4);
}

TEST_F(OperatorsTests, SumDifferentArguments) {
    auto sum1 = f + g;
    set<char> expVert1 = {'A', 'B', 'C', 'D', 'E', 'F'};
    set<pair<char, char>> expEdge1 = {{'C', 'A'}, {'E', 'A'}, {'F', 'A'},
                                      {'C', 'A'}, {'C', 'A'},
                                      {'F', 'E'},
                                      {'C', 'B'},{'D', 'A'}, {'D', 'B'}};
    EXPECT_EQ(sum1->getVertices(), expVert1);
    EXPECT_EQ(sum1->getEdges(), expEdge1);

    EXPECT_ANY_THROW(a + c);
    EXPECT_ANY_THROW(d + f);
}

TEST_F(OperatorsTests, DiffSameArguments) {
    auto sum1 = a - b;
    set<char> expVert1 = {'B', 'D'};
    set<pair<char, char>> expEdge1 = {{'D', 'B'}};
    EXPECT_EQ(sum1->getVertices(), expVert1);
    EXPECT_EQ(sum1->getEdges(), expEdge1);

    auto sum2 = d - c;
    set<char> expVert2 = {'E', 'F'};
    set<pair<char, char>> expEdge2 = {{'F', 'E'}};
    EXPECT_EQ(sum2->getVertices(), expVert2);
    EXPECT_EQ(sum2->getEdges(), expEdge2);
    ostringstream  stream;
    stream << "===Weighted===" << endl
           << "Vertices: E F" << endl
           << "Edges: FE-1.4" << endl
           << "==============";
    string actual2 = sum2->toString();
    string expected2 = stream.str();
    EXPECT_EQ(actual2, expected2);

    auto sum3 = e - f;
    set<char> expVert3 = {'B', 'C', 'D'};
    set<pair<char, char>> expEdge3 = {{'D', 'B'}, {'C', 'B'},{'D', 'C'}};
    EXPECT_EQ(sum3->getVertices(), expVert3);
    EXPECT_EQ(sum3->getEdges(), expEdge3);

    auto sum4 = g - h;
    set<char> expVert4 = {'B', 'C', 'D'};
    set<pair<char, char>> expEdge4 = {{'C', 'B'}, {'D', 'B'}};
    EXPECT_EQ(sum4->getVertices(), expVert4);
    EXPECT_EQ(sum4->getEdges(), expEdge4);
}

TEST_F(OperatorsTests, DifDifferentArguments) {
    auto sum1 = c - b;
    set<char> expVert1 = {'B', 'D'};
    set<pair<char, char>> expEdge1 = {{'D', 'B'}};
    EXPECT_EQ(sum1->getVertices(), expVert1);
    EXPECT_EQ(sum1->getEdges(), expEdge1);
    ostringstream  stream1;
    stream1 << "===Weighted===" << endl
           << "Vertices: B D" << endl
           << "Edges: DB-2.1" << endl
           << "==============";
    string actual1 = sum1->toString();
    string expected1 = stream1.str();
    EXPECT_EQ(actual1, expected1);

    auto sum2 = b - c;
    set<char> expVert2 = {'E', 'F'};
    set<pair<char, char>> expEdge2 = {{'F', 'E'}};
    EXPECT_EQ(sum2->getVertices(), expVert2);
    EXPECT_EQ(sum2->getEdges(), expEdge2);
    ostringstream  stream2;
    stream2 << "===Simple===" << endl
           << "Vertices: E F" << endl
           << "Edges: FE" << endl
           << "============";
    string actual2 = sum2->toString();
    string expected2 = stream2.str();
    EXPECT_EQ(actual2, expected2);

    auto sum3 = f - g;
    set<char> expVert3 = {'E', 'F'};
    set<pair<char, char>> expEdge3 = {{'F', 'E'}};
    EXPECT_EQ(sum3->getVertices(), expVert3);
    EXPECT_EQ(sum3->getEdges(), expEdge3);
}
