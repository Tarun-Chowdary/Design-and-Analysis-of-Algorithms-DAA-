#include <stdio.h>
#include <limits.h>

#define V 10


void dijkstra(int graph[V][V], int src) {
    int dist[V], visited[V] = {0};

    for (int i = 0; i < V; i++)
        dist[i] = INT_MAX;

    dist[src] = 0;

    for (int count = 0; count < V - 1; count++) {

    
        int u = -1, min = INT_MAX;
        for (int i = 0; i < V; i++) {
            if (!visited[i] && dist[i] < min) {
                min = dist[i];
                u = i;
            }
        }

        visited[u] = 1;

        for (int v = 0; v < V; v++) {
            if (graph[u][v] != INT_MAX && !visited[v]) {
                if (dist[u] + graph[u][v] < dist[v]) {
                    dist[v] = dist[u] + graph[u][v];
                }
            }
        }
    }

    printf("\n--- Dijkstra Result (WRONG due to negative edges) ---\n");
    for (int i = 0; i < V; i++)
        printf("Distance from %d to %d = %d\n", src, i, dist[i]);
}


int main() {
    int graph[V][V];


    for (int i = 0; i < V; i++)
        for (int j = 0; j < V; j++)
            graph[i][j] = INT_MAX;

    
    graph[0][1] = 4;
    graph[0][2] = 1;

    
    graph[2][3] = 2;
    graph[3][1] = -4;   

    
    graph[1][2] = 1;    
                        

    int src = 0;

    dijkstra(graph, src);

    printf("\n⚠ Observation:\n");
    printf("Dijkstra gives incorrect results because of negative edges.\n");
    printf("With negative cycle, shortest path is undefined (distance → -∞).\n");

    return 0;
}