#include <stdio.h>
#include <stdlib.h>
#include "../include/graph_core.h"

int main(void) {
  Edge edges[] = { {0, 1}, {0, 2}, {1, 2} };
  int n = sizeof(edges) / sizeof(edges[0]);

  Graph *graph = create_graph(edges, n, 3);
  if (!graph) {
    fprintf(stderr, "Failed to create graph\n");
    return 1;
  }

  printf("=== 1. Initial Graph (3 Vertices, %d Edges) ===\n", graph->num_edges);
  print_graph(graph);

  printf("\n=== 2. Adding Vertex 3 ===\n");
  int new_v = graph_add_vertex(graph);
  printf("Successfully added vertex with ID: %d\n", new_v);
  
  printf("\n=== 3. Adding Edges: 2->3 and 3->0 ===\n");
  graph_add_edge(graph, 2, 3);
  graph_add_edge(graph, 3, 0);
  print_graph(graph);

  printf("\n=== 4. Removing Edge 0->2 ===\n");
  printf("(Notice that Vertex 0 will only point to 1 now!)\n");
  if (graph_remove_edge(graph, 0, 2) == 0) {
    printf("Successfully removed edge 0->2. Total edges now: %d\n", graph->num_edges);
  } else {
    printf("Failed to remove edge.\n");
  }
  print_graph(graph);

  printf("\n=== 5. Removing Vertex 1 ===\n");
  printf("(Notice: Vertex 2 becomes 1, Vertex 3 becomes 2. Edges shift automatically!)\n");
  graph_remove_vertex(graph, 1);
  print_graph(graph);

  printf("\n=== Cleaning up memory... ===\n");
  free_graph(graph);
  printf("Done!\n");
  
  return 0;
}
