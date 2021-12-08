#include "gtest/gtest.h"
#include "../Graphs/GraphFactory.h"
#include "stdexcept"
#include <iostream>

class PathTests : public ::testing::Test {
public:
    GraphFactory factory;
    std::shared_ptr<TGraph> a, b;
};

TEST_F(PathTests, ShortestPathCorrect) {
    a = factory.create("weighted", {'A', 'C', 'D', 'E', 'M', 'Z'},
                       {{'A', 'C', 1.0}, {'A', 'E', 1.0}, {'A', 'D', 2.0},
                        {'A', 'Z', 5.0}, {'C', 'M', 2.0}, {'M', 'Z', 1.0},
                        {'D', 'Z', 2.0}, {'E', 'Z', 3.0}, {'E', 'M', 1.0}});
    vector<char> expectedPath = {'A', 'E', 'M', 'Z'};
    EXPECT_EQ(a->shortestPath('A', 'Z'), expectedPath);

    b = factory.create("weighted", {'A', 'C', 'D', 'E', 'M', 'Z'},
                       {{'A', 'C', 1.0}, {'A', 'E', 1.0}, {'A', 'D', 2.0},
                        {'A', 'Z', 5.0}, {'C', 'M', 2.0}, {'M', 'Z', 1.0},
                        {'D', 'Z', 2.0}, {'E', 'Z', 3.0}});
    vector<char> expectedPath2 = {'A', 'E', 'Z'};
    EXPECT_EQ(b->shortestPath('A', 'Z'), expectedPath2);
}

TEST_F(PathTests, NoPath) {
    a = factory.create("weighted", {'A', 'B', 'C', 'D', 'X', 'Z'},
                       {{'A', 'C', 1.0}, {'A', 'B', 1.0}, {'B', 'C', 2.0}, {'Z', 'X', 2.0}});
    vector<char> expectedPath1 = {};
    EXPECT_EQ(a->shortestPath('A', 'Z'), expectedPath1);
    vector<char> expectedPath2 = {'X', 'Z'};
    EXPECT_EQ(a->shortestPath('X', 'Z'), expectedPath2);
}

TEST_F(PathTests, NotWeighted) {
    a = factory.create("complete", {'A', 'B', 'C', 'D', 'X', 'Z'});
    EXPECT_ANY_THROW(a->shortestPath('A', 'Z'));
    vector<char> expectedPath = {'A', 'Z'};
    EXPECT_EQ(a->asWeighted(1.0)->shortestPath('A', 'Z'), expectedPath);
}
