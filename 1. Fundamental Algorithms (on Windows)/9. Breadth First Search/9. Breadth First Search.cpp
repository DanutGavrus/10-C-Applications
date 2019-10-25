#include <stdio.h>
#include <stdlib.h>

// We globally declare our variables for the number of Operations
int operations = 0;
int bfsDemo[8] = { -1, -1, -1, -1, -1, -1, -1, -1 };

///Definition of a node
typedef struct Node
{
	int key;
	char color;
	int dist;
	struct Node* next;
} NodeT;

///Definition of a list
typedef struct List
{
	int listLength;
	NodeT* first;
	NodeT* last;
} ListT;

///Definition for a BFS root
typedef struct Root
{
	int key;
	int nrOfChilds;
	struct Root* rootChildrens[5];
} RootT;

///Create a node and fill it with data
NodeT* createSLLNode(int key)
{
	NodeT* p = (NodeT*)malloc(sizeof(NodeT));
	if (p)
	{
		p->key = key;
		p->color = 'W';
		p->dist = -1;
		p->next = NULL;
		return p;
	}
	return NULL;
}

///Create an empty single linked list
ListT* createEmptySLL()
{
	ListT* listPtr = (ListT*)malloc(sizeof(ListT));
	if (listPtr)
	{
		listPtr->listLength = 0;
		listPtr->first = NULL;
		listPtr->last = NULL;
		return listPtr;
	}
	return NULL;
}

///Insert at rear; does not check for duplicate keys
int insertAtRear(ListT* listPtr, NodeT* p)
{
	if (listPtr)
	{
		if (listPtr->listLength == 0) listPtr->first = p;
		else listPtr->last->next = p;
		listPtr->last = p;
		listPtr->listLength++;
		return 1;
	}
	return 0;
}

///Removing the first node
NodeT* removeFirstNode(ListT* listPtr)
{
	if (listPtr)
	{
		NodeT* p;
		p = listPtr->first;
		if (p != NULL)
		{
			listPtr->first = listPtr->first->next;
			listPtr->listLength--;
			if (listPtr->first == NULL)
			{
				listPtr->last == NULL;
			}
			return p;
		}
	}
	return NULL;
}

///Print a list
void PrintList(ListT* listPtr)
{
	int i = 0;
	if (listPtr)
	{
		NodeT* p;
		p = listPtr->first;
		if (listPtr->first == NULL) printf("none");
		else
		{
			while (i < listPtr->listLength)
			{
				printf(" %d%c", p->key, p->color);
				p = p->next;
				i++;
			}
		}
	}
	else printf("Error");
	printf("\n");
}

///Add an edge to a graph
void AddEdge(ListT* listPtr, NodeT* node)
{
	insertAtRear(listPtr, node);
}

///Print the graph
void PrintGraph(ListT* GraphLists[], int nrOfLists)
{
	for (int i = 0; i < nrOfLists; i++)
	{
		printf("Node %d forms edges with nodes:", i);
		PrintList(GraphLists[i]);
	}
}

///Print the BFS
void PrintBFS(RootT* root, int heigth)
{
	int i;
	if (root != NULL)
	{
		for (i = 0; i < heigth; i++)
		{
			printf("\t");
		}
		printf("%d\n", root->key);
		int i = 0;
		while (root->rootChildrens[i] != NULL)
		{
			PrintBFS(root->rootChildrens[i], heigth + 1);
			i++;
		}
	}
	else return;
}

///Definition for a root
RootT* createSLLRoot(int key)
{
	RootT* p = (RootT*)malloc(sizeof(RootT));
	if (p)
	{
		p->key = key;
		for (int i = 0; i < 5; i++)
		{
			p->rootChildrens[i] = NULL;
		}
		return p;
	}
	return NULL;
}

///BSF FUNCTION
RootT* CreateBFS(ListT* GraphLists[], NodeT* source)
{
	int height = 0, j;
	RootT* root, * aux, * aux2 = NULL; root = createSLLRoot(source->key);
	source->color = 'G';
	source->dist = 0;
	ListT* Queue = createEmptySLL();
	insertAtRear(Queue, source);
	aux = root;
	bfsDemo[0] = source->key;
	int position = 1;
	while (Queue->listLength > 0)
	{
		NodeT* u, * v;
		u = removeFirstNode(Queue);
		int auxVal = u->key;
		bool added = false;
		for (int j = 0; j < 8; j++) {
			if (auxVal == bfsDemo[j]) added = true;
		}
		if (!added) {
			bfsDemo[position] = u->key;
			position++;
		}
		printf("\nFrom node %d we try to visit nodes: ", u->key);
		v = GraphLists[u->key]->first;
		int i = 0, contor = 0;
		while (v != NULL)
		{
			if (v->color == 'W')
			{
				contor++;
				aux2 = createSLLRoot(v->key);
				root->rootChildrens[i] = aux2;
				printf("%d ", v->key);
				i++;
				v->color = 'G';
				v->dist = u->dist + 1;
				insertAtRear(Queue, v);
			}
			v = v->next;
		}
		if (contor == 0) printf("none because we have already been here before. ");
		if (contor != 0) printf(";Node with key %d will be Black after we have visited these nodes.", u->key);
		u->color = 'B';
		root = aux2;
	}
	return aux;
}

///Function for showing Demo
void Demo()
{
	int graphLength = 8;
	ListT** GraphLists = (ListT * *)malloc(graphLength * sizeof(ListT*));
	NodeT* nodeCopy;
	for (int i = 0; i < graphLength; i++)
	{
		GraphLists[i] = createEmptySLL();
	}
	nodeCopy = createSLLNode(1); AddEdge(GraphLists[0], nodeCopy); nodeCopy = createSLLNode(0); AddEdge(GraphLists[1], nodeCopy); //0-1
	nodeCopy = createSLLNode(4); AddEdge(GraphLists[0], nodeCopy); nodeCopy = createSLLNode(0); AddEdge(GraphLists[4], nodeCopy); //0-4
	nodeCopy = createSLLNode(5); AddEdge(GraphLists[1], nodeCopy); nodeCopy = createSLLNode(1); AddEdge(GraphLists[5], nodeCopy); //1-5
	nodeCopy = createSLLNode(3); AddEdge(GraphLists[2], nodeCopy); nodeCopy = createSLLNode(2); AddEdge(GraphLists[3], nodeCopy); //2-3
	nodeCopy = createSLLNode(5); AddEdge(GraphLists[2], nodeCopy); nodeCopy = createSLLNode(2); AddEdge(GraphLists[5], nodeCopy); //2-5
	nodeCopy = createSLLNode(6); AddEdge(GraphLists[2], nodeCopy); nodeCopy = createSLLNode(2); AddEdge(GraphLists[6], nodeCopy); //2-6
	nodeCopy = createSLLNode(6); AddEdge(GraphLists[3], nodeCopy); nodeCopy = createSLLNode(3); AddEdge(GraphLists[6], nodeCopy); //3-6
	nodeCopy = createSLLNode(7); AddEdge(GraphLists[3], nodeCopy); nodeCopy = createSLLNode(3); AddEdge(GraphLists[7], nodeCopy); //3-7
	nodeCopy = createSLLNode(6); AddEdge(GraphLists[5], nodeCopy); nodeCopy = createSLLNode(5); AddEdge(GraphLists[6], nodeCopy); //5-6
	nodeCopy = createSLLNode(7); AddEdge(GraphLists[6], nodeCopy); nodeCopy = createSLLNode(6); AddEdge(GraphLists[7], nodeCopy); //6-7
	printf("The initial graph is:(See 'Initial Graph For Demo'.png)\n");
	PrintGraph(GraphLists, graphLength);
	RootT* root;
	root = createSLLRoot(0);
	root = CreateBFS(GraphLists, GraphLists[0]->first);
	printf("\n");
	PrintBFS(root, 0);
	printf("The BFS traversal is: ");
	for (int j = 0; j < 8; j++) {
		printf("%d ", bfsDemo[j]);
	}
	printf("(See 'Initial Graph For Demo'.png)\n");
}

int main()
{
	Demo();
	//system("pause"); Working only on Windows! Solution for Linux & Windows:
	printf("\nDemo is printed above.\nPRESS ENTER TO EXIT\n");
	getchar();
	return 0;
}
