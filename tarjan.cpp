#include <cstdio>
#include <cstdlib>
#include <cstring>
#include "common.h"

using namespace std;

/**
 *  求解重连通分量
 *
 */

namespace tarjan {

struct Edge {
    int u, v;
    void output()
    {
        printf("%d-%d\n", &u, &v);
    }

    int cmp(Edge t)
    {
        return (u == t.u && v == t.v) || (u == t.v && v == t.u);
    }
};

//顶点数目、边的数目
int n, m;

//栈
Edge queue[MMAX];

int se;

// 0 代表没有连接 1代表有连接但是没访问 2代表有连接已访问
int edge[NMAX][NMAX];

int dfn[NMAX];
int low[NMAX];
int subnets[NMAX];
int visited[NMAX];

int tmpdfn = 0;

void dfs(int u)
{
    for(int v = 1; v<=n; v ++)
    {
        if(edge[u][v] == 1)
        {
            Edge e;
            e.u = u;
            e.v = v;
            edge[se ++] = e;
            edge[u][v] = 2;
            if(!visited[v])
            {
                visited[v] = 1;
                tmpdfn ++;
                dfn[v] = low[v] = tmpdfn;
                dfs(v);
                low[u] = MIN(low[u], low[v]);
                //走到这里说明u是一个桥。以他为根的那个路径必然也是一个连通分量
                if(low[v] >= dfn[u])
                {
                    while(1)
                    {
                        Edge t = edge[se --];
                        t.output();
                        if(se == -1) break;
                        if(t.cmp(e)) break;
                    }
                }
            }
            else
            {
                low[u] = MIN(low[u], dfn[v]);
            }
        }
    }
}

}
