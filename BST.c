//
//Soklong Lim
//CSE 222
//Programming Assignment #6
//Feb 13, 2015
//
//***Description***
//This program is about Binary Search Tree(BST) and function as following:
//-type 'd #' to delete #
//-type 's #' to search #
//-type 'p' to traverse the tree
//-type 'any integer' to add data to the tree
//-type 'Q' to exit the program
//-type '?' to ask for help
//-unrecognized command will bring error & help message
//-all contents on the tree are Unique
//
			
			
#include<stdio.h>
#include<string.h>
#include<stdlib.h>



struct node{
	int data;
	struct node *left;
	struct node *right;
};


//--------function declaration block--------------------			
struct node *newNode(int number);
struct node *insert(struct node *root, int number);
struct node *delete(struct node *root, int number);
struct node *leftMaxNode(struct node *root);
int search(struct node *root, int number);
int traverse(struct node *root);
int height(struct node *root);
int balance(struct node *root);
int tBalance(struct node *root);
int maxx(int a, int b);
void tFree(struct node *root);
void help();
//-----------------------------------------------------


main(){

	struct node *root;
	char buff[10];
	int num, height;

	root = NULL;			//set tree to empty
				
	system("clear");		//clear screen		
			
	help();					//start by showing instruction
			
	while(1){														//
		printf("\n> ");
		fgets(buff, 10, stdin);
		if( 1 == sscanf(buff, "%d", &num)){							//insert block
			if( search(root, num)!= 0){								//check if data is already on the tree
				root = insert(root, num);							//insert data to the tree
			} else {
				printf("!!! %d is Already on the tree.\n", num);
			}

		} else if( buff[0] == 's' || buff[0] == 'p' || buff[0] == '?' || buff[0] == 'Q' || buff[0] == 'd'){			//check for keywords 
			if( buff[0] == 's' || buff[0] == 'd'){					//search or deleted check
				if( 1 == sscanf(&buff[2], "%d", &num)){				//capture # to search or delete 
					if( buff[0] == 's'){							//search block 's #'
						if( search(root, num) !=0){						
							printf(" %d is NOT on the tree.\n", num);
						} else {
							printf(" %d is ON the tree.\n", num);
						}

					} else if( buff[0] == 'd'){						//delete block 'd #'
						if( search(root, num) !=0){					//check if data on the tree
							printf(" %d is NOT on the tree.\n", num);
						} else {
							root = delete(root, num);				//delete data	
						}
					} 

				} else { 											//error mseg if user does not enter proper # after 's' or 'd'
					printf("!!!Error!!! Unrecongnized Input.\n");
					help();
				}

			} else if( buff[0] == 'p'){								//traverse block 'p'
				if( isEmpty(root)!=0){								//check if empty
					printf("[");
					height = traverse(root);						//traverse return height of the tree
					printf(" ]\n");
					printf("Height = %d.\n", height);				//height of the tree
					if(tBalance(root) !=0){							//check balance
						printf("Tree is Unbalance.\n");				//empty tree also balance
					} else {
						printf("Tree is Balance.\n");
					}
				}

			} else if( buff[0] == 'Q'){                     		//exit and free memory block 'Q'
				tFree(root);										//free entire tree
    	        printf(">>>>>>>>>>>>Exit!!!\n\n");
        	    exit (0);

			} else if( buff[0] == '?'){								//help block '?'
				help();
			}

		} else {													//error mseg and help block
			printf("!!!Error!!! Unrecongnized Input.\n");
			help();
		}	//end of else if 		
	}	//end of while								
}	//end of main


//function block--------------------------------------------------------------

//create new node function-------------------
struct node *newNode(int number){
	struct node *new;
	
	new = malloc(sizeof(struct node));						//allocate memory
	if( new == NULL){
		printf("Out of Memory.\n");
		return NULL;										//return 'NULL' if fail
	} else {
		new->data = number;									//store data in new node
		new->left = NULL;
		new->right = NULL;
		return new;											//return 'new node' address if succeed
	}
}

//insert function-----------------------------
struct node *insert(struct node *root, int number){

    if( root == NULL){                                      //found empty spot on the tree
        root = newNode(number);								

    } else if( number < root->data){
        root->left = insert( root->left, number);           //move left and recurse

    } else if( number > root->data){
        root->right = insert( root->right, number);         //move right and recurse

    }
	return root;											//return 'root pointer'
}

//delete function----------------------------
struct node *delete(struct node *root, int number){
	struct node *previous;									//keep track of the path of next
	struct node *next;										//point to deleted node
	struct node *temp;

	previous = next = root;									//initialize preivous, next

	while(1==1){											
		while(number!=next->data){							//until deleted node found
			if(number>next->data){
				previous = next;							//move prevoius down one level
				next = next->right;							//move next to right 
			} else if(number<next->data){
				previous = next;							//move previous down one level
				next = next->left;							//move next to left 
			}
		}
															//now deleted node found

		if(next->left == NULL && next->right == NULL){			//zero child
			if(height(root)!=0){								//check if only one node leftover
				if(previous->left == next){						//next is the left child of previous
					previous->left = NULL;						
				} else {										//next is the right child of previous
					previous->right = NULL;
				}	
				free(next);										//free deleted node
				return root;									//return

			} else {											//tree with one node
				free(next);										//free deleted node
				root = NULL;									//set tree to null (empty tree)
				return root;									//return 
			}

		} else if(next->right == NULL){							//delted node has only 1 left child
			if(previous->left == next){							//next is the left child of previous
				previous->left = next->left;					//change previous to point to left child of deleted node
			} else {											//next is the right child of previous
				previous->right = next->left;					//change previous to point to left child of deleted node
			}
			free(next);											//free deleted node
			return root;										//return

		} else if(next->left == NULL){							//delted node has only 1 right child
			if(previous == next){								//check if deleted node is the root of the tree with no left child
				root = next->right;								//use right subtree of deleted node as the root of the tree
				free(next);										//free deleted node
				return root;									//return
			}

			if(previous->left == next){							//next is the left child of previous
				previous->left = next->right;					//change previous to point to right child of deleted node
			} else {											//next is the right child of previous
				previous->right = next->right;					//change previous to point to right child of delted node
			}
			free(next);											//free deleted node
			return root;										//return

		} else if(next->left != NULL && next->right != NULL){	//deleted node has 2 children
			temp = leftMaxNode(next->left);						//find the max node on the left subtree of deleted node
			next->data = temp->data;							//replace data of deleted with new max data 
			previous = next;									//reset previous
			next = next->left;									//reset next
			number = temp->data;								//reset number
		}														//go back to delete temp(max node on the left subtree of deleted node)
	}
}


//max left subtree function------------------
struct node *leftMaxNode(struct node *root){					//find the largest number on the left subtree of deleted node

	while( root->right != NULL){						
		root = root->right;										//continue to right until 
	}															//right subtree == NULL
	return root;
}


//search function----------------------------
int search(struct node *root, int number){

	if( root == NULL){
		return 1;											//return '1' if not found 

	} else if( number > root->data){						//move right and recurse
		return (search(root->right, number));

	} else if( number < root->data){						//move left and recurse
		return (search(root->left, number));

	} else 	if( number == root->data){
		return 0;											//return '0' if found
	} 
}															
			

//traverse function--------------------------
int traverse(struct node *root){							//print in-order (LNR)
	int h;
	
	if( root == NULL){
		return -1;									//empty tree return '-1'
	}
	traverse( root->left);
	printf(" %d", root->data);
	traverse( root->right);
	h = height(root);								//keep track of height
	return h;										//return height when done
}


//height function----------------------------
int height(struct node *root){						//measure the height of the tree
	int h;	

	if( root == NULL){								//empty tree: height = -1
		return -1;									//single node tree; height = 0
	}
	h = 1 + maxx( height(root->left), height(root->right));
	return h;
}


//check balance function---------------------
int tBalance(struct node *root){
	int ba, hLeft, hRight;
	
	hLeft = 1 + height(root->left);					//find height of left subtree
	hRight = 1 + height(root->right);				//find height of right subtree

	if( hLeft == hRight){
		ba = 0;
		return ba;									//balance
	} else if(hLeft+1 == hRight){
		ba = 0;
		return ba;									//balance
	} else if(hLeft == hRight+1){	
		ba = 0;
		return ba;
	} else {
		ba = 1;
		return ba;									//unbalance
	}
}


//find max value function--------------------
int maxx(int a, int b){

	if( a>=b){										//find the max valuse between 2 numbers
		return a;
	} else {
		return b;
	}
}


//isEmpty in stack---------------------------
int isEmpty(struct node *root){

	if( root == NULL){
		printf("Tree is Empty.\nHeight = -1.\n");
		printf("Tree is Balance.\n");
		return 0;									//return '0' if empty
	} else {
		return 1;									//return '1' if not empty
	}
}


//free the tree function---------------------
void tFree(struct node *root){						//free entire tree before exiting

	if(root!=NULL){
		tFree(root->left);
		tFree(root->right);
		free(root);
	}
}


//help instruction---------------------------
void help(){									 
	printf("\t*******Instruction*******\n");
	printf(" #\t Insert # the tree.\n");
	printf(" s #\t Search # on the tree.\n");
	printf(" d #\t Delete # from the tree.\n");
	printf(" p\t Traverse entire tree.\n");
	printf(" ?\t Help.\n");
	printf(" Q\t Quit the program.\n");
}


//-----------------------------------------end of code--------------------------------------------------
