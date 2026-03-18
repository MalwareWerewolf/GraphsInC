#ifndef GRAPH_TYPES_H
#define GRAPH_TYPES_H

/**
 * @brief Represents a directed edge between two vertices.
 * 
 * Used primarily as a convenient way to pass an initial batch of 
 * connections into the create_graph() function.
 */
typedef struct Edge {
    int source;      /**< The ID of the starting vertex. */
    int destination; /**< The ID of the vertex the edge points to. */
} Edge;

/**
 * @brief A single node in an adjacency list.
 * 
 * Represents one outgoing edge from a specific vertex. These nodes 
 * form a linked list containing all destinations reachable from a source.
 */
typedef struct AdjNode {
    int destination;       /**< The ID of the target vertex. */
    struct AdjNode *next;  /**< Pointer to the next outgoing edge in the list. */
} AdjNode;

/**
 * @brief The main Graph data structure.
 * 
 * Implements a directed graph using an adjacency list representation. 
 * Memory is managed dynamically, allowing vertices and edges to be 
 * added or removed at runtime.
 */
typedef struct Graph {
    int capacity;        /**< Total number of vertex slots currently allocated in memory. */
    int vertex_count;    /**< The actual number of active vertices (IDs 0 to vertex_count - 1). */
    int num_edges;       /**< Total number of directed edges currently in the graph. */
    AdjNode **adj_lists; /**< Dynamic array of pointers, where index 'i' holds the linked list of edges for vertex 'i'. */
} Graph;

#endif
