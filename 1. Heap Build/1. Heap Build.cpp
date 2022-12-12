#include "Profiler.h"

#include <stdio.h>
#include <stdlib.h>

constexpr auto MAX_SIZE = 10000;
constexpr auto INCREMENT = 100;

Profiler profiler("HeapBuild_BottomUp_VS_TopDown_Graphs");

// We globally declare our variables for Assignments and Comparisons
int assCom = 0, assComAvg = 0;
// Set demo for showing the correctness of the algorithms
bool demo = true;

/// Bottom Up approach
void BottomUp(int myArray[], int n)
{
	bool heap;
	int i, position, left, right, bigger, aux;
	if (demo)
	{
		// We list the initial array
		printf("The array before heapBottomUp is: ");
		for (i = 0; i < n; i++)
		{
			printf("%d ", myArray[i]);
		}
		printf("\n");
	}
	// We set A&C
	assCom = 0;
	// We create the heap using HeapBottomUp
	if (demo)
	{
		printf("We construct the heap using heapBottomUp...\n");
	}
	for (i = (n - 1) / 2; i >= 0; i--)
	{
		position = i;
		while (position <= (n - 1) / 2) // (n-1)/2 means PARENT
		{
			left = 2 * position + 1;
			bigger = left;
			if (left < n)
			{
				right = left + 1;
				assCom++;
				if (myArray[right] > myArray[left])
					bigger = right;
			}
			assCom++;
			if (myArray[bigger] > myArray[position])
			{
				assCom += 3;
				aux = myArray[position];
				myArray[position] = myArray[bigger];
				myArray[bigger] = aux;
				position = bigger;
			}
			else break;
		}
	}
	assComAvg += assCom;
	if (demo)
	{
		// We list the created Heap
		printf("The created heap using heapBottomUp is: ");
		for (i = 0; i < n; i++)
		{
			printf("%d ", myArray[i]);
		}
		printf("\n");
		printf("The number of Assigns&Comps of the method heapBottomUp is: %d\n", assCom);
	}
}

/// Top Down approach
void TopDown(int myArray[], int n)
{
	int i, aux, position;
	if (demo)
	{
		// We list the initial array
		printf("\nThe array before heapTopDown is: ");
		for (i = 0; i < n; i++)
		{
			printf("%d ", myArray[i]);
		}
		printf("\n");
	}
	// We set A&C
	assCom = 0;
	// We create the heap using heapTopDown
	if (demo)
	{
		printf("We construct the heap using heapTopDown...\n");
	}
	for (i = 1; i < n; i++)
	{
		position = i;
		while (position > 0)
		{
			assCom++;
			if (myArray[position] > myArray[(position - 1) / 2]) // (position-1)/2 means PARENT
			{
				assCom += 3;
				aux = myArray[position];
				myArray[position] = myArray[(position - 1) / 2];
				myArray[(position - 1) / 2] = aux;
				position = (position - 1) / 2;
			}
			else break;
		}
	}
	assComAvg += assCom;
	if (demo)
	{
		// We list the created Heap
		printf("The created heap using heapTopDown is: ");
		for (i = 0; i < n; i++)
		{
			printf("%d ", myArray[i]);
		}
		printf("\n");
		printf("The number of Assigns&Comps of the method heapTopDown is: %d\n", assCom);
	}
}

/// Before implementing Heap Sort we need to implement Heapify
void Heapify(int myArray[], int i, int maxPos)
{
	int position, leftChild, righChild, aux;
	while (i < maxPos)
	{
		position = i;
		leftChild = 2 * i + 1;
		righChild = leftChild + 1;
		assCom++;
		if (leftChild < maxPos && myArray[leftChild] > myArray[position])
		{
			position = leftChild;
		}
		assCom++;
		if (righChild < maxPos && myArray[righChild] > myArray[position])
		{
			position = righChild;
		}
		if (position == i) return;
		assCom += 3;
		aux = myArray[i];
		myArray[i] = myArray[position];
		myArray[position] = aux;
		i = position;
	}
}

/// Heap Sort
void HeapSort(int myArray[], int n)
{
	int i, lastPos, aux;
	if (demo)
	{
		// We list the initial array
		printf("\nThe array before heapSort is: ");
		for (i = 0; i < n; i++)
		{
			printf("%d ", myArray[i]);
		}
		printf("\n");
	}
	// We set A&C
	assCom = 0;
	// We create the heap using heapSort
	if (demo)
	{
		printf("Sorting the array using heapSort...\n");
	}
	// We build our max heap using heapBottomUp
	demo = false;
	BottomUp(myArray, n);
	demo = true;
	// We save the position of our last element
	lastPos = n - 1;
	// Continue heap sorting until we have just one element left in the array
	while (lastPos > 0)
	{
		assCom += 3;
		aux = myArray[0];
		myArray[0] = myArray[lastPos];
		myArray[lastPos] = aux;
		Heapify(myArray, 0, lastPos);
		lastPos--;
	}
	assComAvg += assCom;
	if (demo)
	{
		// We list the sorted array
		printf("The sorted array using heapSort is: ");
		for (i = 0; i < n; i++)
		{
			printf("%d ", myArray[i]);
		}
		printf("\n");
		printf("The number of Assigns&Comps of the method heapSort is: %d\n", assCom);
	}
}

/// We create the function for the average case using bottomUp
void BottomUpAvg()
{
	int n, j;
	int myArray[MAX_SIZE];
	for (n = 100; n <= MAX_SIZE; n += INCREMENT)
	{
		assComAvg = 0;
		for (j = 0; j <= 4; j++)
		{
			FillRandomArray(myArray, n);
			BottomUp(myArray, n);
		}
		profiler.countOperation("bottomUpAssComAvg", n, assComAvg / 5);
	}
}

/// We create the function for the average case using topDown
void TopDownAvg()
{
	int n, j;
	int myArray[MAX_SIZE];
	for (n = 100; n <= MAX_SIZE; n += INCREMENT)
	{
		assComAvg = 0;
		for (j = 0; j <= 4; j++)
		{
			FillRandomArray(myArray, n);
			TopDown(myArray, n);
		}
		profiler.countOperation("topDownAssComAvg", n, assComAvg / 5);
	}
}

/// We create the function for the worst case using bottomUp
void BottomUpWorst()
{
	int n, i;
	int myArray[MAX_SIZE];
	for (n = 100; n <= MAX_SIZE; n += INCREMENT)
	{
		for (i = 0; i < n; i++)
		{
			myArray[i] = i;
		}
		BottomUp(myArray, n);
		profiler.countOperation("bottomUpAssComWorst", n, assCom);
	}
}

/// We create the function for the worst case using topDown
void TopDownWorst()
{
	int n, i;
	int myArray[MAX_SIZE];
	for (n = 100; n <= MAX_SIZE; n += INCREMENT)
	{
		for (i = 0; i < n; i++)
		{
			myArray[i] = i;
		}
		TopDown(myArray, n);
		profiler.countOperation("topDownAssComWorst", n, assCom);
	}
}

int main()
{
	/// We give values to our array for the correctness test
	int n = 6;
	int myArray[6];
	// Bottom Up:
	myArray[0] = 5;
	myArray[1] = 2;
	myArray[2] = 7;
	myArray[3] = 4;
	myArray[4] = 12;
	myArray[5] = 11;
	BottomUp(myArray, n);
	// Top Down:
	myArray[0] = 5;
	myArray[1] = 2;
	myArray[2] = 7;
	myArray[3] = 4;
	myArray[4] = 12;
	myArray[5] = 11;
	TopDown(myArray, n);
	// Heap Sort:
	myArray[0] = 5;
	myArray[1] = 2;
	myArray[2] = 7;
	myArray[3] = 4;
	myArray[4] = 12;
	myArray[5] = 11;
	HeapSort(myArray, n);
	// We get out of the testing mode
	demo = false;
	printf("\nGenerating the graphs file, this might take a while...\nYou can find a previously generated graphs file in the folder.\n");
	/// We create the graphs
	BottomUpAvg();
	TopDownAvg();
	BottomUpWorst();
	TopDownWorst();
	/// We group the graph for the comparisons
	profiler.createGroup("AVG bottomUp VS topDown", "bottomUpAssComAvg", "topDownAssComAvg");
	profiler.createGroup("WORST bottomUp VS topDown", "bottomUpAssComWorst", "topDownAssComWorst");
	// We create the file with the graphs
	profiler.showReport();
	//system("pause"); Working only on Windows! Solution for Linux & Windows:
	printf("\nDemo is printed above. Graphs file was generated.\nPRESS ENTER TO EXIT...");
	getchar();
	return 0;
}