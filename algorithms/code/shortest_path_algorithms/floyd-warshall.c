#include <stdio.h>
#include <limits.h>

#define N 15

void printmatrix(int nodes[][N]) {
	for(int i=0; i<N; i++) {
		for(int j=0; j<N; j++) {
			printf("%d ", nodes[i][j]);
		}
		printf("\n");
	}
}

void floyd_warshall(int costs[][N], int dist[][N], int pred[][N]) {
	for(int i=0; i<N; i++) {
		for(int j=0; j<N; j++) {
			dist[i][j] = INT_MAX;
			pred[i][j] = 0;
		}
	}
	for(int i=0; i<N; i++) {
		dist[i][i] = 0;
	}
	// if arc(i,j) exists, set d[i,j] = c_ij and pred[i,j] = i
	for(int i=0; i<N; i++) {
		for(int j=0; j<N; j++) {
			if (costs[i][j] != 0) {
				dist[i][j] = costs[i][j];
				pred[i][j] = i;
			}
		}
	}
	printmatrix(dist);
	for(int k=1; k<N; k++) {
		for(int i=0; i<N; i++) {
			for(int j=0; j<N; j++) {
				if(dist[i][j] != INT_MAX && dist[i][k] != INT_MAX && dist[k][j] != INT_MAX) {
					if (dist[i][j] > (dist[i][k] + dist[k][j])) {
						dist[i][j] = dist[i][k] + dist[k][j];
						pred[i][j] = pred[k][j];
					}
				}
			}
		}
	}
	printmatrix(pred);
	printf("++++++++++++++++\n");
	printmatrix(dist);
}

int main(void) {
	printf("Hello, world!\n");
	int nodes[N][N] = {
	{0,0,10,10,10,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,10,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,10,0,0,0,0,0,0,0},
	{0,0,10,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,10,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,10,0,0,10,0,0,0,10,0,0,0},
	{0,0,0,0,10,10,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,10,0,0,0},
	{0,0,10,0,0,0,0,0,0,0,0,10,10,0},
	{0,0,0,0,0,0,10,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,10,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,10,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,10,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	};
	int dist[N][N] = {0};
	int pred[N][N] = {0};
	

	//printmatrix(nodes);
	//printf("%d\n", INT_MAX);
	floyd_warshall(nodes, dist, pred);

	return 0;
}
