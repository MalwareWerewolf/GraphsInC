#include "unity.h"
#include "../include/graph_core.h"

void setUp(void) {}
void tearDown(void) {}

void test_create_graph_not_null(void) {
    Edge edges[] = { {0,1}, {1,2} };
    int n = sizeof(edges) / sizeof(edges[0]);
    Graph *g = create_graph(edges, n, 3);
    TEST_ASSERT_NOT_NULL(g);
    free_graph(g);
}

void test_graph_add_vertex(void) {
    Graph *g = create_graph(NULL, 0, 0);
    TEST_ASSERT_NOT_NULL(g);

    int v0 = graph_add_vertex(g);
    TEST_ASSERT_EQUAL_INT(0, v0);

    int v1 = graph_add_vertex(g);
    TEST_ASSERT_EQUAL_INT(1, v1);

    free_graph(g);
}

// NEW: Test adding edges dynamically
void test_graph_add_edge(void) {
    Graph *g = create_graph(NULL, 0, 0);
    
    // Add 3 vertices (IDs 0, 1, 2)
    graph_add_vertex(g);
    graph_add_vertex(g);
    graph_add_vertex(g);

    // Add an edge from 0 to 1
    int result1 = graph_add_edge(g, 0, 1);
    TEST_ASSERT_EQUAL_INT(0, result1); // 0 means success

    // Try to add an invalid edge (to a non-existent vertex 5)
    int result2 = graph_add_edge(g, 0, 5);
    TEST_ASSERT_EQUAL_INT(-1, result2); // -1 means failure

    // Verify the edge 0->1 actually exists in the graph
    TEST_ASSERT_NOT_NULL(g->adj_lists[0]);
    TEST_ASSERT_EQUAL_INT(1, g->adj_lists[0]->destination);

    free_graph(g);
}

// NEW: Test removing a vertex and shifting edges
void test_graph_remove_vertex(void) {
    // Create a graph with edges: 0->1, 1->2, 0->2
    Edge edges[] = { {0,1}, {1,2}, {0,2} };
    Graph *g = create_graph(edges, 3, 3);

    // Remove vertex 1
    int result = graph_remove_vertex(g, 1);
    TEST_ASSERT_EQUAL_INT(0, result);

    // After removing vertex 1:
    // - Total vertices should drop from 3 to 2
    TEST_ASSERT_EQUAL_INT(2, g->vertex_count);

    // - The old vertex 2 should have shifted down to become vertex 1
    // - The old edge 0->2 should now point to 0->1
    TEST_ASSERT_NOT_NULL(g->adj_lists[0]);
    TEST_ASSERT_EQUAL_INT(1, g->adj_lists[0]->destination); // Edge shifted correctly

    free_graph(g);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_create_graph_not_null);    
    RUN_TEST(test_graph_add_vertex);
    
    // Register the new tests
    RUN_TEST(test_graph_add_edge);
    RUN_TEST(test_graph_remove_vertex);
    
    return UNITY_END();
}
