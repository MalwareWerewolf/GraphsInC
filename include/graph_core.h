#ifndef GRAPH_CORE_H
#define GRAPH_CORE_H

#include "graph_types.h"

Graph* create_graph(Edge edges[], int num_edges, int initial_vertices);
int graph_add_vertex(Graph *g);
int graph_remove_vertex(Graph *g, int v);
int graph_add_edge(Graph *g, int source, int dest);
void print_graph(Graph *g);
void free_graph(Graph *g);

#endif
