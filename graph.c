/* **************************************** */
/* Aluno: Emanuel Gefferson Maciel Sampaio  */
/* CES-11: Algoritmos para grafos           */
/* Turma T3                                 */
/* **************************************** */

#include "graph.h"

#include <assert.h>
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct edge EDGE;

struct edge {
    int index;
    EDGE *next;
};

struct graph {
  int order;
  EDGE **vertex;
};


GRAPH *graph_read() {
    int ordem, vertice_1, vertice_2;
    scanf("%d", &ordem);
    GRAPH *grafo = graph_create(ordem);
    while ((scanf("%d %d", &vertice_1, &vertice_2)) != EOF){
        graph_add_edge(grafo, vertice_1, vertice_2);
        graph_add_edge(grafo, vertice_2, vertice_1);
    }

    return grafo;
}

GRAPH *graph_create(int order) {
    GRAPH *grafo = (GRAPH*)malloc(sizeof(GRAPH));
    grafo->order = order;
    grafo->vertex = (EDGE**)malloc(order*sizeof(EDGE*));

    for(int i=0; i<order; i++){
        grafo->vertex[i] = NULL;
    }

    return grafo;
}

void graph_destroy(GRAPH *graph) {
    if(graph != NULL){
        EDGE *temp;
        for(int i=0; i<graph->order; i++){
            for(EDGE *p = graph->vertex[i]; p != NULL; p = temp){
                temp = p->next;
                free(p);
            }
        }
        free(graph->vertex);
        free(graph);
    }
}

static EDGE *graph_create_edge(int v) {
    EDGE *aresta = (EDGE*)malloc(sizeof(EDGE));
    aresta->index = v;
    aresta->next = NULL;
    return aresta;
}

void graph_add_edge(GRAPH *graph, int u, int v) {
    EDGE *aresta = graph_create_edge(v);
    if(graph->vertex[u] != NULL){
        for(EDGE *p = graph->vertex[u]; p != NULL; p = p->next){
            if(p->next != NULL){
                if(v>p->index && v<p->next->index){
                    aresta->next = p->next;
                    p->next = aresta;
                }
            }
            else{
                p->next = aresta;
                break;
            }
        }
    }
    else{
         graph->vertex[u] = aresta;
    }
}

bool graph_has_edge(const GRAPH *graph, int u, int v) {
    for(EDGE *p = graph->vertex[u]; p != NULL; p = p->next){
        if(p->index == v){
            return true;
        }
    }

    return false;
}

typedef enum { PINK, BLUE, GREY } COLOR;

void Proc_Pontos(const GRAPH *graph,  int u, int *tempo_tot, COLOR *color, int *previous, int *tempo_d, int *anc_distante){

    if(color[u] == GREY){
        return;
    }

    color[u] = PINK;
    *tempo_tot = *tempo_tot + 1;
    tempo_d[u] = *tempo_tot;
    anc_distante[u] = *tempo_tot;

    for(int v=0; v<graph->order; v++){
        if(graph_has_edge(graph, u, v) && previous[u] != v){
            if(color[v] == BLUE){
                previous[v] = u;
                Proc_Pontos(graph, v, tempo_tot, color, previous, tempo_d, anc_distante);
            }
            if(anc_distante[u]>tempo_d[v] && color[v] == PINK){
                anc_distante[u]=tempo_d[v];
            }
        }
    }
    if(anc_distante[u]<anc_distante[previous[u]]){
        anc_distante[previous[u]] = anc_distante[u];
    }

    color[u] = GREY;
    return;
}

void Pontos_Art(const GRAPH *graph, int u){

    COLOR *cor = (COLOR*)malloc(graph->order*sizeof(COLOR));
    int *previous = (int*)malloc(graph->order*sizeof(int));
    int *tempo_d = (int*)malloc(graph->order*sizeof(int));
    int *anc_distante = (int*)malloc(graph->order*sizeof(int));

    for(int i=0; i<graph->order; i++){
        cor[i] = BLUE;
        previous[i] = -1;
        tempo_d[i] = INT_MAX;
        anc_distante[i] = INT_MAX;
    }
    tempo_d[u] = 0;
    anc_distante[u] = u;

    int tempo_tot = -1;

    for(int i=0; i<graph->order; ++i){
        Proc_Pontos(graph, i, &tempo_tot, cor, previous, tempo_d, anc_distante);
    }

    for(int i = 0; i<graph->order; i++){
        if(previous[i] == -1){
            int contador = 0;
            for(int j = 0; j<graph->order; j++){
                if(previous[j] == i){
                    contador++;
                    if(contador>1){
                        printf("%d\n", i);
                        break;
                    }
                }
            }
        }
        else{
            for(int j = 0; j<graph->order; j++){
                if(anc_distante[j]>=tempo_d[i] && previous[j] == i){
                    printf("%d\n", i);
                    break;
                }
            }
        }
    }

    free(cor);
    free(previous);
    free(tempo_d);
    free(anc_distante);
}
