#include <cstdio>
#include <cstdlib>
#include <cstring>

using namespace std;

/**
 *
 * 弗洛伊德算法 求解每个顶点到其他顶点最短路径
 *
 **/


namespace floyd {


#define INF 0x7fffffff
#define MAXN 1000
#define MAXM 1000


int u, v, w;

int n;

int Edge[MAXN][MAXN];
int A[MAXN][MAXN];
int path[MAXN][MAXN];


void floyd()
{
    int i, j, k;
    for(i=0; i<n; i++)
    {
        for(j=0; j<n; j++)
        {
            A[i][j] = Edge[i][j];
            if(A[i][j] != INF)
            {
                path[i][j] = i;
            }
            else
            {
               path[i][j] = -1;
            }
        }
    }

    //k代表i-j经过k是否可以缩短那段距离
    for(k=0; k<n; k++)
    {
        //代表从i到j的最短距离
        for(i=0; i<n; i++)
        {
            for(j=0; j<n; j++)
            {
                if(k == i || k == j) continue;
                if(A[i][k] + A[k][j] < A[i][j])
                {
                    A[i][j] = A[i][k] + A[k][j];
                    //A[k][j] k不一定是直接到达j的
                    path[i][j] = path[k][j];
                }
            }
        }
    }
}


void run()
{
    int i, j;
    int u, v, w;
    scanf("%d", &n);
    for(i=0; i<n; i++)
    {
        for(j=0; j<n; j++)
        {
            if(i == j)
                A[i][j] = 0;
            else
                A[i][j] = INF;
        }
    }

    while(scanf("%d, %d, %d", &u, &v, &w) != EOF)
    {
        Edge[u][v] = w;
    }

    floyd();
    char shortest[100];
    int k = 0;
    for(i=0; i<n; i++)
    {
       for(j=0; j<n; j++)
       {
           k = 0;
           if(i == j) continue;
           printf("%d->%d: %d", i, j, A[i][j]);
           memset(shortest, 0, sizeof(shortest));
           shortest[k] = j;
           while(path[i][shortest[k]] != i)
           {
               shortest[k++] = path[i][shortest[k-1]];
           }
           shortest[k] = i;

       }
    }

}


}
