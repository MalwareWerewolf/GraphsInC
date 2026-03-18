#ifndef GRAPH_TYPES_H
#define GRAPH_TYPES_H

typedef struct Edge {
    int source;
    int destination;
} Edge;

// Represents a single outgoing connection in the adjacency list
typedef struct AdjNode {
    int destination;
    struct AdjNode *next;
} AdjNode;

// The Graph structure
typedef struct Graph {
    int capacity;
    int vertex_count;
    int num_edges;
    AdjNode **adj_lists;
} Graph;

#endif
