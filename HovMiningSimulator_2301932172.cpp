/*
 *	created : April 8th 2020
 *	by		: David Christian M. A. M. (2301932172)
 */
 
/////////////// COPY -> PASTE ////////////////////////////////////////////
// 1 52 10 1 31 15 1 27 25 1 40 11 1 79 89 1 65 4 1 82 2 1 94 51 1 40 13//
//////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct node{
	int cave;
	int gold;
	int depth ;
	struct node *left;
	struct node *right;	
};

int total = 0;
int gold_total[999];

struct node *newNode(int cave, int gold, int recursive){  // create new node
	struct node *currNewNode = (struct node*)malloc(sizeof(struct node));
	currNewNode->cave = cave;
	currNewNode->gold = gold;
	currNewNode->depth = recursive;
	currNewNode->left = NULL;
	currNewNode->right = NULL;
	printf("\n New cave index detected.\n");
	printf(" Total gold production for Cave %d is %d.\n\n\n", cave, gold);
	return currNewNode;
}

struct node *insert(struct node *root, int cave, int gold, int recursive){
	if(root == NULL){ // if node is empty
		recursive++;
		return newNode(cave, gold, recursive);
	}	
	else if (cave == root->cave){
		struct node *temp = NULL;
		temp = root;
		temp->gold = temp->gold + gold;
		printf("\n Cave index already existed.\n");
		printf(" Total gold production for Cave %d is %d.\n\n\n", cave, root->gold);
	}
	else if(cave < root->cave){ // insert to the left of the root
		recursive++;
		root->left = insert(root->left, cave, gold, recursive);
	}
	else if(cave > root->cave){ // insert to the right of the root
		recursive++;
		root->right = insert(root->right, cave, gold, recursive);
	}
	return root;
}

void printAll(struct node *root){ // print with infix method
	if(root == NULL){
		return;
	}
	printAll(root->left);
	printf(" >> Cave %d  (depth %-3d), total gold production: %d\n", root->cave, root->depth, root->gold);
	printAll(root->right);
}

void printAllbyDepth(struct node *root, int depth, int total_gold){
	if(root == NULL){
		return;
	}
	if(root->depth == depth){
		gold_total[depth] = gold_total[depth] + root->gold;
	}
	printAllbyDepth(root->left, depth, total_gold);
	printAllbyDepth(root->right, depth, total_gold);
}

void freeAll(struct node *temp)
{
    if(temp == NULL){
    	return;
	}
	if(temp->left != NULL){
    	freeAll(temp->left);
	}
	if(temp->right != NULL){
    	freeAll(temp->right);
	}
	free(temp);
}

int main(){
	for(int z=0; z<1000; z++){
		gold_total[z] = NULL;
	}
	int menu = 0;
	struct node *root = NULL;
	do{
		printf("\n Hov Mining Simulator\n");
		printf(" ====================\n");
		printf(" [1] Insert Mining Data\n");
		printf(" [2] Display All Cave Data\n");
		printf(" [3] Display Mining Reports\n");
		printf(" [4] Exit\n");
		printf(" >> ");
		scanf("%d", &menu);
		
		if(menu == 1){
			system("cls");
			int cave, gold_production, recursive = 0;
			do{
				printf("\n Input cave index [1-999]     : ");
				scanf("%d", &cave);
			}while(cave < 1 || cave > 999);
			do{
				printf(" Input gold production [1-100]: ");
				scanf("%d", &gold_production);
			}while(gold_production < 1 || gold_production > 100);
			root = insert(root, cave, gold_production, recursive);
			total++;
		}
		else if(menu == 2){
			system("cls");
			if(total == 0){
				printf(" Cave data is empty, nothing to display.\n");
			}
			else{
				printf("\n");
				printAll(root);
				printf("\n");				
			}
		}
		else if(menu == 3){
			system("cls");
			if(total == 0){
				printf("\n");
				printf(" Cave data is empty, nothing to report.\n");
				printf("\n");
			}
			else{
				printf("\n");
				for(int i=1; i <= total; i++){
					printAllbyDepth(root, i, gold_total[i]);
					if(gold_total[i] != NULL){
						printf(" >> Total gold production for depth %-3d is %d\n", i, gold_total[i]);
					}
				}
				printf("\n");				
			}
		}
		else if(menu == 4){
			freeAll(root);
			printf("\n All data has been removed from memory.\n");
			printf(" Thank you for playing. see you again...\n");
			break;
		}
		system("pause");
		system("cls");
	}while(true);
	
	return 0;
}

