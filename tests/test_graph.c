#include "../include/graph_core.h"
#include "unity.h"

void setUp(void) {}
void tearDown(void) {}

void test_create_graph_not_null(void) {
  Edge edges[] = {{0, 1}, {1, 2}};
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

void test_graph_add_edge(void) {
  Graph *g = create_graph(NULL, 0, 0);

  graph_add_vertex(g);
  graph_add_vertex(g);
  graph_add_vertex(g);

  int result1 = graph_add_edge(g, 0, 1);
  TEST_ASSERT_EQUAL_INT(0, result1); // 0 means success

  int result2 = graph_add_edge(g, 0, 5);
  TEST_ASSERT_EQUAL_INT(-1, result2);

  TEST_ASSERT_NOT_NULL(g->adj_lists[0]);
  TEST_ASSERT_EQUAL_INT(1, g->adj_lists[0]->destination);

  free_graph(g);
}

void test_graph_remove_vertex(void) {
  Edge edges[] = {{0, 1}, {1, 2}, {0, 2}};
  Graph *g = create_graph(edges, 3, 3);

  int result = graph_remove_vertex(g, 1);
  TEST_ASSERT_EQUAL_INT(0, result);
  TEST_ASSERT_EQUAL_INT(2, g->vertex_count);

  TEST_ASSERT_NOT_NULL(g->adj_lists[0]);
  TEST_ASSERT_EQUAL_INT(1, g->adj_lists[0]->destination);

  free_graph(g);
}

void test_graph_remove_edge(void) {
  Edge edges[] = {{0, 1}, {0, 2}};
  Graph *g = create_graph(edges, 2, 3);

  TEST_ASSERT_EQUAL_INT(2, g->num_edges);

  int result = graph_remove_edge(g, 0, 1);
  TEST_ASSERT_EQUAL_INT(0, result);
  TEST_ASSERT_EQUAL_INT(1, g->num_edges);

  TEST_ASSERT_NOT_NULL(g->adj_lists[0]);
  TEST_ASSERT_EQUAL_INT(2, g->adj_lists[0]->destination);

  int fail_result = graph_remove_edge(g, 0, 5);
  TEST_ASSERT_EQUAL_INT(-1, fail_result);

  free_graph(g);
}

int main(void) {
  UNITY_BEGIN();
  RUN_TEST(test_create_graph_not_null);
  RUN_TEST(test_graph_add_vertex);

  RUN_TEST(test_graph_add_edge);
  RUN_TEST(test_graph_remove_vertex);
  RUN_TEST(test_graph_remove_edge);

  return UNITY_END();
}
