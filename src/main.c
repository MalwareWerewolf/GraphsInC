#include <stdio.h>
#include <stdlib.h>
#include "../include/graph_core.h"

int main(void) {
    // 1. Create an initial graph with 3 vertices (0, 1, 2)
    Edge edges[] = { {0, 1}, {0, 2}, {1, 2} };
    int n = sizeof(edges) / sizeof(edges[0]);

    Graph *graph = create_graph(edges, n, 3);
    if (!graph) {
        fprintf(stderr, "Failed to create graph\n");
        return 1;
    }

    printf("=== Initial Graph (3 Vertices) ===\n");
    print_graph(graph);

    // 2. Test dynamically adding a new vertex
    printf("\n=== Adding Vertex 3 ===\n");
    int new_v = graph_add_vertex(graph);
    printf("Successfully added vertex with ID: %d\n", new_v);
    
    // 3. Test dynamically adding edges
    printf("\n=== Adding Edges: 2->3 and 3->0 ===\n");
    graph_add_edge(graph, 2, 3);
    graph_add_edge(graph, 3, 0);
    print_graph(graph);

    // 4. Test removing a vertex from the middle
    printf("\n=== Removing Vertex 1 ===\n");
    printf("(Notice how Vertex 2 and 3 shift down to become 1 and 2!)\n");
    graph_remove_vertex(graph, 1);
    print_graph(graph);

    // 5. Clean up
    free_graph(graph);
    return 0;
}
