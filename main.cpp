#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "LinkStack.h"
#include "Init_Graph.h"
#include "TSP_function.h"
#include "Tree.h"
void copy(int *graph,int *graphP0,int n);
int price(int *graph,Bedge dot,int n);

int main()
{
	long int start,finish;
	int n;
	LinkStack S = (LinkStack)malloc((sizeof(StackNode)));
	InitStack(S);
	printf("Input the number of vertex n:\n");
	scanf("%d",&n);
	int *graph = (int *)malloc(n*n*sizeof(int));
	int *graphP0 = (int *)malloc(n*n*sizeof(int));	
	Init_data(graph,n);
	copy(graph,graphP0,n);
	print1(graph,n);
	start = clock();
	BTree T;
	T = (BTree)malloc(sizeof(BTNode));
	T ->min_bound = RC_have_Zero(graph,n);
	T ->S = S;
	Create_TSPTree(graph,T,n);
	Bedge dot = (Bedge)malloc(n*sizeof(edge));	
	ergodic_Tree(T,n,dot);
	finish = clock();
	printf("最短路径为：");
	print(dot,n);
	printf("时间耗费为%d ms\n",finish - start);
	printf("代价为：%d\n",price(graphP0,dot,n));
	getchar();
	return 0;
}

void copy(int *graph,int *graphP0,int n)
{
	int i,j;
	for(i = 0;i < n;i++)
	{
		for(j = 0;j < n;j++)
		{
			*(graphP0 + i*n +j) = *(graph + i*n +j);
		}
	}
}

int price(int *graph,Bedge dot,int n)
{
	int i;
	int sum = 0;
	for(i = 0;i < n;i++)
	{
		sum = sum + *(graph + dot[i].edge_from*n + dot[i].edge_to);
	}
	return sum;
}