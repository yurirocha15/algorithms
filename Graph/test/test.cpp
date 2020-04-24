#include "graph.hpp"
#include "gtest/gtest.h"

class GraphTester : public ::testing::Test
{
protected:
    no_stl::Graph graph;
public:
    GraphTester() {};
    ~GraphTester() {};
};

TEST_F(GraphTester, testEmpty) {
    ASSERT_EXIT((graph.BFS(1), exit(0)), ::testing::ExitedWithCode(0), ".*");
    ASSERT_EXIT((graph.DFS(1), exit(0)), ::testing::ExitedWithCode(0), ".*");
    ASSERT_EXIT((graph.Dijkstra(1), exit(0)), ::testing::ExitedWithCode(0), ".*");
}
