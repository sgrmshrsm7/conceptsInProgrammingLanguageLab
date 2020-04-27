/* Given a pointer to the root of a binary tree, write a program to mark all the nodes of the tree using only constant space(i.e, without recursion and without using a stack) */

#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
	int data;
	int markingbit;
	struct Node* left;
	struct Node* right;
} node;

node *createNode(int data)
{
	node* newnode = (node*)malloc(sizeof(node));
	newnode -> data = data;
	newnode -> markingbit = 0;
	newnode -> left = NULL;
	newnode -> right = NULL;
	return (newnode);
}

node *createBinaryTree()
{
	node *root = createNode(1);
	root -> left = createNode(2);
	root -> right = createNode(3);
	root -> left -> left = createNode(4);
	root -> left -> right = createNode(5);
	root -> right -> left = createNode(6);
	root -> right -> right = createNode(7);
	root -> left -> left -> left = createNode(8);
	root -> left -> left -> right = createNode(9);
	return root;
}

void preorderTraversal(node *root)
{
	node *current;
	while (root)
	{
		if (root -> left == NULL)
		{
			printf("\nData : %d, Mark Bit : %d", root -> data, root -> markingbit);
			root = root -> right;
		}
		else
		{
			current = root -> left;
			while (current -> right && current -> right != root)
				current = current -> right;
			if (current -> right == root)
			{
				current -> right = NULL;
				root = root -> right;
			}
			else
			{
				printf("\nData : %d, Mark Bit : %d", root -> data, root -> markingbit);
				current -> right = root;
				root = root -> left;
			}
		}
	}
}

void mark(node *root)
{
	node *current;
	while (root)
	{
		if (root -> left == NULL)
		{
			root -> markingbit = 1;
			root = root -> right;
		}
		else
		{
			current = root -> left;
			while (current -> right && current -> right != root)
				current = current -> right;
			if (current -> right == root)
			{
				current -> right = NULL;
				root = root -> right;
			}
			else
			{
				root -> markingbit = 1;
				current -> right = root;
				root = root -> left;
			}
		}
	}
}

int main()
{
	node* root = createBinaryTree();
	preorderTraversal(root);
	mark(root);
	printf("\n\nAfter Marking nodes of Binary Tree :-");
	preorderTraversal(root);
	return 0;
}