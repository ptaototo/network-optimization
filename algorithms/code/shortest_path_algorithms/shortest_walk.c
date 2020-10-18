/* 
 * Author: Pesi Taototo
 * Date: October 13, 2020
 * File: shortest_walk.c
 * Purpose Find shortest walk from s to t that includes arc (q,r).
 */

#include <stdio.h>
#include <limits.h> // for INT_MAX which acts as "infinity" 

// Defining macros
#define V 15
#define false 0
#define true 1
typedef int bool;

/* ********************************************************************
 *     minDistance(), printSolution(), dijkstra()
 *     is from GeekforGeeks 
 *     Some small modifications were made in adding a predecessor array
 *     to the dijkstra algorithm
 *
 *https://www.geeksforgeeks.org/c-program-for-dijkstras-shortest-path-algorithm-greedy-algo-7/
 * ********************************************************************/

// A utility function to find the vertex with minimum distance value, from
// the set of vertices not yet included in shortest path tree
int minDistance(int dist[], bool sptSet[])
{
    // Initialize min value
    int min = INT_MAX, min_index;

    for (int v = 0; v < V; v++)
        if (sptSet[v] == false && dist[v] <= min)
            min = dist[v], min_index = v;

    return min_index;
}

// A utility function to print the constructed distance array
int printSolution(int vec[], int n)
{
    //printf("Vertex   Distance from Source\n");
    for (int i = 0; i < V; i++) {
        printf("%d  tt  %d\n",i, vec[i]);
	}
}

// Function that implements Dijkstra's single source shortest path algorithm 
// for a graph represented using adjacency matrix representation 
void dijkstra(int graph[V][V], int dist[V], int pred[V], int src) 
{ 
    // distance from src to i 
  
    bool sptSet[V]; // sptSet[i] will be true if vertex i is included in shortest 
    // path tree or shortest distance from src to i is finalized 
  
    // Initialize all distances as INFINITE and stpSet[] as false 
    for (int i = 0; i < V; i++) 
        dist[i] = INT_MAX, sptSet[i] = false; 
  
    // Distance of source vertex from itself is always 0 
    dist[src] = 0; 
  
    // Find shortest path for all vertices 
    for (int count = 0; count < V - 1; count++) { 
        // Pick the minimum distance vertex from the set of vertices not 
        // yet processed. u is always equal to src in the first iteration. 
        int u = minDistance(dist, sptSet); 
  
        // Mark the picked vertex as processed 
        sptSet[u] = true; 
  
        // Update dist value of the adjacent vertices of the picked vertex. 
        for (int v = 0; v < V; v++) { 
            // Update dist[v] only if is not in sptSet, there is an edge from 
            // u to v, and total weight of path from src to  v through u is 
            // smaller than current value of dist[v] 
            if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX 
                && dist[u] + graph[u][v] < dist[v]) { 
                dist[v] = dist[u] + graph[u][v];
				pred[v] = u;
			}
		}
    } 
  
    // print the constructed distance array 
    //printSolution(dist, V);
	//printSolution(pred, V);
}
/* *********************** end of GeekforGeeks code **********************/

/* ***********************************************************************
 *     shortest_walk()
 *     Author:  	Pesi Taototo
 *	   Purpose: 	Find the shortest_walk from a node (s) to (t) which 
 *		   			includes the arc (q,r).
 *					It is assumed that the arc (q,r) exists in the first place,
 *					so there is no error checking mechanism to detect if
 *					the given (q,r) is valid. In which case, the algorithm
 *					will print an erroneous walk.	
 *
 *     Inputs:      int graph_costs[V][V] - costs of the network 
 *     								arcs represented as a VxV integer array
 *     				int src - the integer value of the source node
 *     				int q, r - arc value
 *     				int trg - the integer value of the target node
 *     Output: 
 *     				Void type returns no output.
 *     				The algorithm prints to the console the shortest walk 
 *     				between a source node (s) to a node (t) which includes 
 *     				arc (q,r).
 * ***********************************************************************/
// (src) ---> (q)->(r) ---> trg
void shortest_walk(int graph_costs[V][V], int src, int q, int r, int trg) {
	int dist[V];
	int pred[V];
	int walk[V] = {INT_MAX}; // this array tracks the walk in the nodes 
	int track_the_walk = 0;
	int counter = 0; // detect loop
	
	// first element of the walk is the src node
	walk[0] = src;
	// First run of dijkstra's algorithm to find shortest path from (s) -> (q)
	dijkstra(graph_costs, dist, pred, src);
	
	int i=0, j=1;
	do {
		walk[j] = pred[i];
		printf("walkj; %d\n", walk[0]);
		i = pred[i];
		track_the_walk++;
		counter++;
		if(counter > V)
			break;
		j++;
	} while(pred[i] != q);
	
	// Second run of dijkstra's algorithm to find shortest path from (r) -> (trg)
	dijkstra(graph_costs, dist, pred, r);	

	printSolution(pred,V);	
	counter = 0;
	i=0, j=track_the_walk;
	do {
		walk[j] = pred[i];
		i = pred[i];
		counter++;
		if(counter > V)
			break;
		j++;
		track_the_walk = j;
		printf("pred[i] = trg = %d\n", pred[i]);
	} while(pred[i] != trg);

	// add target to the walk
	track_the_walk++;	
	walk[track_the_walk] = trg;
	
	printf("The walk:\n");
	i=0;
	do {
		printf("(%d)\n", walk[i]);
		i++;
		track_the_walk = i;
	} while(walk[i] != trg);

}


int main(void) {
	int src = 0, q = 0,r = 0, trg = 0;
	src = 0;
	q = 2;
	r = 13;
	trg = 10;

	// Node-node adjacency matrix containing
	// the costs of each arc
	int graph_costs[V][V] = {
		{5,2,5,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,5,0,5,0,0,0,0,0,0,0,0,0,0},
		{0,0,4,0,0,0,5,6,7,7,6,0,0,0,6},
		{0,0,0,0,3,0,0,0,0,0,0,4,3,0,0},
		{0,0,0,0,0,2,0,0,0,0,0,4,2,0,0},
		{0,0,0,0,0,0,4,0,0,0,0,0,3,2,4},
		{0,0,0,0,0,0,0,6,0,10,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,7,0,0,0,0,0,0},
		{0,0,0,0,0,0,10,0,0,2,0,0,0,0,0},
		{0,0,0,10,0,0,0,0,0,0,5,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,3,0,0,7},
		{0,0,0,0,20,0,0,0,10,0,0,0,6,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,2,0},
		{0,0,10,0,0,0,0,0,0,0,0,0,0,0,9},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,2,1},
	};
	
	shortest_walk(graph_costs, src, q, r, trg); 
	return 0;
}
