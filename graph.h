#ifndef GRAPH_H
#define GRAPH_H

#include <stdbool.h>

typedef struct graph GRAPH;

GRAPH *graph_read();

GRAPH *graph_create(int order);
void graph_destroy(GRAPH *graph);
void graph_add_edge(GRAPH *graph, int u, int v);

bool graph_has_edge(const GRAPH *graph, int u, int v);
void graph_print(const GRAPH *graph);

void Pontos_Art(const GRAPH *graph, int u);

#endif // GRAPH_H
