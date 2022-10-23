#include <stdio.h>
#include <stdlib.h>
#define MAX 5000

void Init(int c[][21], int P[], int T[], int n);
void Out(int P[], int cost, int n);
int reducedMatrix(int c[][21], int n);
void dist(int c[][21], int **r, int **s, int n);
int min1(int c[][21], int i, int d, int n);
int min2(int c[][21], int j, int d, int n);
void unsub(int c[][21], int P[], int T[], int r, int s, int n);
int TSP(int c[][21], int P[], int T[], int *r, int *s, int *cost, int n, int k);

int main()
{
	int n;
	int r=0, s=0;
	int cost=0;
	system("COLOR E4");
    printf("***********************************************************************\n");
    printf("                  Dai hoc Bach Khoa - Dai hoc Da Nang                  \n");
    printf("                       Khoa Cong nghe thong tin                        \n");
	printf("                _______________________________________                \n");
	printf("*                   PBL1:DO AN LAP TRINH TINH TOAN                    *\n");
	printf("*                    DE TAI:Bai toan Nguoi du lich                    *\n");
	printf("*   Sinh vien thuc hien:	             Giang vien huong dan:    *\n");
	printf("*   +Tran Thi Kim Quy	                    + Nguyen Van Nguyen       *\n");
	printf("*   +Tran Thi My Linh                                                 *\n");
	printf("***********************************************************************\n");
	printf("-----------------------------------------------------------------------\n");
	printf("*                        ~~~~~~~~~~~~~~~~~~~~~~                       *\n");
	printf("                     KET QUA THUC HIEN CHUONG TRINH                    \n");
	printf("\n");
	freopen("intest2.txt", "r", stdin);
	printf("Nhap so thanh pho: ");
	scanf("%d", &n);
	printf(" %d\n", n);
	int c[21][21], P[n+1], T[n+1];
	for(int i=1; i<=n; i++)
	{
	   for(int j=1; j<=n; j++) 
	   {
	      scanf("%d ", &c[i][j]);
	      if (i==j) c[i][j]=MAX;
	      printf("%8d", c[i][j]);
	   }
	   printf("\n");
    }
    int a=1;
    for(int i=1; i<=n; i++)
    {
	    for(a=1;a<=n;a++)
        {
    	  if (c[i][a]<0) 
		  {
		  printf("input bi loi");
    	  return 0;
    	  }
	    }
    }
	Init(c,P,T,n);
	TSP(c,P,T,&r,&s,&cost,n,n);
	return 0;
}

void Init(int c[][21], int P[], int T[], int n)
{
	for (int i=1; i<=n; i++)
	{
	   P[i]=T[i]=0;
    }
}

void Out(int P[], int cost, int n)
{
	int i=1;
	printf("Hanh trinh: ");
	printf("1 -> ");
	while (P[i]!=1)
	{
		printf("%d -> ", P[i]);
		i=P[i];
	}
	printf("1");
	printf("\nTong chi phi min cua hanh trinh: %d", cost);
}

int min1(int c[][21], int i, int d, int n)
{
	int min=MAX;
	for (int k=1; k<=n; k++)
	if ((c[i][k]<min) && (k!=d)) min=c[i][k];
	return min;
}

int min2(int c[][21], int j, int d, int n)
{
	int min=MAX;
	for (int k=1; k<=n; k++)
	if ((c[k][j]<min) && (k!=d)) min=c[k][j];
	return min;
}

int reducedMatrix(int c[][21], int n)
{
	printf("\nBat dau xet\n");
	int sum = 0, d = 0;
	for (int i=1; i<=n; i++)
	{
		int m = min1(c,i,d,n);
		if ((m>0) && (m!=MAX))
		{
			for (int j=1; j<=n; j++) 
			if (c[i][j]!=MAX) c[i][j]=c[i][j]-m;
			sum+=m;
		}		
	}
    printf("\n");
	for (int i=1; i<=n; i++)
	{
	    for (int j=1; j<=n; j++)
		printf("%8d", c[i][j]);
		printf("\n");
    }
	for (int j=1; j<=n; j++)
	{
		int m = min2(c,j,d,n);
		if ((m>0) && (m!=MAX))
		{
			for (int i=1; i<=n; i++) 
			if (c[i][j]!=MAX) c[i][j]=c[i][j]-m;
			sum+=m;
		}
	}
	printf("\n");
	for (int i=1; i<=n; i++)
	{
	    for (int j=1; j<=n; j++)
		printf("%8d", c[i][j]);
		printf("\n");
    }
    printf("\n sum =%d",sum);
	return sum;
}

void dist(int c[][21], int **r, int **s, int n)
{
	int beta = -MAX;
	for (int i=1; i<=n; i++)
	for (int j=1; j<=n; j++)
	if(c[i][j]==0)
	{
		int total = min1(c,i,j,n) + min2(c,j,i,n);
		if (total>beta) 
		{
			beta = total;
			**r = i;
			**s = j;
		}
	}
	printf("\nr=%d, s=%d",**r, **s);
}

void unsub(int c[][21], int P[], int T[], int r, int s, int n)
{
	P[r] = s;
	T[r] = s;
	for(int j=1; j<=n; j++)
	{
		c[r][j] = MAX;
		c[j][P[r]] = MAX;
	}
	for (int i=1; i<=n; i++)
	{
		if ((i==T[r]) && (T[i]!=0)) 
		{
		    T[r]=T[i];
		    T[i]=0;
		}
		if (T[i]==r) 
		{
			T[i] = T[r];
			T[r]=0;
			r = i;
		}
	}
	c[T[r]][r] = MAX;
	printf("\nsau khi unsub\n");
	for (int i=1; i<=n; i++)
	{
	    for (int j=1; j<=n; j++)
		printf("%8d", c[i][j]);
		printf("\n");
    }
}

int TSP(int c[][21], int P[], int T[], int *r, int *s, int *cost, int n, int k)
{
	*cost+=reducedMatrix(c,n);
	if (k==2)
	{
		for(int i=1; i<=n; i++)
		if (P[i]==0)
		for(int j=1; j<=n; j++)
		if (c[i][j]==0) P[i]=j;
		Out(P,*cost,n);
	}
	else
	{
		dist(c, &r, &s, n);
		unsub(c, P, T, *r, *s, n);
		TSP(c,P,T,r,s,cost,n,k-1);
		
	}
	return 0;
}
