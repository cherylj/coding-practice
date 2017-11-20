// Author:  Cheryl Jennings

/* This program will read input from a file and store it in a binary tree.
 * It will then remove the element specified as input from the tree and
 * print the resulting tree.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>

struct node {
	int val;
	struct node *left;
	struct node *right;
};

void populate(char *fileName, int *list, int *size) {
	int fd, i, length, rc;
	char *buf, *c1, *c2;

	i = 0;

	buf = malloc(4096);
	if (!buf)
		printf("Unable to allocate memory: %d\n", errno);

	fd = open(fileName, O_RDWR);
	if (fd == -1){
		printf("Unable to open file: %s.  Error: %d\n",
			fileName, errno);
		free(buf);
		exit(errno);
	}
	
	length = read(fd, buf, 4096);	
	printf("length: %d\n", length);

	if(length == -1){
		printf("Error reading file: %d\n", errno);
		free(buf);
		exit(errno);
	}

	c1 = buf;
	while((c1 < (buf + length)) && (i < *size)){
		c2 = c1;
		while(*c2 != ' ' && *c2 != '\0')
			c2++;
		*c2 = '\0';
		list[i++] = atoi(c1);
		c1 = c2+1;
	}		

	*size = i;
	free(buf);

}

void printTree(struct node *head) {
	if(!head)
		return;

	// print the right tree, then us, then our left tree
	printTree(head->left);
	printf("%d ", head->val);
	printTree(head->right);
	
}

struct node* insertNode(struct node *head, int val, struct node *np){

	struct node *nnp;

	if(!np){
		nnp = malloc(sizeof(struct node));

		if(!nnp){
			printf("Unable to allocate a new node: %d\n", errno);	
			return(NULL);
		}

		nnp->val = val;
		nnp->left = NULL;
		nnp->right = NULL;
	}
	else
		nnp = np;

	if(!head){
		return(nnp);
	}

	if(nnp->val > head->val){
		if(head->right)
			insertNode(head->right, val, nnp);
		else 
			head->right = nnp;
		return(head);
	}

	// We are less than the head
	if(head->left)
		insertNode(head->left, val, nnp);
	else
		head->left = nnp;

	return(head);

}

int findNode(struct node *head, struct node **foundNode, 
	     struct node **parent, int val){

	if(!head || !foundNode){
		return(1);
	}

	if(val == head->val){
		*foundNode = head;
		return(0);
	}
	
	*parent = head;

	if(val > head->val)
		return(findNode(head->right, foundNode, parent, val));
	
	return(findNode(head->left, foundNode, parent, val));
}

struct node* removeNode(struct node *head, int val){

	struct node *parent, *np, *tmpNode;
	int rc;

	// If we remove a node, we will replace it with the largest
	// value in its left tree.  If it has no left tree, update the
	// parent's pointer to it to be the node's right pointer

	parent = np = tmpNode = NULL;

	rc = findNode(head, &np, &parent, val);
	if(rc)
		return(head);

	printf("Found node: %d with parent: %d\n", val, 
		(parent)? parent->val:0);

	if(np->left){
		// We have a left pointer, find the largest value in
		// this subtree
		parent = np;
		tmpNode = np->left;
		while(tmpNode->right){
			parent = tmpNode;
			tmpNode = tmpNode->right;
		}


		// We know this largest value will have no right subtree,
		// but if it has a left subtree, update its parent's right
		// tree (UNLESS the parent is the node being removed, then
		// replace that node's left tree
		//
		printf("parent's val: %d, tmpNode: %d\n", 
			parent->val, tmpNode->val);
		
		if(parent == np){
			parent->left = tmpNode->left;
		}
		else{
			parent->right = tmpNode->left;
		}

		np->val = tmpNode->val;

		free(tmpNode);
		return(head);
	}

	// We had no left subtree.  Replace our parent's pointer to us with
	// our right subtree. If we're the head node, update the head node 
	// pointer
	if(!parent)
		head = np->right;
	else if(np->val > parent->val)
		parent->right = np->right;
	else
		parent->left = np->right;

	free(np);
	return(head);
	
}

	
int main(int argc, char *argv[])
{
	int size=100, i;
	int list[100];
	struct node *head = NULL;

	if (argc != 3)
	{
		printf("Usage: %s <filename> <element>\n", argv[0]);
		return 1;
	}

	populate(argv[1], list, &size);

	for(i = 0; i < size; i++){
		head = insertNode(head, list[i], (struct node*)NULL);
	}
	printTree(head);
	printf("\n");
	
	printf("Removing element: %d\n", atoi(argv[2]));
	removeNode(head, atoi(argv[2]));

	printTree(head);
	printf("\n");

	
	return 0;
}
