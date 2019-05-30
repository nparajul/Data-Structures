#include<iostream>

using namespace std;

struct node 
{
	int source;
	int dest;
	int weight;		
	node* left;
	node* right;
};

class Graph
{
public:
	//variable that stores the respective graph- input
	int source;
	int dest;
	int weight;
};

class BSTminTop
{
public:
	node *createnode(int source, int destination, int weight);					//creates a new node
	node *push(node *root, int source, int destination, int weight);			//inserts a new node
	void swap(node *x, node *y);												//swaps two nodes
	void arrange(node *root);													// converts the BST to a min heap
	void minTop(node *root);													// puts the minimum value as the parent
	node* delete_node(node* root, int tdata);									// deletes a node from the heap
	node* FindMin(node *root);													//finds the minimum value from the right after deleting a node 
	void kruskals(node* root, int n);											// implements the kruskal's algorithm
	void store_output(int n, node* root, int* cycle_check, Graph* MST);			// stores the MST grpah inputs in an array
};

node *BSTminTop::createnode(int source, int destination, int weight)
{
	node *newnode = new node;
	newnode->source = source;
	newnode->dest = destination;
	newnode->weight = weight;
	newnode->left = NULL;
	newnode->right = NULL;

	return newnode;
}

node *BSTminTop::push(node *root, int source, int destination, int weight)
{
	if (root == NULL)
	{
		root = createnode(source, destination, weight);
	}

	else if (weight <= root->weight)
	{
		root->left = push(root->left, source,destination,weight);
	}
	else
	{
		root->right = push(root->right, source,destination,weight);
	}
	arrange(root);
	return root;
}

node* BSTminTop::delete_node(node* root, int tdata)
{
	if (root != NULL)
	{

		if (root->weight < tdata)
		{
			root->right = delete_node(root->right, tdata);
		}

		else if (root->weight > tdata)
		{
			root->left = delete_node(root->left, tdata);
		}

		else
		{

			if (root->left == NULL && root->right == NULL)
			{
				delete root;
				root = NULL;

			}

			else if (root->left == NULL)
			{
				node *temp = root;
				root = root->right;
				delete temp;
			}

			else if (root->right == NULL)
			{
				node *temp = root;
				root = root->left;
				delete temp;
			}

			else
			{
				node *temp = FindMin(root->right);
				root->weight = temp->weight;
				root->dest = temp->dest;
				root->source = temp->source;
				root->right = delete_node(root->right, temp->weight);
			}

		}
	}
	arrange(root);
	return root;

}

node* BSTminTop::FindMin(node *root)
{
	if (root != NULL)
	{
		if (root->left == NULL)
		{
			return root;
		}

		else
		{
			return FindMin(root->left);
		}
	}
}

void BSTminTop::arrange(node* root)
{
	if (root != NULL)
	{
		arrange(root->left);
		arrange(root->right);
		minTop(root);
	}
}

void BSTminTop::minTop(node* root)
{
	node *min = root;
	node *rootLeft = root->left;
	node *rootRight = root->right;

	if (root->left != NULL && rootLeft->weight < root->weight)
	{
		min = rootLeft;
	}

	if (root->right != NULL && rootRight->weight < root->weight)
	{
		min = rootRight;
	}

	if (root != min)
	{
		swap(min, root);
		minTop(min);
	}
}

void BSTminTop::swap(node *x, node *y)
{
	int temp_source = x->source;
	int temp_dest = x->dest;
	int temp_weight = x->weight;

	x->source = y->source;
	x->dest = y->dest;
	x->weight = y->weight;

	y->source = temp_source;
	y->dest = temp_dest;
	y->weight = temp_weight;
}

int findNeighbor(int n, int* cycle_check)
{
	if (cycle_check[n] == n)
	{
		return n;
	}

	return findNeighbor(cycle_check[n], cycle_check);
}

void BSTminTop::kruskals(node* root, int vertices) 
{
	
	Graph* MST = new Graph[vertices-1];						//stores the MST output which has n-1 edges
	int *cycle_check = new int[vertices];

	for (int i = 0; i < vertices; i++)
	{
		cycle_check[i] = i;
	}
		
	store_output(vertices,root, cycle_check, MST);
	
	for (int i = 0; i < vertices - 1; i++)
	{		
			cout << MST[i].source << " " << MST[i].dest << " " << MST[i].weight<<endl;
	}
}

void BSTminTop::store_output(int n,node* root, int* cycle_check, Graph* MST)
{
	int count = 0;				// stores the number of edges in MST

	// until all the MST output is not stored, i.e, until count!= n-1
	while (count != n - 1)
	{
			//stores the graph values
			Graph myEdge;						
			myEdge.source = root->source;
			myEdge.dest = root->dest;
			myEdge.weight = root->weight;

			//finds the source and destination parents
			int neighbor1 = findNeighbor(myEdge.source, cycle_check);
			int neighbor2 = findNeighbor(myEdge.dest, cycle_check);
			
			if ( neighbor1 != neighbor2 )
			{
				//i.e. edge will be in MST
				MST[count]= myEdge;
				count++;
				cycle_check[neighbor1] = neighbor2;
			}
			
			root = delete_node(root, root->weight);		// delete the minimum value in the heap
			arrange(root);								// bring the next min value to the top
			
	}
		
}

int main()
{
	// the total number of vertices and edges of the graph
	int vertices = 9;
	int edges = 14;
	
	// heap which stores all the graph inputs on its nodes
	BSTminTop myHeap;			

	node* root = NULL;

	//graph inputs
	root = myHeap.push(root, 0, 1, 4);
	root = myHeap.push(root, 1, 2, 8);
	root = myHeap.push(root, 1, 7, 11);
	root = myHeap.push(root, 2, 3, 7);
	root = myHeap.push(root, 2, 5, 4);
	root = myHeap.push(root, 2, 8, 2);
	root = myHeap.push(root, 3, 4, 9);
	root = myHeap.push(root, 4, 5, 10);
	root = myHeap.push(root, 5, 3, 14);
	root = myHeap.push(root, 5, 6, 2);
	root = myHeap.push(root, 6, 8, 6);
	root = myHeap.push(root, 6, 7, 1);
	root = myHeap.push(root, 7, 0, 8);
	root = myHeap.push(root, 8, 7, 7);

	
	
	// Kruskal's Algorithm
	myHeap.kruskals(root, vertices);

	return 0;
}
