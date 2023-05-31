#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define V 10
#define INF 99999

// functie pentru a genera o valoare aleatoare intre 0 si max
int rand_int(int max) {
    return rand() % (max + 1);
}

int main() {
    int graph[V][V]; // matricea de adiacenta pentru graf
    int dist[V]; // distantele minime de la sursa
    int visited[V]; // vector de marcaj pentru nodurile vizitate
    int i, j, u, v, min_dist, src = 0;

    // initializam generatorul de numere aleatoare
    srand(time(NULL));

    // generam graful aleator
    for(i = 0; i < V; i++) {
        for(j = i; j < V; j++) {
            if(i == j) {
                graph[i][j] = 0; // nu exista muchii de la un nod la el insusi
            } else {
                // generam o valoare aleatoare intre 0 si 20 pentru ponderile muchiilor
                int weight = rand_int(20);
                graph[i][j] = weight;
                graph[j][i] = weight; // graful este neorientat, deci adaugam muchiile in ambele directii
            }
        }
    }

    // initializam distantele minime si vectorul de marcaj
    for(i = 0; i < V; i++) {
        dist[i] = INF;
        visited[i] = 0;
    }

    // distanta minima de la sursa la sursa este 0
    dist[src] = 0;



    // aplicam algoritmul lui Dijkstra
    for(i = 0; i < V - 1; i++) {
        // gasim nodul nevizitat cu distanta minima de la sursa
        min_dist = INF;
        for(j = 0; j < V; j++) {
            if(!visited[j] && dist[j] < min_dist) {
                min_dist = dist[j];
                u = j;
            }
        }

        // marcăm nodul ca fiind vizitat
        visited[u] = 1;

        // actualizam distantele minime catre vecinii nevizitati
        for(v = 0; v < V; v++) {
            if(!visited[v] && graph[u][v] && dist[u] + graph[u][v] < dist[v]) {
                dist[v] = dist[u] + graph[u][v];
            }
        }
    }
    //printf("Nodul aleator: %d\n ", weight);

    printf("Matricea de adiacenta:\n");
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            printf("%2d ", graph[i][j]);
        }
        printf("\n");
    }

    // afisam distantele minime
    printf("Distante minime de la nodul %d la celelalte noduri:\n", src);
    for(i = 0; i < V; i++) {
        printf("%d -> %d: %d\n", src, i, dist[i]);
    }

    return 0;
}
