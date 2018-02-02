#include <cstdio>
#include <cstdlib>
#include <cstring>

#include "common.h"

using namespace std;


namespace drainage_ditches {


//排水沟数量 相当于弧
#define M 5
//节点数量
#define N 5


#define INF 0x7fffffff

//邻接矩阵 沟的数量加上 s和t
int Edge[N + 2][N + 2];
int flow[N + 2][N + 2];

int m, n;

int alpha[N + 2];

int pre[N + 2];

void init()
{
    //排水沟的起始点、终点、容量
    int u, v, c;
    scanf("%d %d", &m, &n);
    memset(Edge, 0, sizeof(Edge));
    memset(pre, -2, sizeof(pre));
    for(int i=0; i<m; i++)
    {
        scanf("%d %d %d", &u, &v, &c);
        Edge[u][v] = c;
    }
}



int resolve()
{
    int queue[N];
    int t = n + 1;
    while(1)
    {
        int qs = 0, qe = 0;
        queue[qe ++] = 0;
        pre[0] = -1;
        alpha[0] = INF;

        while(qs < qe && pre[t] = -2)
        {
            int u = queue[qs];
            for(int i=1; i<=t; i++)
            {
                if(pre[i] == -2 && Edge[u][i] - flow[u][i] > 0)
                {
                    alpha[i] = MIN(alpha[u], Edge[u][i] - flow[u][i]);
                    pre[i] = u;
                    queue[qe ++] = i;
                }
            }
        }

        if(pre[t] == -2) break;
        int v = t, u = pre[t];
        while(u != -1)
        {
            flow[u][v] += alpha[u][v];
            flow[v][u] -= alpha[u][v];
        }
    }

    int sum = 0;
    for(int i=0; i<= t; i++)
    {
        sum += flow[i][t];
    }

    return sum;
}

}
