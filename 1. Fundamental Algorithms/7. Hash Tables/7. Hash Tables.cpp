#include "Profiler.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define c1 1
#define c2 2

//We globally declare our variables for the number of Operations
float operations = 0, maxOperations = 0;
//We globally declare our demo variable
bool demo = true;

///Definition of a HashTable and an Element
typedef struct Element
{
	int id;
	char name[30];
} ElementT;

///HashFunction
int HashFunction(int id, int i, int hashTableSize)
{
	return (id + c1 * i + c2 * i * i) % hashTableSize;
}

///HashTable Print
void HashTablePrint(ElementT* hashTable, int hashTableSize)
{
	int i;
	printf("The hashTable is: \n");
	for (i = 0; i < hashTableSize; i++) printf("%d: %s %d\n", i, hashTable[i].name, hashTable[i].id);
}

///HashTable Initialization
void HashTableGeneration(ElementT* hashTable, ElementT* k, int hashTableSize, float fillingFactor)
{
	int i;
	int* a = (int*)malloc(hashTableSize * sizeof(int));
	int omg = floor(hashTableSize * fillingFactor);
	if (demo) FillRandomArray(a, omg, 2 * hashTableSize, 3 * hashTableSize - 1, true);
	else FillRandomArray(a, omg, 2 * hashTableSize, 3 * hashTableSize - 1);
	for (i = 0; i < floor(hashTableSize * fillingFactor); i++)
	{
		k[i].id = a[i];
		if (i % 3 == 0) strcpy(k[i].name, "ana");
		else if (i % 3 == 1) strcpy(k[i].name, "casa");
		else strcpy(k[i].name, "mar");
		if (i % 5 == 0) strcpy(k[i].name, "banana");
		if (i % 6 == 0) strcpy(k[i].name, "piatra");
		if (i % 7 == 0) strcpy(k[i].name, "energie");
		if (i == 0) strcpy(k[i].name, "ana");
		if (demo) printf("#%d %s having the id %d has been created\n", i, k[i].name, k[i].id);
	}
	for (i = 0; i < hashTableSize; i++)
	{
		strcpy(hashTable[i].name, "NULL");
		hashTable[i].id = 0;
	}
	if (demo) printf("\n");
}

///HashTable Insert
int HashTableInsert(ElementT* hashTable, ElementT k, int hashTableSize, int l, float fillingFactor)
{
	int i = 0, j;
	do
	{
		j = HashFunction(k.id, i, hashTableSize);
		if (strcmp(hashTable[j].name, "NULL") == 0)
		{
			strcpy(hashTable[j].name, k.name);
			hashTable[j].id = k.id;
			if (demo) printf("#%d %s having the id %d has been introduced in the position %d\n", l, hashTable[j].name, hashTable[j].id, j);
			return j;
		}
		else i++;
	} while (i < floor(hashTableSize * fillingFactor)); // while(i < hashTableSize || strcmp(hashTable[j].name, "NULL") != 0);
	return -1;
}

///HashTable Search
int HashTableSearch(ElementT* hashTable, int hashTableSize, int id, float fillingFactor)
{
	int i = 0, j;
	do
	{
		maxOperations++;
		operations++;
		j = HashFunction(id, i, hashTableSize);
		if (hashTable[j].id == id)
		{
			return j;
		}
		else i++;
	} while (i < floor(hashTableSize * fillingFactor) && strcmp(hashTable[j].name, "NULL") != 0); // (i < hashTableSize || hashTable[j].id != id );
	return -1;
}

///HashTable Demo
void HashTableDemo()
{
	//Declare our variables
	int i, j, id, l = 0;
	int hashTableSize = 0;
	float fillingFactor = 0;
	//Define HastTableSize
	printf("Input the desired hashTableSize for demo: ");
	scanf("%d", &hashTableSize);
	//Define our filling factor
	printf("Input the desired fillingFactor(between 0 and 1): ");
	scanf("%f", &fillingFactor);
	printf("\n");
	//Define our HastTable
	ElementT* k = (ElementT*)malloc(hashTableSize * sizeof(ElementT));
	ElementT* hashTable = (ElementT*)malloc(hashTableSize * sizeof(ElementT));
	//Generate the HashTable
	HashTableGeneration(hashTable, k, hashTableSize, fillingFactor);
	//Insertion Demo
	for (i = 0; i < floor(hashTableSize * fillingFactor); i++) { HashTableInsert(hashTable, k[i], hashTableSize, l, fillingFactor); l++; } printf("\n");
	HashTablePrint(hashTable, hashTableSize);
	//Searching Demo
	printf("\nInput the ID that you want to search for: ");
	scanf("%d", &id);
	j = HashTableSearch(hashTable, hashTableSize, id, fillingFactor);
	if (j != -1) printf("The element with the ID equal to %d is placed on position %d\n", id, j);
	else printf("The element with the ID equal to %d IS NOT in OUR hashTable\n", id);
}

///Create Table With Values
void HashTableCreateTable()
{
	printf("\nGenerating the table with the evaluation of 'serach' operation. You cand read about it in the README. This might take a while...");
	//Declare our variables
	int i, j, id, l = 0, m, n, search1[1500], search2[1500];
	int hashTableSize = 10007;
	float fillingFactor[] = { 0.800000000, 0.850000000, 0.900000000, 0.950000000, 0.99000000000 };
	float avgEffortFound[5], avgEffortNOTFound[5], maxEffortFound[5], maxEffortNOTFound[5];
	//Define our HastTable
	ElementT* k = (ElementT*)malloc(hashTableSize * sizeof(ElementT));
	ElementT* hashTable = (ElementT*)malloc(hashTableSize * sizeof(ElementT));
	//Insertion Dfor each filling factor
	for (m = 0; m < 5; m++)
	{
		int maxOpFound = 0, maxOpNOTFound = 0;
		int omg = floor(hashTableSize * fillingFactor[m]);
		//Generate the HashTable
		HashTableGeneration(hashTable, k, hashTableSize, fillingFactor[m]);
		for (i = 0; i < floor(hashTableSize * fillingFactor[m]); i++) { HashTableInsert(hashTable, k[i], hashTableSize, l, fillingFactor[m]); l++; }
		FillRandomArray(search1, 1500, 2 * hashTableSize, 3 * hashTableSize - 1);
		FillRandomArray(search2, 1500, 3 * hashTableSize, 4 * hashTableSize - 1, true);
		//Search for elements that are in the table
		operations = 0;
		for (n = 0; n < 1500; n++)
		{
			maxOperations = 0;
			j = HashTableSearch(hashTable, hashTableSize, search1[n], fillingFactor[m]);
			if (maxOperations > maxOpFound) maxOpFound = maxOperations;
		}
		avgEffortFound[m] = operations / 1500;
		maxEffortFound[m] = maxOpFound;
		//Search for elements that are not in the table
		operations = 0;
		for (n = 0; n < 1500; n++)
		{
			maxOperations = 0;
			j = HashTableSearch(hashTable, hashTableSize, search2[n], fillingFactor[m]);
			if (maxOperations > maxOpNOTFound) maxOpNOTFound = maxOperations;
		}
		avgEffortNOTFound[m] = operations / 1500;
		maxEffortNOTFound[m] = maxOpNOTFound;
	}
	printf("\n%s\t%s\t%s\t%s %s\n", "Filling factor", "AvgEffortFound", "MaxEffortFound", "AvgEffortNOTFound", "MaxEffortNOTFound");
	for (m = 0; m < 5; m++)
	{
		printf("%f\t%f\t%f\t%f\t  %f\n", fillingFactor[m], avgEffortFound[m], maxEffortFound[m], avgEffortNOTFound[m], maxEffortNOTFound[m]);
	}
}

int main()
{
	HashTableDemo();
	demo = false;
	HashTableCreateTable();
	//system("pause"); Working only on Windows! Solution for Linux & Windows:
	printf("\nDemo is printed above.\nPRESS ENTER TO EXIT\n");
	getchar();
	getchar();
	return 0;
}
