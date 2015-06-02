typedef struct Bnode
{
	LinkStack S ;
	int min_bound;
	struct Bnode *left;
	struct Bnode *right;
}BTNode,*BTree;

/*********************************************************/
void print1(int *graph,int n);
int row_select(int *graph,BTree T,int n);
int col_select(int *graph,int row,int n);
int row_add(int *graph,int row,int col,int n);
int col_add(int *graph,int row,int col,int n);
void copyfromfather(LinkStack S1,LinkStack S);
bool termination(BTree T,int n);
int leaf(int *graph,int n,int *x,int *y);
bool ALLINACCESS(int *graph,int n);
/*******************************************************/
int MIN_BOUND = INACCESS;
void Create_TSPTree(int *graph,BTree T,int n)
{
	int i,j,k;
	int row,col;
	int left_min_bound;
	int right_min_bound; 
	int min_bound;
	int *graphL = (int *)malloc(n*n*sizeof(int));
	int *graphR = (int *)malloc(n*n*sizeof(int));
	if(termination(T,n))
	{	
		T->left = (BTree)malloc(sizeof(BTNode));
		T->right = NULL;
	    LinkStack SL = (LinkStack)malloc(sizeof(StackNode));
	    InitStack(SL);
		copyfromfather(SL,T->S);
		//print1(graph,n);
		T->left->min_bound = T->min_bound + RC_have_Zero(graph,n);
		//print1(graph,n);
		if(MIN_BOUND > T->left->min_bound)
		{
		     MIN_BOUND = T->left->min_bound;
		}
		else
		{
			T->left = NULL;
			return ;
		}
		leaf(graph,n,&row,&col);
		//printf("%d最后%d\n",row,col);
		if(row>=0&&row<n&&col>=0&&col<n)
		{
			Push(SL,row,col);
			T->left->S = SL;
			T->left->left =NULL;
			T->left->right = NULL;
		}
		else
		{
			T->left = NULL;
		}
		return ;
	}

	min_bound = RC_have_Zero(graph,n);
   // print1(graph,n);
	for(i = 0;i < n;i++)
	{
		for(j = 0;j < n;j++)
		{
			*(graphL + i*n + j) = *(graph + i*n + j);
		}
	}
	row = row_select(graphL,T,n);
	col = col_select(graphL,row,n);
	//printf("选择的节点%d    %d\n",row,col);
	T->left = (BTree)malloc(sizeof(BTNode));
	T->right = (BTree)malloc(sizeof(BTNode));
	LinkStack SL = (LinkStack)malloc(sizeof(StackNode));
	LinkStack SR = (LinkStack)malloc(sizeof(StackNode));
    InitStack(SL);
	InitStack(SR);
	copyfromfather(SL,T->S);
	copyfromfather(SR,T->S);
	left_min_bound = T->min_bound + min_bound + *(graphL + row*n + col);
	right_min_bound = T->min_bound + min_bound + row_add(graph,row,col,n) + col_add(graph,row,col,n);
	

	for(i = 0;i < n;i++)
	{
		for(j = 0;j < n;j++)
		{
			*(graphR + i*n + j) = *(graph + i*n + j);
		}
	}
	*(graphR + row*n + col) = INACCESS;

	for(i = 0;i < n;i++)
	{
		*(graph + row*n + i) = INACCESS;
	}
	for(i = 0;i < n;i++)
	{
		*(graph + i*n + col) = INACCESS;
	}
	*(graph + col*n + row) = INACCESS;
	Push(SL,row,col);
	T->left->min_bound = left_min_bound;
	T->left->S = SL;
	T->right->S = SR;
	T->right ->min_bound = right_min_bound;
	if(row < 0)
	{
		T->left = NULL;
		free(T->left);		
	}
	if(T->left&&T->left->min_bound < MIN_BOUND)
	{
		Create_TSPTree(graph,T ->left,n);
	}
	else
	{
		T->left = NULL;
	}
	if(T->right&&T->right->min_bound < MIN_BOUND)
	{
		Create_TSPTree(graphR,T ->right,n);
	}
	else
	{
		T->right = NULL;
	}
}

/***************************************************/
void copyfromfather(LinkStack S1,LinkStack S)
{
	LinkStack P = S;
	while(P->next)
	{
		Push(S1,P->next->dot.edge_from,P->next->dot.edge_to);
		//printf("%d  从父亲拷贝路径  %d\n",P->next->dot.edge_from,P->next->dot.edge_to);
		P = P ->next;
	}
}

/********************************************/

int second_min(int *graph,int n,int row);

bool no_circle(edge *SET ,int x,int y,int k);


int row_select(int *graph,BTree T,int n)
{
	int i;
	int *RR = (int *)malloc(n*sizeof(int));
	edge *SET = (edge *)malloc(n*sizeof(edge));
	for(i = 0;i < n;i++)
	{
		*(RR + i) = *(graph + i*n + second_min(graph,n,i));
		//printf("次、次最小值%d\n",*(RR + i));
	}
	int count = 0;
	LinkStack Q = T->S->next;
	while(Q)
	{
		SET[count] = Q->dot;
		count++;
		Q = Q->next;
	}
	int k = 0;	
	int TAG = 1;
	int v = 0;
	while(TAG&&v < n)
	{
		k = 0;
		int t = 0;
		int j;
		int RR_MAX = 0;
		for(i = 0;i < n;i ++)
		{
			if(RR_MAX < *(RR + i))
			{
				RR_MAX = *(RR + i);
				k = i;
			}
		}
		for(t = 0;t < n;t++)
		{
			j = col_select(graph,k,n);
			if(no_circle(SET,k,j,count)&&(*(graph + k*n + j)!= INACCESS))
			{
				//printf("k的值%d          j的值%d\n",k,j);
				//printf("判断条件%d\n",no_circle(SET,k,j,count));
				//printf("判断%d\n",*(graph + k*n + j));
				TAG = 0;
				break;
			}
			else
			{
				//printf("sss");
				*(graph + k*n + j) = INACCESS;
			}
		}
		v++;
		*(RR + k) = -1;
	
	}
   return k;


}

int second_min(int *graph,int n,int row)
{
	int i;
	int *row_point = (int *)malloc(n*sizeof(int));
	for(i = 0;i < n;i++)
	{
		row_point[i] = *(graph + row*n + i);
	}
	int MIN = INACCESS;
	int k = 0;
	for(i = 0;i < n;i++)
	{
		if(MIN > row_point[i])
		{
			MIN = row_point[i];
			k = i;
		}
	}
	row_point[k] = INACCESS;
	MIN = INACCESS;
	k = 0;
	for(i = 0;i < n;i++)
	{
		if(MIN > row_point[i])
		{
			MIN = row_point[i];
			k = i;
		}
	}
	free(row_point);
	return k;
}


int col_select(int *graph,int row,int n)
{	int i;
	int k = 0;
	int MIN_VALUE = INACCESS;
	for(i = 0;i < n;i++)
	{
		if(MIN_VALUE > *(graph + row*n + i))
		{
			MIN_VALUE = *(graph + row*n + i);
			k = i;
		}
	}
	return k;
}


bool no_circle(edge *SET ,int x,int y,int k)
{
	int i = 0,j;
	while(i < k)
	{
		for(j = 0;j < k;j++)
		{
			if(y == SET[j].edge_from)
				break;
		}
		if(SET[j].edge_to == x)
		{			
			return FALSE;
		}
		y = SET[j].edge_to;
		i++;
	}
	return TRUE;
}


int row_add(int *graph,int row,int col,int n)
{
	int i;
	int *R_ADD = (int *)malloc(n*sizeof(int));
	for(i = 0;i < n;i++)
	{
		*(R_ADD + i) = *(graph + row*n + i);
	}
	*(R_ADD + col) = INACCESS;
	int RR_MIN = INACCESS;
	for(i = 0;i < n;i++)
	{
		if(RR_MIN > *(R_ADD + i))
		{
			RR_MIN = *(R_ADD + i);
		}
	}
	free(R_ADD);
	return RR_MIN;
}
int col_add(int *graph,int row,int col,int n)
{
	int i;
	int *C_ADD = (int *)malloc(n*sizeof(int));
	for(i = 0;i < n;i++)
	{
		*(C_ADD + i) = *(graph + i*n + col);
	}
	*(C_ADD + col) = INACCESS;
	int C_MIN = INACCESS;
	for(i = 0;i < n;i++)
	{
		if(C_MIN  > *(C_ADD + i))
		{
			C_MIN = *(C_ADD + i);
		}
	}
	free(C_ADD);
	return C_MIN;
}

bool termination(BTree T,int n)
{
	int k = 0;
	LinkStack Q = T->S->next;

	while(Q)
	{
		k++;
		Q = Q->next;
	}
	if(k == n - 1)
		return TRUE;
	else
		return FALSE;
}

int leaf(int *graph,int n,int *x,int *y)
{
	int i,j;
	for(i = 0;i < n;i++)
	{
		for(j = 0;j < n;j++)
		{
			if(*(graph + i*n +j) == 0)
			{
				*x = i;
				*y = j;
				//printf("真实\n");
				return TRUE ;
			}
		}
	}
	return FALSE;
}

/************************输出*************************************/
int terminal(BTree T,int n)
{
	int k = 0;
	if(T->S->next)
	{
	    LinkStack Q = T->S->next;
		while(Q)
	    {
	     	k++;
	    	Q = Q->next;
	    }
	}
	//printf("输出%d\n",k);
	return k;
}


void ergodic_Tree(BTree T,int n,Bedge P)
{
	int i = 0;	
	if(terminal(T,n)== n)
	{	
		LinkStack Q = T->S->next;
		while(Q)
		{
			*(P + i) = Q->dot;
			//printf("%d  正在生成最终节点 %d\n",(P + i)->edge_from,(P + i)->edge_to);
			Q = Q->next;
			i++;
		}
		return ;
	}			
	if(T->left != NULL)
	{	
	    ergodic_Tree(T->left,n,P);
	}
	if(T->right != NULL)
	{		
	    ergodic_Tree(T->right,n,P);
	}
}

void print(Bedge P,int n)
{
	int i = 0;
	int j;
	int from = P[0].edge_from,to;
	printf("%d -> ",from);
	while(i < n)
	{
		for(j = 0;j < n;j++)
		{
			if(from == P[j].edge_from)
			{
				if(i < n -1)
				{
					to = P[j].edge_to;
					printf("%d  ->",to);
					break;
				}
				else
				{
					printf("%d\n ",P[j].edge_to);
				}
			}
		}
		from = to;
		i++;
	}
}



void print1(int *graph,int n)
{
	int i,j;
	for(i = 0;i < n;i++)
	{
		for(j = 0;j < n;j++)
		{
			printf("   %5d",*(graph + i*n +j));
		}
		printf("\n");
	}
}


bool ALLINACCESS(int *graph,int n)
{
	int i,j;
	for(i = 0;i < n;i++)
	{
		for(j = 0;j < n;j++)
		{
			if(*(graph + i*n + j)!=INACCESS);
			{
				return FALSE;
			}
		}
	}
	return TRUE;
}