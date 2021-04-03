# include <stdio.h>
# include <stdlib.h>
# define empty -1
# define default_cost 1
# define viol_cost 1
struct block
{
	int puzzle[4][4];
	struct block *up,*down,*left,*right;
};
int check_if_empty(int matrix[4][4])
{
	int i,j,freq=0;
	for(i=0;i<4;i++)
		for(j=0;j<4;j++)
		{
			if(matrix[i][j]==empty)
				return 1;
		}
	return 0;
}
int check_if_repeat(int matrix[4][4])
{
	int i,j,freq=0,temp,m,n;
	for(i=0;i<4;i++)
		for(j=0;j<4;j++)
		{
			temp=matrix[i][j];
			for(m=i;m<4;m++)
				for(n=j+1;n<4;n++)
				{
					if(matrix[m][n]==temp)
					{
						return 0;
					}
				}
		}
	return 1;
}
int check(int matrix[4][4])
{
	int i,j;
	for(i=0;i<4;i++)
		for(j=0;j<4;j++)
		{
			if(matrix[i][j]<1 || matrix[i][j]>15)
			{
				if(matrix[i][j]!=empty)
				{
					return 0;
				}
			}
			
		}
	if(check_if_empty(matrix)==1 && check_if_repeat(matrix)==1 )
		return 1;
	else
		return 0;
}

void printmatrix(int matrix[4][4])
{
	int i,j;
	for(i=0;i<4;i++)
	{
		for(j=0;j<4;j++)
		
			printf("\t%d",matrix[i][j]);
		printf("\n");	
		
	}	
			
}
int min(int arr[4])
{
	int i,small=arr[0];
	for(i=1;i<3;i++)
	{
		if(arr[i]<=small)
			small=arr[i];
	}
	return small;
	
}
int cost_calculator(int matrix[4][4],int goal[4][4]);
int empty_colindex_finder(int matrix[4][4]);
int empty_rowindex_finder(int matrix[4][4]);
void movements_decision_function(struct block *root,int cost,int goal[4][4]);
void main()
{
	int i,j,cost,goal[4][4],status=1;
	
	printf("\n\n\n************ADA MINIPROJECT***************\n\n\n");
	printf("\n$$$$$$$$$$TOPIC:15-PUZZLE PROBLEMS USING LCBB$$$$$$$$$$$$$\n");
	printf("\n##########Strategy:Least Cost Branch and Bound(LCBB)###########\n");
	printf("\n@@@@@@@@@@Data structure used:General tree@@@@@@@@@@@@@\n");
	
	
	
	do
	{
		printf("\n\nRULES OF THE PUZZLE:\n\n");
		printf("\n1.Enter a 4x4 initial matrix with 15 numbers and 1 empty space.\n");
		printf("\n2.The 15 numbers should only be from 1 to 15.\n");
		printf("\n3.Please do not enter 0 or negative numbers or any positive number more than 15.\n");
		printf("\n4.Enter another 4x4 goal matrix similarly.");
		printf("\n5.The n-puzzle problem moves the numbers up,down,left or right of the blank space in the initial matrix to obtain the goal matrix.\n");
		
		printf("\nEnter initial matrix.Use %d to indicate the empty space:",empty);
		struct block *root=(struct block*)malloc(sizeof(struct block));
		root->left=NULL;
		root->down=NULL;
		root->right=NULL;
		root->up=NULL;
		for(i=0;i<4;i++)
			for(j=0;j<4;j++)
				scanf("%d",&root->puzzle[i][j]);
		if(check(root->puzzle)==0)
		{
			printf("\nPlease enter a valid input for the initial matrix.Ensure that your input satisfies all the rules given above.");
			printf("\nPress 1 to continue,0 to exit.Thank you!\n");
			scanf("%d",&status);
			
			
		}
		
		if(check(root->puzzle)==1)
		{
			printf("\nEnter goal matrix.Use %d to indicate the empty space:",empty);
			for(i=0;i<4;i++)
				for(j=0;j<4;j++)
					scanf("%d",&goal[i][j]);
		}
	
		
			
		if(check(goal)==0 && check(root->puzzle)==1)
		{
			printf("\nPlease enter a valid input for the goal matrix.Ensure that your input satisfies all the rules given above:");
			printf("\nPress 1 to continue,0 to exit.Thank you!\n");
			scanf("%d",&status);
			
		}
		
		if(check(goal)==1 && check(root->puzzle)==1)
		{
			cost=cost_calculator(root->puzzle,goal);
			//printf("\nCost of initial=%d",cost);
			//printmatrix(root->puzzle);
			movements_decision_function(root,cost,goal);
			printf("\nPress 1 to continue,0 to exit.Thank you!\n");
			scanf("%d",&status);
			
		}
	
		
		
		
		
	
	}while(status==1);			
	
	
	
}
int cost_calculator(int matrix[4][4],int goal[4][4])
{
	int i,j,cost=0;
	for(i=0;i<4;i++)
	{
		for(j=0;j<4;j++)
		{
			if(matrix[i][j]!=goal[i][j])
			{
				cost=cost+viol_cost;
			}
		}
	}
	return cost;
}
void movements_decision_function(struct block *root,int cost,int goal[4][4])
{
	int posi,posj,i,j,swap,costarr[4],mincost,min_index;
	
	if(cost==default_cost || cost==0)
	{
		printf("\nHurrah!Goal reached!!!");
		return;
	}
	
	struct block *temp_up=(struct block*)malloc(sizeof(struct block));
	//printf("\ntemp_up created");
	struct block *temp_down=(struct block*)malloc(sizeof(struct block));
	struct block *temp_left=(struct block*)malloc(sizeof(struct block));
	struct block *temp_right=(struct block*)malloc(sizeof(struct block));
	
	temp_up->up=NULL;
	temp_up->down=NULL;
	temp_up->left=NULL;
	temp_up->right=NULL;
	
	temp_down->up=NULL;
	temp_down->left=NULL;
	temp_down->right=NULL;
	temp_down->down=NULL;
	
	temp_left->up=NULL;
	temp_left->down=NULL;
	temp_left->left=NULL;
	temp_left->right=NULL;
	
	temp_right->up=NULL;
	temp_right->down=NULL;
	temp_right->left=NULL;
	temp_right->right=NULL;
	
	for(i=0;i<4;i++)
	{
		for(j=0;j<4;j++)
		{
			temp_up->puzzle[i][j]=root->puzzle[i][j];
			temp_left->puzzle[i][j]=root->puzzle[i][j];
			temp_right->puzzle[i][j]=root->puzzle[i][j];
			temp_down->puzzle[i][j]=root->puzzle[i][j];
		}
	}
	
	posi=empty_rowindex_finder(root->puzzle);
	posj=empty_colindex_finder(root->puzzle);
	
	if(posi >= 0 && posi < 3)
	{
		swap=temp_down->puzzle[posi][posj];
		temp_down->puzzle[posi][posj]=temp_down->puzzle[posi+1][posj];
		temp_down->puzzle[posi+1][posj]=swap;
	}

	
	if(posj >= 0 && posj < 3)
	{
		swap=temp_left->puzzle[posi][posj];
		temp_left->puzzle[posi][posj]=temp_up->puzzle[posi][posj+1];
		temp_left->puzzle[posi][posj+1]=swap;
	}
	
	if(posi > 0 && posi <= 3)
	{
		swap=temp_up->puzzle[posi][posj];
		temp_up->puzzle[posi][posj]=temp_up->puzzle[posi-1][posj];
		temp_up->puzzle[posi-1][posj]=swap;
	}
	if(posj > 0 && posj <= 3)
	{
		swap=temp_right->puzzle[posi][posj];
		temp_right->puzzle[posi][posj]=temp_up->puzzle[posi][posj-1];
		temp_right->puzzle[posi][posj-1]=swap;
	}
	
	root->left=temp_left;
	root->up=temp_up;
	root->right=temp_right;
	root->down=temp_down;
	
	/*printf("\nUP:");
	printmatrix(temp_up->puzzle);
	printf("\nDOWN:");
	printmatrix(temp_down->puzzle);
	printf("\nLEFT");
	printmatrix(temp_left->puzzle);
	printf("\nRIGHT");
	printmatrix(temp_right->puzzle);*/
	
	costarr[0]=cost_calculator(temp_up->puzzle,goal)+default_cost;
	costarr[1]=cost_calculator(temp_down->puzzle,goal)+default_cost;
	costarr[2]=cost_calculator(temp_left->puzzle,goal)+default_cost;
	costarr[3]=cost_calculator(temp_right->puzzle,goal)+default_cost;
	
	mincost=min(costarr);
	//printf("\nMin cost=%d",mincost);
	for(i=0;i<4;i++)
	{
		if(costarr[i]==mincost)
		{
			min_index=i;
			break;
		}
	}
	if(min_index==0 && posi > 0 && posi <= 3)
	{
		printf("\n-->>Move %d down",root->puzzle[posi-1][posj]);
		printf("\nNow,the matrix obtained is:\n");
		printmatrix(temp_up->puzzle);
		movements_decision_function(temp_up,mincost,goal);
		free(temp_down);
		free(temp_left);
		free(temp_right);
	}
	else if(min_index==1 && posi >= 0 && posi < 3)
	{
		printf("\n-->>Move %d up",root->puzzle[posi+1][posj]);
		
		printf("\nNow,the matrix obtained is:\n");
		printmatrix(temp_down->puzzle);
		
		movements_decision_function(temp_down,mincost,goal);
		
		free(temp_up);
		free(temp_left);
		free(temp_right);
	}
	else if(min_index==2 && posj >= 0 && posj < 3)
	{
		printf("\n-->>Move %d left",root->puzzle[posi][posj+1]);
		
		printf("\nNow,the matrix obtained is:\n");
		printmatrix(temp_left->puzzle);
		
		movements_decision_function(temp_left,mincost,goal);
		free(temp_down);
		free(temp_up);
		free(temp_right);
	}	
	else if(min_index==3 && posj > 0 && posj <= 3)
	{
		printf("\n-->>Move %d right",root->puzzle[posi-1][posj-1]);
		
		printf("\nNow,the matrix obtained is:\n");
		printmatrix(temp_right->puzzle);
		
		movements_decision_function(temp_right,mincost,goal);
		free(temp_down);
		free(temp_left);
		free(temp_up);
	}
    else
    {
        printf("Error in bounds! Min Index = %d & Pos = (%d, %d)", min_index, posi, posj);
        return;
    }
	
}
int empty_rowindex_finder(int matrix[4][4])
{
	int i,j,posi;
	for(i=0;i<4;i++)
		for(j=0;j<4;j++)
		{
			if(matrix[i][j]== empty)
			{
				posi=i;
				break;
			}
		}
	/*if(!(posi < 0 ||  posi > 3))
		printf("\nSome unexpected error,sorry!!!");*/
		
	return posi;
}
int empty_colindex_finder(int matrix[4][4])
{
	int i,j,posj;
	for(i=0;i<4;i++)
		for(j=0;j<4;j++)
		{
			if(matrix[i][j]== empty)
			{
				posj=j;
				break;
			}
		}
	return posj;
}

