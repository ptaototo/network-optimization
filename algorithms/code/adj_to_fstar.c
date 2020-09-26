#include <stdio.h>
#include <string.h>

void print_matrix(int dimension, int matrix[][dimension]) {
	for(int i=0; i<dimension; i++) {
		for(int j=0; j<dimension; j++) {
			printf("%d ", matrix[i][j]);		
		}
	}
		putchar('\n');
}

void print_vector(int dimension, int vector[]) {
	for(int i=0; i<dimension; i++) {
		printf("i=%d, %d\n",i, vector[i]);
	}
}

/* func void adj2fstar(int, int, int[][], int[][], int[][]) takes 5 arguments:
 *	dimension (number of nodes), dim_arcs (number of arcs), adjacency matrix, cost matrix, capacities matrix. 
 *	And converts an adjacency matrix to a forward and reverse star representation
 */
void adj2fstar(int dimension, int dim_arcs, int adj_matrix[][dimension], int costs[][dimension], int capacities[][dimension]) {
    int tails[dim_arcs], heads[dim_arcs];
    int costs_vec[dim_arcs], capacities_vec[dim_arcs];
    int point[dimension+1], rpoint[dim_arcs], trace[dim_arcs];
    int counter = 0;
    int thcc[4][dim_arcs];	
    /* Initialize the variable int arrays with 0
     *	Time complexity of memset() is O(n)
     */
    memset(tails, 0, dim_arcs*sizeof(int)); 
    memset(heads, 0, dim_arcs*sizeof(int));
    memset(costs_vec, 0, dim_arcs*sizeof(int));
    memset(capacities_vec, 0, dim_arcs*sizeof(int));
    memset(point, 0, dim_arcs*sizeof(int));
    memset(rpoint, 0, dim_arcs*sizeof(int));
    memset(trace, 0, dim_arcs*sizeof(int));

    /* Populate tails, heads, costs_vec, capacities_vec
     * Time complexity is O(n^2) 
     */
    for(int i=0; i < dimension; i++) {
        for(int j=0; j<dimension; j++) {
            if(adj_matrix[i][j] == 1) {
                tails[counter] = i+1;
                heads[counter] = j+1;
                costs_vec[counter] = costs[i][j];
                capacities_vec[counter] = capacities[i][j];

                counter++;
            }
        }
    }

    /* Populate point and rpoint arrays
     * 	Time complexity O(n)
     */
    point[0] = 1; // definition
    point[dimension] = dim_arcs+1;
    for(int i=1,j=1,k=1; i<dim_arcs; i++) {
	    if(tails[i-1] != tails[i]) {
		    point[j] = i+1;
		    j++;
	    }
	    if(heads[i-1] != heads[i]) {
		    rpoint[k] = i+1;
		    k++;
	    }
    }

      /* Find minimum and maximum data in the heads array
       *  This will help with generating the trace[] array
       */
    int min=heads[0], max=heads[0];
    for(int i=0; i<dim_arcs; i++) {
        if(min > heads[i]) {
            min = heads[i];
        }

        if(max < heads[i]) {
          max = heads[i];
        }
    }

      /*  Generate the trace[] array
       *
       */
    for(int i=0, counter=0; i<dim_arcs; i++) {
        for(int j=0; j<dim_arcs; j++) {
            if(heads[j] == min) {
                trace[counter++] = j+1;
      	    }
        }
        min++;
    }
}


int main(void) {
	// take a node-node adjacency matrix as input and output the forward and reverse star representation
	// forward & star representation needs: point, tail, head, cost, capacities, trace, rpoint
	int adj_matrix[5][5] = { 
		{0, 1, 1, 0, 0}, 
		{0, 0, 0, 1, 0}, 
		{0, 1, 0, 0, 0}, 
		{0, 0, 1, 0, 1}, 
		{0, 0, 1, 1, 0}
	};

	int costs[5][5] = {
		{0, 25, 35, 0, 0},
		{0, 0, 0, 15, 0},
		{0, 45, 0, 0, 0},
		{0, 0, 15, 0, 45},
		{0, 0, 25, 35, 0}
	};

	int capacities[5][5] = {
		{0, 30, 50, 0, 0},
		{0, 0, 0, 40, 0},
		{0, 10, 0, 0, 0},
		{0, 0, 30, 0, 60},
		{0, 0, 20, 50, 0}
	};
	
	adj2fstar(5, 8, adj_matrix, costs, capacities);

	return 0;
}
