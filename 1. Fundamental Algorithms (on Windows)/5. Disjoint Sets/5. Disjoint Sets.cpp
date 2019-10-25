#include "Profiler.h"

#include <stdio.h>
#include <stdlib.h>

Profiler profiler("Disjoint Sets");

// We globally declare our variables for the number of Operations
int operations = 0;
// We globally declare our matrix for checking where do we have edges
int isEdge[10000][10000];

// We declare our node structure
typedef struct Node
{
	int key;
	int Rank;
	Node* parent;
}NodeT;

// We declare our edge structure
typedef struct Edge
{
	int weig;
	Node* start;
	Node* stop;
}EdgeT;

// Space allocation for one node
NodeT* CreateEmptyNode(int key)
{
	NodeT* node = (NodeT*)malloc(sizeof(NodeT));
	if (node)
	{
		node->key = key;
		node->Rank = 0;
		node->parent = NULL;
		return node;
	}
	else return NULL;
}

// Space allocation for one edge
EdgeT* CreateEmptyEdge(int weig)
{
	EdgeT* edge = (EdgeT*)malloc(sizeof(EdgeT));
	if (edge)
	{
		edge->weig = weig;
		edge->start = NULL;
		edge->stop = NULL;
		return edge;
	}
	else return NULL;
}

// Creating a set
void MakeSet(NodeT* node)
{
	node->parent = node; operations++;
	node->Rank = 0;
}

// Finding in which set is a node
NodeT* FindSet(NodeT* node)
{
	operations++; if (node != node->parent)
	{
		node->parent = FindSet(node->parent);
	}
	return node->parent;
}

// Linking 2 sets
void Link2Sets(NodeT* node1, NodeT* node2)
{
	operations++; if (node1->Rank > node2->Rank)
	{
		node2->parent = node1; operations++;
	}
	else
	{
		node1->parent = node2; operations++;
		operations++; if (node1->Rank == node2->Rank)
		{
			node2->Rank++;
		}
	}
}

// Union of 2 sets
void Union2in1Set(NodeT* node1, NodeT* node2)
{
	Link2Sets(FindSet(node1), FindSet(node2));
}

// Create the biggest set
void CreateOneSet(NodeT* nodesArray[])
{
	int i;
	NodeT* aux;
	// Make 5 sets, one with every element
	for (i = 0; i < 5; i++)
	{
		MakeSet(nodesArray[i]);
	}
	// Union for 0&1 and find 4
	printf("\nMaking a union between nodes 0 and 1...\n");
	Union2in1Set(nodesArray[0], nodesArray[1]);
	aux = FindSet(nodesArray[0]);
	printf("Our biggest set is now: \n");
	for (i = 0; i < 5; i++)
	{
		if (FindSet(nodesArray[i]) == aux)
			printf("%d ", nodesArray[i]->key);
	}
	aux = FindSet(nodesArray[4]);
	printf("\nNode 4 is in the set: %d\n", aux->key);
	// Union for 0&2 and find 3
	printf("\nMaking a union between nodes 0 and 2...\n");
	Union2in1Set(nodesArray[0], nodesArray[2]);
	aux = FindSet(nodesArray[0]);
	printf("Our biggest set is now: \n");
	for (i = 0; i < 5; i++)
	{
		if (FindSet(nodesArray[i]) == aux)
			printf("%d ", nodesArray[i]->key);
	}
	aux = FindSet(nodesArray[3]);
	printf("\nNode 3 is in the set: %d\n", aux->key);
	// Union for 0&3 and find 2
	printf("\nMaking a union between nodes 0 and 3...\n");
	Union2in1Set(nodesArray[0], nodesArray[3]);
	aux = FindSet(nodesArray[0]);
	printf("Our biggest set is now: \n");
	for (i = 0; i < 5; i++)
	{
		if (FindSet(nodesArray[i]) == aux)
			printf("%d ", nodesArray[i]->key);
	}
	aux = FindSet(nodesArray[2]);
	printf("\nNode 2 is in the set: %d\n", aux->key);
	// Union for 0&4 and find 1
	printf("\nMaking a union between nodes 0 and 4...\n");
	Union2in1Set(nodesArray[0], nodesArray[4]);
	aux = FindSet(nodesArray[0]);
	printf("Our biggest set is now: \n");
	for (i = 0; i < 5; i++)
	{
		if (FindSet(nodesArray[i]) == aux)
			printf("%d ", nodesArray[i]->key);
	}
	aux = FindSet(nodesArray[1]);
	printf("\nNode 1 is in the set: %d\n", aux->key);
	// Find 0
	aux = FindSet(nodesArray[0]);
	printf("Node 0 is in the set: %d\n", aux->key);
}

// Kruskal
void Kruskal(NodeT* nodesArray[], EdgeT* edgesArray[], int nrOfNodes, int nrOfEdges, bool demo)
{
	int i, j = 0;
	if (demo)
	{
		printf("\nThe tree has %d nodes 0 to %d and its %d edges with their weights are: ", nrOfNodes, nrOfNodes - 1, nrOfEdges);
		for (i = 0; i < nrOfEdges; i++)
		{
			printf("(%d,%d)-%d ", edgesArray[i]->start->key, edgesArray[i]->stop->key, edgesArray[i]->weig);
		}
	}
	EdgeT** MST = (EdgeT**)malloc(nrOfEdges * sizeof(EdgeT*));
	for (i = 0; i < nrOfEdges; i++)
	{
		MST[i] = CreateEmptyEdge(0);
	}
	for (i = 0; i < nrOfNodes; i++)
	{
		MakeSet(nodesArray[i]);
	}
	for (i = 0; i < nrOfEdges; i++)
	{
		operations++; if (FindSet(edgesArray[i]->start) != FindSet(edgesArray[i]->stop))
		{
			MST[j] = edgesArray[i]; operations++;
			j++;
			Union2in1Set(edgesArray[i]->start, edgesArray[i]->stop);
		}
	}
	if (demo)
	{
		printf("\nIt`s MST is: ");
		for (i = 0; i < j; i++)
		{
			printf("(%d,%d) ", MST[i]->start->key, MST[i]->stop->key);
		}
		printf("\n");
	}
}

///Function for showing Demo
void Demo()
{
	/// Demo for sets:
	int i;
	NodeT* nodesArray[9];
	for (i = 0; i < 5; i++)
	{
		nodesArray[i] = CreateEmptyNode(i);
	}
	CreateOneSet(nodesArray);
	for (i = 0; i < 5; i++)
	{
		free(nodesArray[i]);
	}
	/// Demo for Kruskal
	for (i = 0; i < 9; i++)
	{
		nodesArray[i] = CreateEmptyNode(i);
	}
	EdgeT* edgesArray[6];
	for (i = 0; i < 6; i++)
	{
		edgesArray[i] = CreateEmptyEdge(i);
	}
	edgesArray[0]->start = nodesArray[0];
	edgesArray[0]->stop = nodesArray[1];
	edgesArray[1]->start = nodesArray[1];
	edgesArray[1]->stop = nodesArray[3];
	edgesArray[2]->start = nodesArray[3];
	edgesArray[2]->stop = nodesArray[5];
	edgesArray[4]->start = nodesArray[5];
	edgesArray[4]->stop = nodesArray[6];
	edgesArray[3]->start = nodesArray[0];
	edgesArray[3]->stop = nodesArray[6];
	edgesArray[5]->start = nodesArray[0];
	edgesArray[5]->stop = nodesArray[3];
	Kruskal(nodesArray, edgesArray, 9, 6, true);
	for (i = 0; i < 9; i++)
	{
		free(nodesArray[i]);
	}
	for (i = 0; i < 6; i++)
	{
		free(edgesArray[i]);
	}
}

///Functions for evaluations
void NotDemo()
{
	printf("\nNow generating the graphs file, this might take a while...\nAlso, you can find an already generated graph file in the folder.\n");
	int n, m, i, j, start, stop;
	for (n = 100; n <= 10000; n += 100)
	{
		m = n * 4;
		operations = 0;
		NodeT** nodesArray = (NodeT**)malloc(n * sizeof(NodeT*));
		for (i = 0; i < n; i++)
		{
			for (j = 0; j < n; j++)
			{
				isEdge[i][j] = 0;
			}
		}
		for (i = 0; i < n; i++)
		{
			nodesArray[i] = CreateEmptyNode(i);
		}
		EdgeT** edgesArray = (EdgeT**)malloc(m * sizeof(EdgeT*));
		for (i = 0; i < m; i++)
		{
			edgesArray[i] = CreateEmptyEdge(i);
		}
		int* randomWeigs = (int*)malloc(m * sizeof(int));
		FillRandomArray(randomWeigs, m, 10, 10000, false, 1);
		for (i = 0; i < m; i++)
		{
			start = rand() % n;
			stop = rand() % n;
			while (isEdge[start][stop])
			{
				start = rand() % n;
				stop = rand() % n;
			}
			edgesArray[i]->start = nodesArray[start];
			edgesArray[i]->stop = nodesArray[stop];
			edgesArray[i]->weig = randomWeigs[i];
			isEdge[start][stop] = 1;
			isEdge[stop][start] = 1;
		}
		Kruskal(nodesArray, edgesArray, n, m, false);
		profiler.countOperation("KruskalAlgorithm", n, operations);
		for (i = 0; i < n; i++)
		{
			free(nodesArray[i]);
		}
		for (i = 0; i < m; i++)
		{
			free(edgesArray[i]);
		}
	}
	profiler.showReport();
}

int main()
{
	srand((unsigned)time(NULL));
	Demo();
	NotDemo();
	//system("pause"); Working only on Windows! Solution for Linux & Windows:
	printf("\nDemo is printed above. Graphs file was generated.\nPRESS ENTER TO EXIT\n");
	getchar();
	return 0;
}
