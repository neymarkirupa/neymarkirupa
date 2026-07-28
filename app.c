#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_NODES 20
#define INF 9999

typedef struct {
    int n; // Number of vertices
    int adj[MAX_NODES][MAX_NODES];
    char names[MAX_NODES][50];
} Graph;

void initGraph(Graph *g, int n) {
    g->n = n;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            g->adj[i][j] = (i == j) ? 0 : INF;
        }
        sprintf(g->names[i], "Location %d", i + 1);
    }
}

void addEdge(Graph *g, int u, int v, int weight) {
    if (u >= 0 && u < g->n && v >= 0 && v < g->n) {
        g->adj[u][v] = weight;
        g->adj[v][u] = weight; // Assuming undirected graph for city locations
    }
}

void printPath(int parent[], int j) {
    if (parent[j] == -1)
        return;
    printPath(parent, parent[j]);
    printf(" -> %d", j);
}

void dijkstra(Graph *g, int startNode, int endNode) {
    int dist[MAX_NODES];
    bool visited[MAX_NODES];
    int parent[MAX_NODES];

    for (int i = 0; i < g->n; i++) {
        dist[i] = INF;
        visited[i] = false;
        parent[i] = -1;
    }

    dist[startNode] = 0;

    for (int count = 0; count < g->n - 1; count++) {
        int u = -1;
        int min = INF;

        // Find min distance node not yet visited
        for (int i = 0; i < g->n; i++) {
            if (!visited[i] && dist[i] < min) {
                min = dist[i];
                u = i;
            }
        }

        if (u == -1) break;

        visited[u] = true;

        for (int v = 0; v < g->n; v++) {
            if (!visited[v] && g->adj[u][v] != INF && dist[u] != INF 
                && dist[u] + g->adj[u][v] < dist[v]) {
                dist[v] = dist[u] + g->adj[u][v];
                parent[v] = u;
            }
        }
    }

    if (dist[endNode] == INF) {
        printf("\nNo path exists from node %d to node %d.\n", startNode, endNode);
    } else {
        printf("\nShortest Distance from %d to %d: %d\n", startNode, endNode, dist[endNode]);
        printf("Path: %d", startNode);
        printPath(parent, endNode);
        printf("\n");
    }
}

int main() {
    Graph g;
    int numNodes, choice;

    printf("=== Shortest Path Finder (Dijkstra's Algorithm) ===\n");
    printf("Enter number of nodes in the city (max %d): ", MAX_NODES);
    scanf("%d", &numNodes);

    if (numNodes > MAX_NODES || numNodes <= 0) {
        printf("Invalid number of nodes. Exiting.\n");
        return 1;
    }

    initGraph(&g, numNodes);

    while (1) {
        printf("\n--- Menu ---\n");
        printf("1. Add Road (Edge)\n");
        printf("2. Find Shortest Path\n");
        printf("3. Display Adjacency Matrix\n");
        printf("4. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: {
                int u, v, w;
                printf("Enter source node (0-%d): ", numNodes - 1);
                scanf("%d", &u);
                printf("Enter destination node (0-%d): ", numNodes - 1);
                scanf("%d", &v);
                printf("Enter distance/weight: ");
                scanf("%d", &w);
                addEdge(&g, u, v, w);
                printf("Road added successfully!\n");
                break;
            }
            case 2: {
                int start, end;
                printf("Enter starting location node (0-%d): ", numNodes - 1);
                scanf("%d", &start);
                printf("Enter destination location node (0-%d): ", numNodes - 1);
                scanf("%d", &end);
                dijkstra(&g, start, end);
                break;
            }
            case 3:
                printf("\nAdjacency Matrix (INF = %d):\n", INF);
                for (int i = 0; i < g.n; i++) {
                    for (int j = 0; j < g.n; j++) {
                        if (g.adj[i][j] == INF) printf("INF\t");
                        else printf("%d\t", g.adj[i][j]);
                    }
                    printf("\n");
                }
                break;
            case 4:
                exit(0);
            default:
                printf("Invalid choice!\n");
        }
    }

    return 0;
}
