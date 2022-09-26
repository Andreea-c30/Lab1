#include <stdio.h>
#include <stdlib.h>
#include<string.h>

struct node {
	int item;
	struct node* left;
	struct node* right;
};

void menu(){
	printf("Welcome to the menu!\n");
	printf("\n1 - Load structure from a file");
	printf("\n2 - Print structure to a file");
	printf("\n3 - Insert");
	printf("\n4 - Delete");
	printf("\n5 - Search");
	printf("\n6 - In order");
	printf("\n7 - Pre order");
	printf("\n8 - Post order");
	printf("\n9 - Sort tree");
	printf("\nChoose an option -> ");
}

// Create a new Node
struct node* createNode(int value) {
	struct node* newNode = malloc(sizeof(struct node));
	newNode->item = value;
	newNode->left = NULL;
	newNode->right = NULL;

	return newNode;
}

// Insert on the left of the node
struct node* insertLeft(struct node* root, int value) {
	root->left = createNode(value);
	return root->left;
}

// Insert on the right of the node
struct node* insertRight(struct node* root, int value) {
	root->right = createNode(value);
	return root->right;
}



//Searching a value in the tree
struct node* search(struct node ** tree, int val) {
	if(!(*tree)) {
		return NULL;
	}

	if(val == (*tree)->item) {
		return *tree;
	} else if(val < (*tree)->item) {
		search(&((*tree)->left), val);
	} else if(val > (*tree)->item){
		search(&((*tree)->right), val);
	}
}

//Delete the nodes of the binary tree 
void delete(struct node * tree) {
	if (tree) {
		delete(tree->left);
		delete(tree->right);
		free(tree);
	}
}

// Inorder traversal
void inorderTraversal(struct node* root) {
	if (root == NULL) return;

	inorderTraversal(root->left);
	printf(" %d;", root->item);
	inorderTraversal(root->right);
}

// Preorder traversal
void preorderTraversal(struct node* root) {
	if (root == NULL) return;

	printf(" %d;", root->item);
	preorderTraversal(root->left);
	preorderTraversal(root->right);
}

// Postorder traversal
void postorderTraversal(struct node* root) {
	if (root == NULL) return;

	postorderTraversal(root->left);
	postorderTraversal(root->right);
	printf(" %d;", root->item);
}


struct aux
{
	char in;
	int poz; 
}list[20][10];

int lung[20];
int loc=1;

struct node* insertSorted(struct node* root, int value) {
	if (root == NULL) return createNode(value);
	else if (value <= root->item) root->left = insertSorted(root->left, value);
	else root->right = insertSorted(root->right, value);

	return root;
}

void printGivenLevel(struct node *root, int level,int h) 
{
    if (root == NULL)
    {
    	lung[h]++;
        return; 
    }
    if (level == 1) 
    {
    	lung[h]+=1;
    	list[h][loc].in=root->item;
    }
    else if (level > 1) 
    { 
        printGivenLevel(root->left, level-1,h); 
        loc++;
        printGivenLevel(root->right, level-1,h); 
    }
}

int height(struct node *r)
{
	int s=0,d=0;
	
	if(!r)
	{
		return 0;
	}
	s=height(r->left);
	d=height(r->right);
	
	if(s>d || s==d)
	{
		return s+1;
	}
	else
	{
		return d+1;
	}
}

void printTree(struct node *row)
{
	for(int i=1;i<=height(row);i++)
	{
		loc=1;
		lung[i] = 0;
		printGivenLevel(row,i,i);
	}

	int x=height(row)*2,y=x;
	for(int i=1;i<=height(row);i++) {
		for(int f=1;f<=lung[i];f++) {
			if(f==1) {
				for(int ii=1;ii<=x*2;ii++) printf(" ");
			}
			else if(i!=height(row)) {
				for(int ii=1;ii<=y*2;ii++) printf(" ");
			}
			else {
				if(f%2!=0) {
					for(int ii=1;ii<=3;ii++) printf(" ");
				}
				if(f%2==0)
				{
					for(int ii=1;ii<=4;ii++) printf(" ");
				}
			}
			printf("%d", list[i][f].in);
		}
		y=x;
		x/=2;
		printf("\n");
	}

}

// Load tree from a file
struct node* loadFromFile(FILE *fp) {
	int value;
	struct node* tree;

	// Scan fuccent value from file
	fscanf(fp, "%d", &value);

	// If x value is 0 then close this branch
	if(value==0) {
		tree = NULL;
	} else {
		tree = createNode(value);

		tree->left = loadFromFile(fp);
		tree->right = loadFromFile(fp);
	}

	return tree;
}

// Load tree from console
struct node* loadFromConsole() {
	int value;
	struct node* tree;

	// Scan fuccent value from file
	scanf("%d", &value);

	// If x value is 0 then close this branch
	if(value==0) {
		tree = NULL;
	} else {
		tree = createNode(value);

		tree->left = loadFromConsole();
		tree->right = loadFromConsole();
	}

	return tree;
}

void saveInFile(struct node *root, FILE *fp) {
	if (root == NULL) {
		fprintf(fp, "%d\n", 0);
		return;
	}

	fprintf(fp, "%d\n", root->item);
	saveInFile(root->left, fp);
	saveInFile(root->right, fp);
}

struct node* sort(struct node *root, struct node* resp) {
	if(root == NULL) return resp;
	resp = sort(root->left, resp);
	resp = sort(root->right, resp);

	resp = insertSorted(resp, root->item);
	return resp;
}

int main() {
	struct node* tmp;
	int option,val;
	struct node* root;

	menuop:
	menu();
	scanf("%d", &option);

	switch(option)
	{
		case 1:
			//load the data structure from a file and display it in the terminal.
			printf("The structure loaded from file\n");

			char file_path[100];

			// Input file path
			printf("File path > ");
			scanf("%s", file_path);
			
			// Open file
			FILE *fp_in;
			fp_in = fopen(file_path, "r");
			
			root = loadFromFile(fp_in);
			fclose(fp_in);
			printTree(root);
		break;
		case 2:
			printf("The structure loaded from console\n");

			printf("Please input raw tree (0 is the separator) > ");
			root = loadFromConsole();

			printTree(root);

			printf("Save tree in file? (y|n)\n");
			
			char save;
			scanf("%c", &save);
			scanf("%c", &save);
			
			if(save == 'y') {
				char file_path[100];

				// Input file path
				printf("File path > ");
				scanf("%s", file_path);
				FILE *fp_out;
				fp_out = fopen(file_path, "w+");
				saveInFile(root, fp_out);
				fclose(fp_out);
			}

		break;
		case 3:
			printf("Insert binary tree\n" );

			//adding a root to the tree
			//printf("Add a root :");
			//int rval;
			//scanf("%d",&rval);
			//root = createNode(rval);
			//creating a label to add more nodes to the tree
			insert:
			printf("\n Input the value -> ");
			scanf("%d",&val);

			printf("To insert on the right side press - 0\nTo insert on the left side press- 1\n");
			int side;
			scanf("%d",&side);
			if(side==0){
				insertRight(root, val);
			}
			else if(side==1){
				insertLeft(root, val);
			}
			else printf("This is not an option! Try again!");

			printf("Do you want to insert another node?\n Press 0-no or 1-yes\n->");   
			int ins;
			scanf("%d", &ins);
			if (ins==1)
				goto insert;
			else
				printf("The nodes have been inserted\n");
			break;
		case 4:
			delete(root);
			printf("The tree has been deleted");
			break;
		case 5:
			printf("Input the searching the value: \n");
			int searchval;
			scanf("%d",&searchval);
			tmp = search(&root, searchval);
			if (tmp) {
				printf("\nSearched node=%d ", tmp->item);
				printf("was found in the tree");
			}
			else {
				printf("The node was not found in tree.\n");
			}
			break;
		case 6:
			printf("Inorder traversal \n");
			inorderTraversal(root);
			break;
		case 7:
			printf("\nPreorder traversal \n");
			preorderTraversal(root);
			break;
		case 8:
			printf("\nPostorder traversal \n");
			postorderTraversal(root);
			break;
		case 9:
			root = sort(root, NULL);
			// preorderTraversal(root);
			printTree(root);
			//sorted tree
			printf("The tree has been sorted:\n");
			inorderTraversal(root);
			break;
		
	}

	printf("\nBack to menu?\n Press 0-no or 1-yes\n->");   
	int op;
	scanf("%d", &op);
	if (op)
		goto menuop;
}
