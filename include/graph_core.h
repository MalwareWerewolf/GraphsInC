#ifndef GRAPH_CORE_H
#define GRAPH_CORE_H

#include "graph_types.h"

/**
 * @brief Creates a new directed graph.
 * 
 * Allocates memory for a new graph and initializes it with a starting set of edges.
 * 
 * @param edges Array of Edge structs containing the initial source and destination pairs.
 *              Can be NULL if num_edges is 0.
 * @param num_edges The number of edges in the edges array.
 * @param initial_vertices The starting number of vertices to allocate space for.
 * @return Graph* Pointer to the newly created graph, or NULL if memory allocation fails.
 */
Graph* create_graph(Edge edges[], int num_edges, int initial_vertices);

/**
 * @brief Adds a new, disconnected vertex to the graph.
 * 
 * Dynamically expands the graph's memory if capacity is reached. 
 * The new vertex will initially have no incoming or outgoing edges.
 * 
 * @param g Pointer to the graph.
 * @return int The ID of the newly added vertex, or -1 if the operation fails.
 */
int graph_add_vertex(Graph *g);

/**
 * @brief Removes a vertex and all its associated edges from the graph.
 * 
 * Deletes all outgoing and incoming edges for the specified vertex. 
 * Vertices with IDs greater than the removed vertex will shift down by 1 
 * (e.g., if vertex 2 is removed, vertex 3 becomes the new vertex 2).
 * 
 * @param g Pointer to the graph.
 * @param v The ID of the vertex to remove.
 * @return int 0 on success, or -1 if the graph is NULL or the vertex ID is invalid.
 */
int graph_remove_vertex(Graph *g, int v);

/**
 * @brief Adds a directed edge from one vertex to another.
 * 
 * Creates a new connection in the adjacency list of the source vertex 
 * pointing to the destination vertex.
 * 
 * @param g Pointer to the graph.
 * @param source The ID of the vertex where the edge originates.
 * @param dest The ID of the vertex where the edge points.
 * @return int 0 on success, or -1 if the graph is NULL or either vertex ID is invalid.
 */
int graph_add_edge(Graph *g, int source, int dest);

/**
 * @brief Removes a directed edge between two vertices.
 * 
 * Deletes the connection originating at the source vertex and pointing 
 * to the destination vertex. The vertices themselves remain intact.
 * 
 * @param g Pointer to the graph.
 * @param source The ID of the vertex where the edge originates.
 * @param dest The ID of the vertex where the edge points.
 * @return int 0 on success, or -1 if the graph is NULL, a vertex ID is invalid, 
 *         or the edge does not exist.
 */
int graph_remove_edge(Graph *g, int source, int dest);

/**
 * @brief Prints a visual representation of the graph to standard output.
 * 
 * Iterates through all vertices and prints their adjacency lists in the 
 * format: "Vertex X: -> Y -> Z"
 * 
 * @param g Pointer to the graph.
 */
void print_graph(Graph *g);

/**
 * @brief Frees all memory associated with the graph.
 * 
 * Safely deallocates all linked list nodes (edges), the dynamic adjacency 
 * lists array, and the graph structure itself.
 * 
 * @param g Pointer to the graph.
 */
void free_graph(Graph *g);

#endif
