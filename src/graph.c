#include "../include/graph_core.h"
#include <stdio.h>
#include <stdlib.h>

Graph *create_graph(Edge edges[], int num_edges, int initial_vertices) {
  Graph *g = malloc(sizeof(Graph));
  if (!g)
    return NULL;

  g->vertex_count = initial_vertices;
  g->capacity = initial_vertices > 0 ? initial_vertices : 4; // Safely handle 0
  g->adj_lists = calloc(g->capacity, sizeof(AdjNode *));
  g->num_edges = 0;

  for (int i = 0; i < num_edges; i++) {
    int source = edges[i].source;
    int dest = edges[i].destination;

    if (source >= g->vertex_count || dest >= g->vertex_count)
      continue;

    AdjNode *new_node = malloc(sizeof(AdjNode));
    new_node->destination = dest;
    new_node->next = g->adj_lists[source];
    g->adj_lists[source] = new_node;
    g->num_edges++;
  }

  return g;
}

int graph_add_vertex(Graph *g) {
  if (!g)
    return -1;

  if (g->vertex_count >= g->capacity) {
    int new_capacity = g->capacity == 0 ? 4 : g->capacity * 2;
    AdjNode **new_lists =
        realloc(g->adj_lists, new_capacity * sizeof(AdjNode *));
    if (!new_lists)
      return -1;

    g->adj_lists = new_lists;
    g->capacity = new_capacity;

    for (int i = g->vertex_count; i < g->capacity; i++) {
      g->adj_lists[i] = NULL;
    }
  }

  int new_id = g->vertex_count;
  g->adj_lists[new_id] = NULL;
  g->vertex_count++;

  return new_id;
}

int graph_remove_vertex(Graph *g, int v) {
  if (!g || v < 0 || v >= g->vertex_count)
    return -1;

  AdjNode *curr = g->adj_lists[v];
  while (curr != NULL) {
    AdjNode *temp = curr;
    curr = curr->next;
    free(temp);
    g->num_edges--;
  }
  g->adj_lists[v] = NULL;

  for (int i = 0; i < g->vertex_count; i++) {
    if (i == v)
      continue;

    AdjNode *prev = NULL;
    curr = g->adj_lists[i];

    while (curr != NULL) {
      if (curr->destination == v) {
        AdjNode *temp = curr;
        if (prev != NULL) {
          prev->next = curr->next;
        } else {
          g->adj_lists[i] = curr->next;
        }
        curr = curr->next;
        free(temp);
        g->num_edges--;
      } else {
        if (curr->destination > v) {
          curr->destination -= 1;
        }
        prev = curr;
        curr = curr->next;
      }
    }
  }

  for (int i = v; i < g->vertex_count - 1; i++) {
    g->adj_lists[i] = g->adj_lists[i + 1];
  }

  g->adj_lists[g->vertex_count - 1] = NULL;
  g->vertex_count--;

  return 0;
}

int graph_add_edge(Graph *g, int source, int dest) {
  if (!g || source < 0 || dest < 0 || source >= g->vertex_count ||
      dest >= g->vertex_count) {
    return -1;
  }

  AdjNode *new_node = malloc(sizeof(AdjNode));
  if (!new_node)
    return -1;

  new_node->destination = dest;
  new_node->next = g->adj_lists[source];
  g->adj_lists[source] = new_node;
  g->num_edges++;

  return 0;
}

int graph_remove_edge(Graph *g, int source, int dest) {
  if (!g || source < 0 || dest < 0 || source >= g->vertex_count ||
      dest >= g->vertex_count) {
    return -1;
  }

  AdjNode *curr = g->adj_lists[source];
  AdjNode *prev = NULL;

  while (curr != NULL) {
    if (curr->destination == dest) {
      if (prev != NULL) {
        prev->next = curr->next;
      } else {
        g->adj_lists[source] = curr->next;
      }

      free(curr);
      g->num_edges--;
      return 0;
    }

    prev = curr;
    curr = curr->next;
  }

  return -1;
}

void print_graph(Graph *g) {
  if (!g)
    return;
  for (int i = 0; i < g->vertex_count; i++) {
    AdjNode *ptr = g->adj_lists[i];
    printf("Vertex %d:", i);
    while (ptr != NULL) {
      printf(" -> %d", ptr->destination);
      ptr = ptr->next;
    }
    printf("\n");
  }
}

void free_graph(Graph *g) {
  if (!g)
    return;
  for (int i = 0; i < g->vertex_count; i++) {
    AdjNode *ptr = g->adj_lists[i];
    while (ptr != NULL) {
      AdjNode *temp = ptr;
      ptr = ptr->next;
      free(temp);
    }
  }

  free(g->adj_lists);
  free(g);
}
