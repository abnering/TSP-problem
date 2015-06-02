int ROW_min(int *graph,int row,int n)
{
	int i;
	int ROW_MIN = INACCESS;
	for(i = 0;i < n;i++)
	{
		if(ROW_MIN > *(graph + row*n + i))
		{
			ROW_MIN = *(graph + row*n + i);
		}
	}
	if(ROW_MIN == INACCESS)
	{
		return 0;
	}
	else
	{
	    return ROW_MIN;
	}
}


int COL_min(int *graph,int col,int n)
{
	int i;
	int Flag = 1;
	int COL_MIN = INACCESS;
	for(i = 0;i < n;i++)
	{
		if(COL_MIN > *(graph + i*n + col))
		{
			COL_MIN = *(graph + i*n + col);
		}
	}
	if(INACCESS == COL_MIN)
	{
		return 0;
	}
	else
	{
		return COL_MIN;
	}
}


int RC_have_Zero(int *graph,int n)
{
	int ROW_MIN,COL_MIN;
	int i,j;
	int min_bound = 0;
	//handle ROW
	for(i = 0;i < n;i++)
	{
		ROW_MIN = ROW_min(graph,i,n);
		//printf("%d\n",ROW_MIN);
		min_bound = min_bound + ROW_MIN;
		for(j = 0;j < n;j++)
		{
			if(*(graph + i*n +j) == INACCESS)
			{
				continue;
			}
			else
			{
			    *(graph + i*n +j) = *(graph + i*n +j) - ROW_MIN;
			}
		}
	}

	//handle COL
	for(j = 0;j < n;j++)
	{
		COL_MIN = COL_min(graph,j,n);
		//printf("%d\n",COL_MIN);
		min_bound = min_bound + COL_MIN;
		for(i = 0;i < n;i++)
		{
			if(*(graph + i*n +j) == INACCESS)
			{
				continue;
			}
			else
			{
			    *(graph + i*n +j) = *(graph + i*n +j) - COL_MIN;
			}
		}
	}
	return min_bound;
}