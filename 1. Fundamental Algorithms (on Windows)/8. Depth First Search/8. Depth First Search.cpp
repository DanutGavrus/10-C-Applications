#include "Profiler.h"

#include <stdio.h>
#include <stdlib.h>

Profiler profiler("Depth First Search");

// We globally declare our variables for the number of Operations
int operations = 0;
bool demo;
int dfsDemo[8] = { -1, -1, -1, -1, -1, -1, -1, -1 };
int position = 0;

///Definition of a node
typedef struct Node
{
	int start, stop, key;
	char color;
	bool onStack;
	struct Node* parent;
} NodeT;

///Definition on an edge
typedef struct Edge
{
	struct Edge* next;
	struct Node* n;
} EdgeT;

///Definition of a graph
typedef struct Graph
{
	int nrOfNodes;
	struct Node* n;
	struct Edge* e;
} GraphT;

///Definition of a stack element
typedef struct stackElement
{
	struct Node* n;
	struct stackElement* next;
} stackElementT;

///Definition of a stack
typedef struct sStack
{
	struct stackElement* top;
} sStackT;

///PUSH function for stack
void sPush(sStackT* s, NodeT* n)
{
	stackElementT* sNewElement = (stackElementT*)malloc(sizeof(stackElementT));
	sNewElement->n = n;
	sNewElement->next = s->top;
	s->top = sNewElement;
}

///POP function for stack
NodeT* pop(sStackT* s)
{
	NodeT* aux = s->top->n;
	stackElementT* sDelete = s->top;
	s->top = s->top->next;
	free(sDelete);
	return aux;
}

///Visit in DFS
void DFSVisit(GraphT* G, NodeT* n, int* time)
{
	if (demo) {
		printf("Node %d was white and have been visited;\n", n->key);
		dfsDemo[position] = n->key;
		position++;
	}
	(*time)++;
	n->start = (*time);
	n->color = 'B';
	EdgeT* current = ((G->e) + (n->key));
	while (current->n != NULL)
	{
		operations++;
		if (current->n->color == 'W')
		{
			operations++;
			current->n->parent = n;
			DFSVisit(G, current->n, time);
		}
		current = current->next;
	}
	(*time)++;
	n->stop = (*time);
}

///DFS
void DFS(GraphT* G)
{
	int i;
	for (i = 0; i < G->nrOfNodes; i++)
	{
		((G->n) + i)->color = 'W';
		((G->n) + i)->parent = NULL;
	}
	int* time = (int*)malloc(sizeof(int));
	*time = 0;
	for (i = 0; i < G->nrOfNodes; i++)
	{
		operations++;
		if (((G->n) + i)->color == 'W')
		{
			DFSVisit(G, ((G->n) + i), time);
		}
	}
}

///Function for showing Demo(or preparing the evaluation this time)
void DFSDEMO(int e, int n)
{
	operations = 0;
	bool adjMatrix[201][201] = { 0 };
	int i, j, aux1, aux2;
	for (i = 0; i < e; i++)
	{
		do
		{
			aux1 = rand() % n;
			aux2 = rand() % n;
		} while (adjMatrix[aux1][aux2] == 1);
		adjMatrix[aux1][aux2] = 1;
	}
	GraphT* G = (GraphT*)malloc(sizeof(GraphT));
	G->e = (EdgeT*)malloc(n * sizeof(EdgeT));
	G->n = (NodeT*)malloc(n * sizeof(NodeT));
	G->nrOfNodes = n;
	for (i = 0; i < G->nrOfNodes; i++)
	{
		((G->n) + i)->color = 'W';
		((G->n) + i)->onStack = 0;
		((G->n) + i)->start = -1;
		((G->n) + i)->stop = -1;
		((G->n) + i)->key = i;
		((G->n) + i)->parent = NULL;
		EdgeT* current = ((G->e) + i);
		((G->e) + i)->n = NULL;
		for (j = 0; j < G->nrOfNodes; j++)
		{
			if (adjMatrix[i][j] == 1)
			{
				current->n = ((G->n) + j);
				current->next = (EdgeT*)malloc(sizeof(EdgeT));
				current = current->next;
				current->next = NULL;
				current->n = NULL;
			}
		}
	}
	DFS(G);
}

///Function for showing evaluation
void DFSEvaluation()
{
	int e, v;
	//First eval:
	v = 100;
	for (e = 1000; e <= 5000; e += 100)
	{
		DFSDEMO(e, v);
		profiler.countOperation("FixedNrOfVert", e, operations);
	}
	//Second eval:
	e = 9000;
	for (v = 100; v <= 200; v += 10)
	{
		DFSDEMO(e, v);
		profiler.countOperation("FixedNrOfEdges", v, operations);
	}
	profiler.showReport();
}

///Function for Demo
void Demo(int e, int n)
{
	demo = true;
	int i, j, aux1, aux2;
	bool adjMatrix[8][8] = { 0 };
	adjMatrix[1][0] = adjMatrix[0][1] = 1;
	adjMatrix[4][0] = adjMatrix[0][4] = 1;
	adjMatrix[1][5] = adjMatrix[5][1] = 1;
	adjMatrix[5][2] = adjMatrix[2][5] = 1;
	adjMatrix[5][6] = adjMatrix[6][5] = 1;
	adjMatrix[2][6] = adjMatrix[6][2] = 1;
	adjMatrix[2][3] = adjMatrix[3][2] = 1;
	adjMatrix[3][6] = adjMatrix[6][3] = 1;
	adjMatrix[3][7] = adjMatrix[7][3] = 1;
	adjMatrix[6][7] = adjMatrix[7][6] = 1;
	GraphT* G = (GraphT*)malloc(sizeof(GraphT));
	G->e = (EdgeT*)malloc(n * sizeof(EdgeT));
	G->n = (NodeT*)malloc(n * sizeof(NodeT));
	G->nrOfNodes = n;
	for (i = 0; i < G->nrOfNodes; i++)
	{
		((G->n) + i)->color = 'W';
		((G->n) + i)->onStack = 0;
		((G->n) + i)->start = -1;
		((G->n) + i)->stop = -1;
		((G->n) + i)->key = i;
		((G->n) + i)->parent = NULL;
		EdgeT* current = ((G->e) + i);
		((G->e) + i)->n = NULL;
		for (j = 0; j < G->nrOfNodes; j++)
		{
			if (adjMatrix[i][j] == 1)
			{
				current->n = ((G->n) + j);
				current->next = (EdgeT*)malloc(sizeof(EdgeT));
				current = current->next;
				current->next = NULL;
				current->n = NULL;
			}
		}
	}
	DFS(G);
	printf("\nThe DFS traversal is: \n");
	for (int i = 0; i < 8; i++) {
		printf("%d ", dfsDemo[i]);
	}
	printf("\n");
}

///Functions for NotDemo
void NotDemo()
{
	demo = false;
	operations = 0;
	DFSEvaluation();
}

int main()
{
	srand((unsigned)time(NULL));
	Demo(10, 8);
	NotDemo();
	//system("pause"); Working only on Windows! Solution for Linux & Windows:
	printf("\nDemo is printed above. Graphs file was generated.\nPRESS ENTER TO EXIT\n");
	getchar();
	return 0;
}
