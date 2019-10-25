#include "Profiler.h"

#include <stdio.h>
#include <stdlib.h>

#define SPACE 10 //Space for nice printing of Binary Search Trees

Profiler profiler("DynamicOrderStatistics");

//We globally declare our variables for the number of Operations
int operations = 0, operationsAvg = 0;
char demoChar[4];

//We declare our node structure
typedef struct Node
{
	int key;
	int sizE;
	struct Node* left;
	struct Node* right;
}NodeT;

//Node Initialization
NodeT* CreateEmptyNode()
{
	NodeT* node = (NodeT*)malloc(sizeof(NodeT));
	if (node)
	{
		node->key = 0;
		node->sizE = 0;
		node->left = NULL;
		node->right = NULL;
		return node;
	}
	else return NULL;
}

///Function for calculating the size of a node
int GetSize(NodeT* node, int hl, int hr)
{
	if (node == NULL) return 0;
	hl = GetSize(node->left, hl, hr) + 1;
	hr = GetSize(node->right, hl, hr) + 1;
	return hl + hr - 1;
}

///Function for calculating the size for each node
int GetSizes(NodeT* root)
{
	if (root == NULL) return 0;
	root->sizE = GetSize(root, 0, 0);
	GetSizes(root->left);
	GetSizes(root->right);
}

///Function for creating the BST
NodeT* BuildPerfBalBST(int left, int right)
{
	if (left <= right)
	{
		int middle;
		middle = (left + right) / 2;
		NodeT* root;
		root = CreateEmptyNode();
		root->key = middle;
		root->left = BuildPerfBalBST(left, middle - 1);
		root->right = BuildPerfBalBST(middle + 1, right);
		return root;
	}
	else return NULL;
}

///Function for selecting from a BST
NodeT* OS_Select(NodeT* root, int i)
{
	int r = 1;
	if (root->left != NULL) { r += root->left->sizE; operations++; }
	if (i == r)
	{
		return root;
	}
	else if (i < r) return OS_Select(root->left, i);
	else return OS_Select(root->right, i - r);
}

///Function for os_deleting from the BST
NodeT* OS_Delete(NodeT* root, int key)
{
	if (root == NULL) return root;
	root->sizE--;
	// If the key is less than our node then go on left
	operations++;
	if (key < root->key) root->left = OS_Delete(root->left, key);
	// Else if the key is bigger than our node then go on right
	else if (key > root->key) { operations++; root->right = OS_Delete(root->right, key); }
	// Else, we are on the node that needs to get deleted
	else
	{
		// If it is a node with only one child or no child
		if (root->left == NULL)
		{
			NodeT* aux = CreateEmptyNode();
			aux = root->right;
			free(root);
			root = NULL;
			return aux;
		}
		else if (root->right == NULL)
		{
			NodeT* aux = CreateEmptyNode();
			aux = root->left;
			free(root);
			root = NULL;
			return aux;
		}
		// Node with two children
		NodeT* aux;
		aux = CreateEmptyNode();
		aux = root->right;
		while (aux->left != NULL) aux = aux->left;
		// Copy the in_order successor's content to this root
		root->key = aux->key;
		// Delete the in order successor
		root->right = OS_Delete(root->right, aux->key);
	}
	return root;
}

///Function for printing the BST
void PrintBST(NodeT* root, int space)
{
	if (root != NULL)
	{
		int i, j;
		space += SPACE;
		PrintBST(root->right, space);
		printf("\n");
		for (i = SPACE; i < space; i++) printf(" ");
		printf("(%d,%d)\n", root->key, root->sizE);
		PrintBST(root->left, space);
	}
	else return;
}

///Function for showing Demo
void Demo()
{
	// Declare our size for demo
	int treeSize, nrOfElementsToBeDeleted;
	printf("Input the number of elements which you want to be in the tree: ");
	scanf("%d", &treeSize);
	printf("Input the number of elements that you want to delete from the tree: ");
	scanf("%d", &nrOfElementsToBeDeleted);
	printf("\n");
	// We create our root which is the tree and our node to use in other functions
	NodeT* root, * node;
	node = CreateEmptyNode();
	root = CreateEmptyNode();
	// Create the three with the root being root
	root = BuildPerfBalBST(1, treeSize);
	// Fill each node with its size
	GetSizes(root);
	// Print the tree
	printf("The PerfBalBST is:(Rotate your head 90 degrees on the left because that is the root node.)");
	PrintBST(root, SPACE);
	// Demo for 3 elements:
	int i, pos;
	for (i = 0; i < nrOfElementsToBeDeleted; i++)
	{
		pos = rand() % treeSize + 1;
		node = OS_Select(root, pos);
		printf("The %d(-th) smallest element is: (%d,%d)\n", pos, node->key, node->sizE);
		root = OS_Delete(root, node->key);
		treeSize--;
		printf("The tree without that elements is: ");
		PrintBST(root, SPACE);
		if (treeSize == 0) {
			printf("\nEMPTY!");
			exit(-1);
		}
	}
}

///Functions for evaluations
void NotDemo()
{
	printf("\nNow generating the graphs file, this might take a while...\nAlso, you can find an already generated graph file in the folder.\n");
	int n, i, j, pos, treeSize;
	NodeT* root, * aux;
	aux = CreateEmptyNode();
	for (n = 100; n <= 10000; n += 100)
	{
		operationsAvg = 0;
		for (i = 0; i < 5; i++)
		{
			operations = 0;
			treeSize = n;
			root = CreateEmptyNode();
			root = BuildPerfBalBST(1, treeSize);
			GetSizes(root);
			for (j = 0; j < n - 1; j++)
			{
				pos = rand() % treeSize + 1;
				aux = OS_Select(root, pos);
				root = OS_Delete(root, aux->key);
				treeSize--;
			}
			operationsAvg += operations;
		}
		operationsAvg /= 5;
		profiler.countOperation("Operations", n, operationsAvg);
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
