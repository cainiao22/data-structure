#include <cstdio>
#include <cstdlib>
#include <cstring>

using namespace std;

/**
 * 普里姆算法求解最小生成树
 **/

namespace prim {



//无穷大
#define INF 0x7fffff

//顶点的最大数量
#define MAXN 100

int n, m; //顶点个数、边的个数

int Edge[MAXN][MAXN]; //邻接矩阵

int lowcost[MAXN];
int nearvex[MAXN];


void prim(int u)
{
    int i, j;
    int sumcost = 0;
    for(i=1; i<=n; i++)
    {
        lowcost[i] = Edge[u][i];
        nearvex[i] = u;
    }
    //初始情况下u就是那个初始集合T
    nearvex[u] = -1;

    for(i = 1; i<=n; i++)
    {
        int min = INF;
        int v = -1;
        for(j = 1; j<=n; j++)
        {
            if(nearvex[j] != -1 && lowcost[j] < INF)
            {
                min = lowcost[j];
                v = j;
            }
        }

        if(v != -1)
        {
            printf("%d,%d,%d\n", nearvex[v] , v, lowcost[v]);
        }
        sumcost += lowcost[v];
        nearvex[v] = -1;
        for(j = 1; j<=n; j++)
        {
            if(nearvex[j] != -1 && Edge[v][j] < lowcost[j])
            {
                nearvex[j] = v;
                lowcost[j] = Edge[v][j];
            }
        }
    }
}

int testPrim()
{
    scanf("%d, %d", &m, &n);

}

}
