#define TRUE 1
#define FALSE 0
#define NULL  0
typedef struct edge
{
	int edge_from;
	int edge_to;
}*Bedge;
typedef edge ElementType;
typedef struct node{
	ElementType dot;
	struct node *next;
}StackNode,*LinkStack;


void InitStack(LinkStack top)
{
	top->next = NULL;
}

int IsEmpty(LinkStack top)
{
	if(top ->next == NULL)
		return TRUE;
	return FALSE;
}

int Pop(LinkStack top,ElementType *element)
{
	if(IsEmpty(top))
	{
		return FALSE;
	}
	StackNode *temp = top ->next;
	*element = temp->dot;	
	top->next = temp->next;
	free(temp);

	return TRUE;
}

int Push(LinkStack top,int x,int y)
{
	StackNode *temp;
	temp = (StackNode *)malloc(sizeof(StackNode));
	if(temp == NULL) 
		return FALSE;
	temp->dot.edge_from = x;
	temp->dot.edge_to= y;
	temp->next = top->next;
	top->next = temp;
	return TRUE;
}

void GetTop(LinkStack top,ElementType *elemnet)
{
	*elemnet = top->next->dot;	
}