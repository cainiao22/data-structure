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

        while(qs < qe && pre[t] == -2)
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
            flow[u][v] += alpha[u];
            flow[v][u] -= alpha[u];
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




/**
 *  另一种求解方式
 */
namespace drainage_ditches_2 {

#define MAXN 100

struct Matrix
{
    int c, f;
};

Matrix Edge[MAXN][MAXN];
int residual[MAXN][MAXN];


int queue[MAXN * MAXN];

int qs, qe;

int pre[MAXN];
int vis[MAXN];

//源点和汇点
int s, t;

int m, n;

int maxFlow, min_argument;


void find_min_argument_path()
{
    qs = qe = 0;
    queue[qe ++] = s;

    memset(pre, -1, sizeof(pre));
    memset(vis, 0, sizeof(vis));

    while(qs < qe && vis[t] == 0)
    {
        int u = queue[qs ++];
        for(int i=0; i<n; i++)
        {
            if(vis[i] == 0)
            {
                if(Edge[u][i].c < INF && Edge[u][i].f < Edge[u][i].c)
                {
                    residual[u][i] = Edge[u][i].c - Edge[u][i].f;
                    queue[qe ++] = i;
                    pre[i] = u;
                }
                else if(Edge[i][u].f > 0)
                {
                    residual[i][u] = Edge[i][u].f;
                    queue[qe ++] = i;
                    //因为pre不是最终的路径结果，只是根据pre去优化网络路线
                    //也就是flow[u][i] + minflow 而flow[i][u]-minflow
                    pre[i] = u;
                }

            }
        }
    }
}


void find_min_argument()
{
    int i = t;
    if(pre[i] == -1)
    {
        min_argument = 0;
        return;
    }
    int j = INF;
    while(i != s)
    {
        if(residual[pre[i]][i] < j)
            j = residual[pre[i]][i];

        i = pre[i];
    }

    min_argument = j;
}



void update_flow()
{
    int i = t;
    if(pre[i] == -1) return;
    while(i != s)
    {
        if(Edge[pre[i]][i].c > Edge[pre[i]][i].f)
        {
            Edge[pre[i]][i].f += min_argument;
        }else if(Edge[i][pre[i]].f > 0)
        {
            Edge[i][pre[i]].f -= min_argument;
        }

        i = pre[i];
    }
}



}
