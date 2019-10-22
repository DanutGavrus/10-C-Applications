/**
--------------QUICK SORT ANALYSIS---------------

---WORST CASE ANALYSIS---
-Quicksort's worst-case running time is O(n^2)-
The worst case of quickSort is either an increasing or decreasing ordered array. In this case, the pivot chosen by the partition function
is always either the smallest or the largest element in the subarray. Then, one of the partitions will contain no elements and the other
partition will contain n-1 elements. So the recursive calls will be on subarrays of sizes 0 and n-1.

---BEST CASE ANALYSIS---
-Quicksort`s best-case running time is O(nlog(n))-
The best case of quickSort occurs when the partitions are as evenly balanced as possible which means that their sizes are equal or differ by
1 of each other. Each partition has at most n/2 elements and the tree of subproblem sizes looks a lot like the tree of subproblem sizes for
merge sort, with the partitioning times looking like the merging time, therefore, using big O notation, we get the same result as for merge sort.

---AVERAGE CASE ANALYSIS---
-Quicksort`s average-case running time is O(nlog(n))-
Firstly, the average-case running time cannot be better than the best-case running time. Here we have a happy case because it is the same.
Running time of partition of N elements is, of course, O(n). Now, call partition and we get 2 subarrays of sizes Nl(n elements left) and
Nr(n elements right). So, T(N) = N + T(Nl) + T(Nr).
Nl is equally likely to have each of the values 0, 1, 2, … N-1 and NR is also equally likely to have each of the values 0, 1, 2, … N-1.
Thus Nl+Nr = N-1, thus T(Nl) = T(Nr) in average. So, NT(N) = (N+1)T(N-1) + 2N. By doing a lot of calculations, we get O(nlogn).
**/

#include "Profiler.h"

#include <stdio.h>
#include <stdlib.h>

constexpr auto MAX_SIZE = 10000;
constexpr auto INCREMENT = 100;

Profiler profiler("QuickSort_VS_QuickSelect_Heap");

// We globally declare our variables for Assignments and Comparisons
int assCom = 0, assComAvg = 0;
// Set demo for showing the correctness of the algorithms
bool demo = true;

/// Before implementing Quick Sort we need to implement a function for partitioning
int CreatePartition(int myArray[], int left, int right)
{
	int i, j, pivot, aux; // All elements on the left side of pivot are smaller and on the right side are higher
	assCom++;
	pivot = myArray[right];
	i = left - 1;
	for (j = left; j <= right - 1; j++) // j will be actual position
	{
		assCom++;
		if (myArray[j] <= pivot) // If element from this position < pivot, change them
		{
			i++;
			assCom += 3;
			aux = myArray[i];
			myArray[i] = myArray[j];
			myArray[j] = aux;
		}
	}
	assCom += 3;
	aux = myArray[i + 1];
	myArray[i + 1] = myArray[right];
	myArray[right] = aux;
	return (i + 1);
}

/// Quick Sort
void QuickSort(int myArray[], int left, int right)
{
	int i, PI, j; // left  --> Left position,  right  --> Right position
	if (left < right)
	{
		PI = CreatePartition(myArray, left, right); // PI is the PARTITION POSITION
		QuickSort(myArray, left, PI - 1);
		QuickSort(myArray, PI + 1, right);
	}
}

/// Quick Select
int QuickSelect(int myArray[], int left, int right, int k)
{
	if (k > 0 && k <= right - left + 1)
	{
		int position = CreatePartition(myArray, left, right);
		if (position - left == k - 1) return myArray[position]; // If position is same as k

		if (position - left > k - 1) return QuickSelect(myArray, left, position - 1, k); // If position is more, recur for left subarray
		return QuickSelect(myArray, position + 1, right, k - position + left - 1); // Else recur for right subarray
	}
	return INT_MAX; //RETURNS k-th SMALLEST ELEMENT
}

/// Top Down
void TopDown(int myArray[], int n)
{
	int i, aux, position, j;
	if (demo)
	{
		//We list the initial array
		printf("\nThe array before heapTopDown is: ");
		for (i = 0; i < n; i++)
		{
			printf("%d ", myArray[i]);
		}
		printf("\n");
	}
	//We create the heap using heapTopDown
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
			if (myArray[position] > myArray[(position - 1) / 2]) //(position-1)/2 means PARENT
			{
				assCom += 3;
				aux = myArray[position];
				myArray[position] = myArray[(position - 1) / 2];
				myArray[(position - 1) / 2] = aux;
				position = (position - 1) / 2;
			}
			else break;
		}
		/*if(demo)
		{
			printf("The array in the step %d is: ", i);
			for(j=0; j<n; j++)
			{
				printf("%d ",myArray[j]);
			}
			printf("\n");
		}*/
	}
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

/// Before implementing heapSort we need to implement heapify
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
	int i, lastPos, aux, j = 1;
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
	// We create the heap using heapSort
	if (demo)
	{
		printf("First we need to create the heap...");
	}
	// We build our max heap using heapBottomUp
	TopDown(myArray, n);
	if (demo)
	{
		printf("Now sorting the array using heapSort...\n");
	}
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
		/*printf("The array in the step %d is: ", j);
		j++;
		for(i=0; i<n; i++)
		{
			printf("%d ",myArray[i]);
		}
		printf("\n");*/
		lastPos--;
	}
	if (demo)
	{
		// We list the sorted array
		printf("The sorted array using heapSort is: ");
		for (i = 0; i < n; i++)
		{
			printf("%d ", myArray[i]);
		}
		printf("\n");
		printf("The number of Assigns&Comps of the method heapSort is: %d", assCom);
	}
}

/// Quick Sort vs Heap Sort in the Average Case
void QuickSortVSheapSortAvg()
{
	int n, j, AssComAvgCopy;
	int myArray[MAX_SIZE], myArrayCopy[MAX_SIZE];
	for (n = 100; n <= MAX_SIZE; n += INCREMENT)
	{
		assComAvg = 0, AssComAvgCopy = 0;
		for (j = 0; j <= 4; j++)
		{
			FillRandomArray(myArray, n);
			CopyArray(myArrayCopy, myArray, n);
			assCom = 0;
			QuickSort(myArray, 0, n - 1);
			assComAvg += assCom;
			assCom = 0;
			HeapSort(myArrayCopy, n);
			AssComAvgCopy += assCom;
		}
		profiler.countOperation("quickSortAssComAvg", n, assComAvg / 5);
		profiler.countOperation("heapSortAssComAvg", n, AssComAvgCopy / 5);
	}
}

/// Quick Sort for Graphs
void QuickSortForGraphs(int myArray[], int left, int right)
{
	int i, PI, j, aux; // left  --> Left position,  right  --> Right position
	if (left < right)
	{
		assCom += 3;
		aux = myArray[right];
		myArray[right] = myArray[(right - left) / 2 + left];
		myArray[(right - left) / 2 + left] = aux;
		PI = CreatePartition(myArray, left, right); // PI is the PARTITION POSITION
		QuickSortForGraphs(myArray, left, PI - 1);
		QuickSortForGraphs(myArray, PI + 1, right);
	}
}

/// We create the function for the best case using quickSort
void QuickSortBest()
{
	int n, i;
	int myArray[MAX_SIZE];
	for (n = 100; n <= MAX_SIZE; n += INCREMENT)
	{
		for (i = 0; i < n; i++)
		{
			myArray[i] = i;
		}
		assCom = 0;
		QuickSortForGraphs(myArray, 0, n - 1);
		profiler.countOperation("quickSortAssComBest", n, assCom);
	}
}

/// We create the function for the worst case using quickSort
void QuickSortWorst()
{
	int n, i;
	int myArray[MAX_SIZE];
	for (n = 100; n <= MAX_SIZE; n += INCREMENT)
	{
		for (i = 0; i < n; i++)
		{
			myArray[i] = n - 1 - i;
		}
		assCom = 0;
		QuickSortForGraphs(myArray, 0, n - 1);
		profiler.countOperation("quickSortAssComWorst", n, assCom);
	}
}

int main()
{
	/// We give values to our array for the correctness test
	int n = 6, i, quickMin, k;
	int myArray[6];
	/// Quick Sort:
	myArray[0] = 5;
	myArray[1] = 2;
	myArray[2] = 7;
	myArray[3] = 4;
	myArray[4] = 12;
	myArray[5] = 11;
	// We set A&C
	assCom = 0;
	printf("The array before quickSort is: ");
	for (i = 0; i < n; i++) printf("%d ", myArray[i]); printf("\n");
	printf("We sort the array using quickSort...\n");
	QuickSort(myArray, 0, n - 1);
	printf("The array sorted using quickSort is: ");
	for (i = 0; i < n; i++) printf("%d ", myArray[i]); printf("\n");
	printf("The number of Assigns&Comps of the method quickSort is: %d\n", assCom);
	/// Quick Select:
	myArray[0] = 5;
	myArray[1] = 2;
	myArray[2] = 7;
	myArray[3] = 4;
	myArray[4] = 12;
	myArray[5] = 11;
	// We set A&C
	assCom = 0;
	printf("\nThe array in which we select the k-th minimum with quickSelect is: ");
	for (i = 0; i < n; i++) printf("%d ", myArray[i]); printf("\n");
	printf("Choose the k-th smallest element you want to get with quickSort.\n");
	printf("k = ");
	scanf("%d", &k);
	printf("Searching for the element using quickSort...\n");
	quickMin = QuickSelect(myArray, 0, n - 1, k);
	printf("The %d-th smallest element is: %d\n", k, quickMin);
	printf("The number of Assigns&Comps of the method quickSort is: %d\n", assCom);
	/// Heap Sort:
	myArray[0] = 5;
	myArray[1] = 2;
	myArray[2] = 7;
	myArray[3] = 4;
	myArray[4] = 12;
	myArray[5] = 11;
	// We set A&C
	assCom = 0;
	HeapSort(myArray, n);
	// We get out of the testing mode
	demo = false;
	printf("\n\nNow generating the graphs file, this might take a while...\nAlso, you can find an already generated graph file in the folder.\n");
	/// We create the graphs
	QuickSortVSheapSortAvg();
	QuickSortBest();
	QuickSortWorst();
	/// We group the graph for the comparisons
	profiler.createGroup("AVG quickSort VS heapSort", "quickSortAssComAvg", "heapSortAssComAvg");
	// We create the file with the graphs
	profiler.showReport();
	printf("\nDemo is printed above. Graphs file was generated.\n");
	getchar();
	system("pause"); // Working only on Windows !
	return 0;
}
