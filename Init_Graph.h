#define INACCESS 10000
void Init_data(int *graph,int n)
{
	int i,j;
	for(i = 0;i < n;i++)
	{
		for(j = 0;j < n;j++)
		{
			if(i == j)
			{
				*(graph + i*n +j) = INACCESS;
			}
			else
			{
				*(graph + i*n +j) = 1 + rand()%100;				
			}
		}
	}
}

//void Init_data(int *graph,int n)
//{
//	*(graph) = 10000;
//	*(graph + 1) = 5;
//	*(graph + 2) = 61;
//	*(graph + 3) = 34;
//	*(graph + 4) = 12;
//	*(graph + 5) = 57;
//	*(graph + 6) = 10000;
//	*(graph + 7) = 43;
//	*(graph + 8) = 20;
//	*(graph + 9) = 7;
//	*(graph + 10) = 39;
//	*(graph + 11) = 42;
//	*(graph + 12) = 10000;
//	*(graph + 13) = 8;
//	*(graph + 14) = 21;
//	*(graph + 15) = 6;
//	*(graph + 16) = 50;
//	*(graph + 17) = 42;
//	*(graph + 18) = 10000;
//	*(graph + 19) = 8;
//	*(graph + 20) = 41;
//	*(graph + 21) = 26;
//	*(graph + 22) = 10;
//	*(graph + 23) = 35;
//	*(graph + 24) = 10000;
//}
