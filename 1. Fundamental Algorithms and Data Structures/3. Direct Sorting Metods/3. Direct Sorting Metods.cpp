#include "Profiler.h"

#include <stdio.h>
#include <stdlib.h>

constexpr auto MAX_SIZE = 10000;
constexpr auto INCREMENT = 100;

Profiler profiler("DirectSortingMethods_Graphs");

// We globally declare our variables for Assignments and Comparisons
int assigns, comps, assignsAvg, compsAvg;
// Set demo for showing the correctness of the algorithms
bool demo = true;

/// Insertion Sort
void InsertionSort(int myArray[], int n)
{
	int i, j, buff;
	if (demo)
	{
		// Display the unsorted array
		printf("The array before Insertion Sort is: ");
		for (i = 0; i < n; i++)
		{
			printf("%d ", myArray[i]);
		}
		printf("\n");
	}
	// Set the number of Assigns&Comps
	assigns = 0;
	comps = 0;
	// Sort the array using Insertion Sort, also calculating the number of Assigns&Comps
	if (demo)
	{
		printf("Sorting the array using Insertion Sort...\n");
	}
	for (i = 1; i < n; i++)
	{
		buff = myArray[i];
		assigns++;
		j = i - 1;
		while (j >= 0 && myArray[j] > buff)
		{
			comps++;
			myArray[j + 1] = myArray[j];
			assigns++;
			j = j - 1;
		}
		comps++;
		myArray[j + 1] = buff;
		assigns++;
	}
	assignsAvg += assigns;
	compsAvg += comps;
	if (demo)
	{
		// Display the sorted array
		printf("The array sorted with the Insertion Sort method is: ");
		for (i = 0; i < n; i++)
		{
			printf("%d ", myArray[i]);
		}
		printf("\n");
		printf("The number of Assignations of the Insertion Sort method is: %d\n", assigns);
		printf("The number of Comparisons of the Insertion Sort method is: %d\n\n", comps);
	}
}

/// Selection Sort
void SelectionSort(int myArray[], int n)
{
	int i, j, poz_min, buff;
	if (demo)
	{
		// Display the unsorted array
		printf("The array before Selection Sort is: ");
		for (i = 0; i < n; i++)
		{
			printf("%d ", myArray[i]);
		}
		printf("\n");
	}
	// Set the number of Assigns&Comps
	assigns = 0;
	comps = 0;
	// Sort the array using Selection Sort, also calculating the number of Assigns&Comps
	if (demo)
	{
		printf("Sorting the array using Selection Sort...\n");
	}
	for (i = 0; i < n - 1; i++)
	{
		poz_min = i;
		for (j = i + 1; j < n; j++)
		{
			comps++;
			if (myArray[j] < myArray[poz_min])
			{
				poz_min = j;
			}
		}
		buff = myArray[i];
		myArray[i] = myArray[poz_min];
		myArray[poz_min] = buff;
		assigns += 3;
	}
	assignsAvg += assigns;
	compsAvg += comps;
	if (demo)
	{
		// Display the sorted array
		printf("The array sorted with the Selection Sort method is: ");
		for (i = 0; i < n; i++)
		{
			printf("%d ", myArray[i]);
		}
		printf("\n");
		printf("The number of Assignations of the Selection Sort method is: %d\n", assigns);
		printf("The number of Comparisons of the Selection Sort method is: %d\n\n", comps);
	}
}

/// Bubble Sort
void bubbleSort(int myArray[], int n)
{
	int i, j, buff;
	if (demo)
	{
		// Display the unsorted array
		printf("The array before Bubble Sort is: ");
		for (i = 0; i < n; i++)
		{
			printf("%d ", myArray[i]);
		}
		printf("\n");
	}
	// Set the number of Assigns&Comps
	assigns = 0;
	comps = 0;
	// Sort the array using Bubble Sort, also calculating the number of Assigns&Comps
	for (i = 0; i < n - 1; i++)
	{
		for (j = 0; j < n - 1 - i; j++)
		{
			comps++;
			if (myArray[j] > myArray[j + 1])
			{
				buff = myArray[j];
				myArray[j] = myArray[j + 1];
				myArray[j + 1] = buff;
				assigns += 3;
			}
		}
	}
	assignsAvg += assigns;
	compsAvg += comps;
	if (demo)
	{
		// Display the sorted array
		printf("The array sorted with the Bubble Sort method is: ");
		for (i = 0; i < n; i++)
		{
			printf("%d ", myArray[i]);
		}
		printf("\n");
		printf("The number of Assignations of the Bubble Sort method is: %d\n", assigns);
		printf("The number of Comparisons of the Bubble Sort method is: %d\n\n", comps);
	}
}

/// First we need a Binary Search function for Binary Search Insertion
int BinarySearch(int myArray[], int element, int low, int high, int& comps)
{
	comps++;
	if (high <= low)
		return (element > myArray[low]) ? (low + 1) : low;
	// Set the middle
	int mid = (low + high) / 2;
	comps++;
	if (element == myArray[mid])
		return mid + 1;
	// Recall function if no return took place already to continue searching for the right place
	comps++;
	if (element > myArray[mid])
		return BinarySearch(myArray, element, mid + 1, high, comps);
	return BinarySearch(myArray, element, low, mid - 1, comps);
}

/// Binary Insertion Sort
void BinaryInsertionSort(int myArray[], int n)
{
	int i, j, buff, place;
	if (demo)
	{
		// Display the unsorted array
		printf("The array before Binart Insertion Sort is: ");
		for (i = 0; i < n; i++)
		{
			printf("%d ", myArray[i]);
		}
		printf("\n");
	}
	// Set the number of Assigns&Comps
	assigns = 0;
	comps = 0;
	//Sort the array using Binary Insertion Sort, also calculating the number of Assigns&Comps
	if (demo)
	{
		printf("Sorting the array using Binary Insertion Sort...\n");
	}
	for (i = 1; i < n; i++)
	{
		buff = myArray[i];
		assigns++;
		j = i - 1;
		// Now we use Binary Search function to find the place where we should insert the buff
		place = BinarySearch(myArray, buff, 0, j, comps);
		// We move the elements to create space
		while (j >= place)
		{
			myArray[j + 1] = myArray[j];
			assigns++;
			j = j - 1;
		}
		myArray[j + 1] = buff;
		assigns++;
	}
	assignsAvg += assigns;
	compsAvg += comps;
	if (demo)
	{
		// Display the sorted array
		printf("The array sorted with the Binary Insertion Sort method is: ");
		for (i = 0; i < n; i++)
		{
			printf("%d ", myArray[i]);
		}
		printf("\n");
		printf("The number of Assignations of the Binary Insertion Sort method is: %d\n", assigns);
		printf("The number of Comparisons of the Binary Insertion Sort method is: %d\n", comps);
	}
}

/// We create the function for the best case using insertion
void InsertionBestCase(int n)
{
	int myArray[MAX_SIZE];
	for (n = 100; n <= MAX_SIZE; n += INCREMENT)
	{
		for (int i = 0; i < n; i++)
		{
			myArray[i] = i;
		}
		InsertionSort(myArray, n);
		profiler.countOperation("InsertionAssignmentsBest", n, assigns);
		profiler.countOperation("InsertionComparisonsBest", n, comps);
	}
}

/// We create the function for the worst case using insertion
void InsertionWorstCase(int n)
{
	int myArray[MAX_SIZE];
	for (n = 100; n <= MAX_SIZE; n += INCREMENT)
	{
		for (int i = 0; i < n; i++)
		{
			myArray[i] = n - i;
		}
		InsertionSort(myArray, n);
		profiler.countOperation("InsertionAssignmentsWorst", n, assigns);
		profiler.countOperation("InsertionComparisonsWorst", n, comps);
	}
}

/// We create the function for the average case using insertion
void InsertionAverageCase(int n)
{
	int j;
	for (n = 100; n <= MAX_SIZE; n += INCREMENT)
	{
		int myArray[MAX_SIZE];
		assignsAvg = 0;
		compsAvg = 0;
		for (j = 0; j <= 4; j++)
		{
			FillRandomArray(myArray, n);
			InsertionSort(myArray, n);
			profiler.countOperation("InsertionAssignmentsAverage", n, assignsAvg / 5);
			profiler.countOperation("InsertionComparisonsAverage", n, compsAvg / 5);
		}
	}
}

/// We create the function for the best case using selection
void SelectionBestCase(int n)
{
	int myArray[MAX_SIZE];
	for (n = 100; n <= MAX_SIZE; n += INCREMENT)
	{
		for (int i = 0; i < n; i++)
		{
			myArray[i] = i;
		}
		SelectionSort(myArray, n);
		profiler.countOperation("SelectionAssignmentsBest", n, assigns);
		profiler.countOperation("SelectionComparisonsBest", n, comps);
	}
}

/// We create the function for the worst case using selection
void SelectionWorstCase(int n)
{
	int myArray[MAX_SIZE];
	for (n = 100; n <= MAX_SIZE; n += INCREMENT)
	{
		for (int i = 0; i < n; i++)
		{
			myArray[i] = n - i;
		}
		SelectionSort(myArray, n);
		profiler.countOperation("SelectionAssignmentsWorst", n, assigns);
		profiler.countOperation("SelectionComparisonsWorst", n, comps);
	}
}

/// We create the function for the average case using selection
void SelectionAverageCase(int n)
{
	int j;
	int myArray[MAX_SIZE];
	for (n = 100; n <= MAX_SIZE; n += INCREMENT)
	{
		assignsAvg = 0;
		compsAvg = 0;
		for (j = 0; j <= 4; j++)
		{
			FillRandomArray(myArray, n);
			SelectionSort(myArray, n);
			profiler.countOperation("SelectionAssignmentsAverage", n, assignsAvg / 5);
			profiler.countOperation("SelectionComparisonsAverage", n, compsAvg / 5);
		}
	}
}

/// We create the function for the best case using bubble
void BubbleBestCase(int n)
{
	int myArray[MAX_SIZE];
	for (n = 100; n <= MAX_SIZE; n += INCREMENT)
	{
		for (int i = 0; i < n; i++)
		{
			myArray[i] = i;
		}
		bubbleSort(myArray, n);
		profiler.countOperation("BubbleAssignmentsBest", n, assigns);
		profiler.countOperation("BubbleComparisonsBest", n, comps);
	}
}

/// We create the function for the worst case using bubble
void BubbleWorstCase(int n)
{
	int myArray[MAX_SIZE];
	for (n = 100; n <= MAX_SIZE; n += INCREMENT)
	{
		for (int i = 0; i < n; i++)
		{
			myArray[i] = n - i;
		}
		bubbleSort(myArray, n);
		profiler.countOperation("BubbleAssignmentsWorst", n, assigns);
		profiler.countOperation("BubbleComparisonsWorst", n, comps);
	}
}

/// We create the function for the average case using bubble
void BubbleAverageCase(int n)
{
	int j;
	int myArray[MAX_SIZE];
	for (n = 100; n <= MAX_SIZE; n += INCREMENT)
	{
		assignsAvg = 0;
		compsAvg = 0;
		for (j = 0; j <= 4; j++)
		{
			FillRandomArray(myArray, n);
			bubbleSort(myArray, n);
			profiler.countOperation("BubbleAssignmentsAverage", n, assignsAvg / 5);
			profiler.countOperation("BubbleComparisonsAverage", n, compsAvg / 5);
		}
	}
}

/// We create the function for the best case using binary Insertion
void BinaryInsertionBestCase(int n)
{
	int myArray[MAX_SIZE];
	for (n = 100; n <= MAX_SIZE; n += INCREMENT)
	{
		for (int i = 0; i < n; i++)
		{
			myArray[i] = i;
		}
		BinaryInsertionSort(myArray, n);
		profiler.countOperation("BinaryInsertionAssignmentsBest", n, assigns);
		profiler.countOperation("BinaryInsertionComparisonsBest", n, comps);
	}
}

/// We create the function for the worst case using binary Insertion
void BinaryInsertionWorstCase(int n)
{
	int myArray[MAX_SIZE];
	for (n = 100; n <= MAX_SIZE; n += INCREMENT)
	{
		for (int i = 0; i < n; i++)
		{
			myArray[i] = n - i;
		}
		BinaryInsertionSort(myArray, n);
		profiler.countOperation("BinaryInsertionAssignmentsWorst", n, assigns);
		profiler.countOperation("BinaryInsertionComparisonsWorst", n, comps);
	}
}

/// We create the function for the average case using binary Insertion
void BinaryInsertionAverageCase(int n)
{
	int j;
	int myArray[MAX_SIZE];
	for (n = 100; n <= MAX_SIZE; n += INCREMENT)
	{
		assignsAvg = 0;
		compsAvg = 0;
		for (j = 0; j <= 4; j++)
		{
			FillRandomArray(myArray, n);
			BinaryInsertionSort(myArray, n);
			profiler.countOperation("BinaryInsertionAssignmentsAverage", n, assignsAvg / 5);
			profiler.countOperation("BinaryInsertionComparisonsAverage", n, compsAvg / 5);
		}
	}
}

int main()
{
	/// Values for the correctness test of the 4 methods.
	int n = 6;
	int myArray[6];
	// Insertion:
	myArray[0] = 5;
	myArray[1] = 2;
	myArray[2] = 7;
	myArray[3] = 4;
	myArray[4] = 12;
	myArray[5] = 11;
	InsertionSort(myArray, n);
	// Selection:
	myArray[0] = 5;
	myArray[1] = 2;
	myArray[2] = 7;
	myArray[3] = 4;
	myArray[4] = 12;
	myArray[5] = 11;
	SelectionSort(myArray, n);
	// Bubble:
	myArray[0] = 5;
	myArray[1] = 2;
	myArray[2] = 7;
	myArray[3] = 4;
	myArray[4] = 12;
	myArray[5] = 11;
	bubbleSort(myArray, n);
	// Binary Insertion:
	myArray[0] = 5;
	myArray[1] = 2;
	myArray[2] = 7;
	myArray[3] = 4;
	myArray[4] = 12;
	myArray[5] = 11;
	BinaryInsertionSort(myArray, n);
	// Get out of the testing mode
	demo = false;
	printf("\nNow generating the graphs file, this might take a while...\nAlso, you can find an already generated graph file in the folder.\n");
	/// Create the 4 graphs for each sorting method
	// Insertion
	InsertionBestCase(n);
	InsertionWorstCase(n);
	InsertionAverageCase(n);
	// Selection:
	SelectionBestCase(n);
	SelectionWorstCase(n);
	SelectionAverageCase(n);
	// Bubble:
	BubbleBestCase(n);
	BubbleWorstCase(n);
	BubbleAverageCase(n);
	// Binary Insertion:
	BinaryInsertionBestCase(n);
	BinaryInsertionWorstCase(n);
	BinaryInsertionAverageCase(n);
	/// Group the graphs 3 by 3 with the help of the profiler
	// Insertion:
	profiler.addSeries("InsertionAssigns&CompsBest", "InsertionAssignmentsBest", "InsertionComparisonsBest");
	profiler.createGroup("Insertion Best Case", "InsertionAssignmentsBest", "InsertionComparisonsBest", "InsertionAssigns&CompsBest");
	profiler.addSeries("InsertionAssigns&CompsWorst", "InsertionAssignmentsWorst", "InsertionComparisonsWorst");
	profiler.createGroup("Insertion Worst Case", "InsertionAssignmentsWorst", "InsertionComparisonsWorst", "InsertionAssigns&CompsWorst");
	profiler.addSeries("InsertionAssigns&CompsAverage", "InsertionAssignmentsAverage", "InsertionComparisonsAverage");
	profiler.createGroup("Insertion Average Case", "InsertionAssignmentsAverage", "InsertionComparisonsAverage", "InsertionAssigns&CompsAverage");
	// Selection:
	profiler.addSeries("SelectionAssigns&CompsBest", "SelectionAssignmentsBest", "SelectionComparisonsBest");
	profiler.createGroup("Selection Best Case", "SelectionAssignmentsBest", "SelectionComparisonsBest", "SelectionAssigns&CompsBest");
	profiler.addSeries("SelectionAssigns&CompsWorst", "SelectionAssignmentsWorst", "SelectionComparisonsWorst");
	profiler.createGroup("Selection Worst Case", "SelectionAssignmentsWorst", "SelectionComparisonsWorst", "SelectionAssigns&CompsWorst");
	profiler.addSeries("SelectionAssigns&CompsAverage", "SelectionAssignmentsAverage", "SelectionComparisonsAverage");
	profiler.createGroup("Selection Average Case", "SelectionAssignmentsAverage", "SelectionComparisonsAverage", "SelectionAssigns&CompsAverage");
	// Bubble:
	profiler.addSeries("BubbleAssigns&CompsBest", "BubbleAssignmentsBest", "BubbleComparisonsBest");
	profiler.createGroup("Bubble Best Case", "BubbleAssignmentsBest", "BubbleComparisonsBest", "BubbleAssigns&CompsBest");
	profiler.addSeries("BubbleAssigns&CompsWorst", "BubbleAssignmentsWorst", "BubbleComparisonsWorst");
	profiler.createGroup("Bubble Worst Case", "BubbleAssignmentsWorst", "BubbleComparisonsWorst", "BubbleAssigns&CompsWorst");
	profiler.addSeries("BubbleAssigns&CompsAverage", "BubbleAssignmentsAverage", "BubbleComparisonsAverage");
	profiler.createGroup("Bubble Average Case", "BubbleAssignmentsAverage", "BubbleComparisonsAverage", "BubbleAssigns&CompsAverage");
	// BinaryInsertion
	profiler.addSeries("BinaryInsertionAssigns&CompsBest", "BinaryInsertionAssignmentsBest", "BinaryInsertionComparisonsBest");
	profiler.createGroup("BinaryInsertion Best Case", "BinaryInsertionAssignmentsBest", "BinaryInsertionComparisonsBest", "BinaryInsertionAssigns&CompsBest");
	profiler.addSeries("BinaryInsertionAssigns&CompsWorst", "BinaryInsertionAssignmentsWorst", "BinaryInsertionComparisonsWorst");
	profiler.createGroup("BinaryInsertion Worst Case", "BinaryInsertionAssignmentsWorst", "BinaryInsertionComparisonsWorst", "BinaryInsertionAssigns&CompsWorst");
	profiler.addSeries("BinaryInsertionAssigns&CompsAverage", "BinaryInsertionAssignmentsAverage", "BinaryInsertionComparisonsAverage");
	profiler.createGroup("BinaryInsertion Average Case", "BinaryInsertionAssignmentsAverage", "BinaryInsertionComparisonsAverage", "BinaryInsertionAssigns&CompsAverage");
	/// Create the graphs for the 3 methods comparison
	// Assignations for these 3:
	profiler.createGroup("AllAssignments Best Case", "InsertionAssignmentsBest", "SelectionAssignmentsBest", "BubbleAssignmentsBest");
	// Comparisons for these 3:
	profiler.createGroup("AllComparisons Worst Case", "InsertionComparisonsWorst", "SelectionComparisonsWorst", "BubbleComparisonsWorst");
	// Assignments&Comparisons for these 3:
	profiler.createGroup("AllAssigns&Comps Average Case", "InsertionAssigns&CompsAverage", "SelectionAssigns&CompsAverage", "BubbleAssigns&CompsAverage");
	/// Display the graphs with the help of the profiler
	profiler.showReport();
	//system("pause"); Working only on Windows! Solution for Linux & Windows:
	printf("\nDemo is printed above. Graphs file was generated.\nPRESS ENTER TO EXIT...");
	getchar();
	return 0;
}
