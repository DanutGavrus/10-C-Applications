#include "Profiler.h"

#include <stdio.h>
#include <stdlib.h>

Profiler profiler("Merge_K_Lists_Graphs");

// We globally declare our variables for Assignments and Comparisons
int operations = 0, operationsAvg = 0;
// Set demo for showing the correctness of the algorithms
bool demo = true;

/// Definition of a node
typedef struct Node
{
	int key;
	struct Node* next;
} NodeT;

/// Definition of a list
typedef struct List
{
	int listLength;
	NodeT* first;
	NodeT* last;
} ListT;

/// Definition of a heap structure
typedef struct Heap
{
	int key;
	int source;
} HeapT;

/// Create an empty single linked list
ListT* CreateEmptySLL()
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

/// Create a node and fill it with data
NodeT* CreateSLLNode(int key)
{
	NodeT* p = (NodeT*)malloc(sizeof(NodeT));
	if (p)
	{
		p->next = NULL;
		p->key = key;
		return p;
	}
	return NULL;
}

/// Insert at rear; does not check for duplicate keys
int InsertAtRear(ListT* listPtr, NodeT* p)
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

/// Removing the first node
int RemoveFirstNode(ListT* listPtr)
{
	if (listPtr)
	{
		NodeT* p;
		p = listPtr->first;
		if (p != NULL)
		{
			listPtr->first = listPtr->first->next;
			free(p);
			listPtr->listLength--;
			if (listPtr->first == NULL)
			{
				listPtr->last == NULL;
			}
			return 1;
		}
	}
	return 0;
}

/// Print a list
void PrintList(ListT* listPtr)
{
	int i = 0;
	printf("The list is:");
	if (listPtr)
	{
		NodeT* p;
		p = listPtr->first;
		if (listPtr->first == NULL) printf(" none");
		else
		{
			while (i < listPtr->listLength)
			{
				printf(" %d", p->key);
				p = p->next;
				i++;
			}
		}
	}
	else printf("Error");
	printf("\n");
}

/// Deleting a list
void Purge(ListT* listPtr)
{
	NodeT* p;
	while (listPtr->first != NULL)
	{
		p = listPtr->first;
		listPtr->first = listPtr->first->next;
		free(p);
	}
	listPtr->last = NULL;
	listPtr->listLength = 0;
}

/// Generating the Lists
void GenerateLists(int nrOfLists, int listsLength, ListT* List[])
{
	int i, j;
	int* myArray = (int*)malloc(listsLength * sizeof(int));
	for (i = 0; i < nrOfLists; i++)
	{
		FillRandomArray(myArray, listsLength, 10, 10000, true, 1);
		List[i] = CreateEmptySLL();
		for (j = 0; j < listsLength; j++)
		{
			NodeT* node;
			node = CreateSLLNode(myArray[j]);
			InsertAtRear(List[i], node);
		}
	}
	if (demo) printf("The generated lists are: \n");
	if (demo) for (i = 0; i < nrOfLists; i++)
		PrintList(List[i]);
}

/// Asking for the Parameters
void AskForParameters(int& nrOfLists, int& listsLength)
{
	printf("\nHow many lists do you want to create for the merging test?\n");
	scanf("%d", &nrOfLists);
	printf("How long do you want the created lists to be ?\n");
	scanf("%d", &listsLength);
	printf("\n");
}

/// Before mergeSort we need to implement the merge function
void Merge2Lists(ListT* List0, ListT* List1, int listsLength)
{
	ListT* newList;
	NodeT* first0, * first1;
	first0 = List0->first;
	first1 = List1->first;
	newList = CreateEmptySLL();
	int i = 0, j = 0;
	while (i < listsLength && j < listsLength)
	{
		if (first0->key < first1->key)
		{
			InsertAtRear(newList, first0);
			first0 = first0->next;
			i++;
		}
		else
		{
			InsertAtRear(newList, first1);
			first1 = first1->next;
			j++;
		}
	}
	while (i < listsLength)
	{
		InsertAtRear(newList, first0);
		first0 = first0->next;
		i++;
	}
	while (j < listsLength)
	{
		InsertAtRear(newList, first1);
		first1 = first1->next;
		j++;
	}
	PrintList(newList);
}

/// Before implementing MinHeap we need to implement MinHeapify
void MinHeapify(HeapT* myHeap, int listsLength, int position)
{
	HeapT aux;
	int leftChildPos, rightChildPos, smallestPos;
	leftChildPos = 2 * position + 1;
	if (leftChildPos < listsLength - 1) rightChildPos = leftChildPos + 1;
	else rightChildPos = 0;
	smallestPos = position;
	if (leftChildPos >= listsLength) leftChildPos = 0;
	operations++;
	if (leftChildPos && leftChildPos < listsLength && myHeap[leftChildPos].key < myHeap[position].key)
	{
		smallestPos = leftChildPos;
	}
	operations++;
	if (rightChildPos && rightChildPos < listsLength && myHeap[rightChildPos].key < myHeap[smallestPos].key)
	{
		smallestPos = rightChildPos;
	}
	if (smallestPos != position)
	{
		operations += 3;
		aux = myHeap[position];
		myHeap[position] = myHeap[smallestPos];
		myHeap[smallestPos] = aux;
		MinHeapify(myHeap, listsLength, smallestPos);
	}
}

/// Now we can implement BuildMinHeap
void BuildMinHeap(HeapT* myHeap, int listsLength)
{
	int middle = listsLength / 2;
	while (middle >= 0)
	{
		MinHeapify(myHeap, listsLength, middle);
		middle--;
	}
}

/// Now we can merge k lists
void MergeKLists(int nrOfLists, int listsLength, ListT* List[])
{
	int i, j;
	ListT* mergedLists;
	HeapT* myHeap = (HeapT*)malloc(nrOfLists * sizeof(HeapT));
	mergedLists = CreateEmptySLL();
	// Create a min heap with the first element of each list
	for (i = 0; i < nrOfLists; i++)
	{
		operations++;
		myHeap[i].key = List[i]->first->key;
		myHeap[i].source = i;
	}
	BuildMinHeap(myHeap, nrOfLists);
	for (i = 0; i < nrOfLists * listsLength; i++)
	{
		// Store the minimum element in output
		operations++;
		HeapT root = myHeap[0];
		NodeT* node;
		node = CreateSLLNode(root.key);
		InsertAtRear(mergedLists, node);
		operations++;
		// Replace current root with the next element
		if (List[root.source]->first->next != NULL)
		{
			operations++;
			root.key = List[root.source]->first->next->key;
			RemoveFirstNode(List[root.source]);
		}
		// If root was the last element in the array
		else
		{
			operations++;
			root.key = 2147483647;
		}
		// Replace root with the next element of the array
		operations++;
		myHeap[0] = root;
		MinHeapify(myHeap, nrOfLists, 0);
	}
	if (demo) PrintList(mergedLists);
}

/// We create the function for the average case using topDown
void MergeKListsAvg()
{
	printf("\nNow generating the graphs file, this might take a while...\nAlso, you can find an already generated graph file in the folder.\n");
	int n, j, k1 = 5, k2 = 10, k3 = 100;
	for (n = 100; n <= 1000; n += 100)
	{
		ListT** List = (ListT * *)malloc(n * k1 * sizeof(ListT*));
		operationsAvg = 0;
		for (j = 0; j < 5; j++)
		{
			operations = 0;
			GenerateLists(k1, n, List);
			MergeKLists(k1, n, List);
			operationsAvg += operations;
		}
		profiler.countOperation("MergeKListsAvgKLists1", n * k1, operationsAvg / 5);
	}
	for (n = 100; n <= 1000; n += 100)
	{
		ListT** List = (ListT * *)malloc(n * k2 * sizeof(ListT*));
		operationsAvg = 0;
		for (j = 0; j < 5; j++)
		{
			operations = 0;
			GenerateLists(k2, n, List);
			MergeKLists(k2, n, List);
			operationsAvg += operations;
		}
		profiler.countOperation("MergeKListsAvgKLists2", n * k2, operationsAvg / 5);
	}
	for (n = 100; n <= 1000; n += 100)
	{
		ListT** List = (ListT * *)malloc(n * k3 * sizeof(ListT*));
		operationsAvg = 0;
		for (j = 0; j < 5; j++)
		{
			operations = 0;
			GenerateLists(k3, n, List);
			MergeKLists(k3, n, List);
			operationsAvg += operations;
		}
		profiler.countOperation("MergeKListsAvgKLists3", n * k3, operationsAvg / 5);
	}
}

int main()
{
	int nrOfLists, listsLength;
	// Input the length of the 2 lists for merging
	printf("How long do you want the 2 randomly created lists for demo to be?\n");
	scanf("%d", &listsLength);
	printf("\n");
	// Declare our lists
	ListT* ListDemo[2];
	GenerateLists(2, listsLength, ListDemo);
	/// Merge 2 Lists
	Merge2Lists(ListDemo[0], ListDemo[1], listsLength);
	// Input the parameters
	AskForParameters(nrOfLists, listsLength);
	ListT** List = (ListT * *)malloc(nrOfLists * listsLength * sizeof(ListT*));
	// Declare our lists
	GenerateLists(nrOfLists, listsLength, List);
	// BuildMinHeap:
	MergeKLists(nrOfLists, listsLength, List);
	// We get out of the testing mode
	demo = false;
	// We set the nr of Operations
	operations = 0;
	operationsAvg = 0;
	/// We create the graphs
	MergeKListsAvg();
	// We create the file with the graphs
	profiler.showReport();
	//system("pause"); Working only on Windows! Solution for Linux & Windows:
	printf("\nDemo is printed above. Graphs file was generated.\nPRESS ENTER TO EXIT\n");
	getchar();
	getchar();
	return 0;
}
