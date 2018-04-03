#include <cstdio>
#include <cstring>
#include "common.h"

using namespace std;

namespace friendship {

struct Node {
    int c, f;
} net[NMAX][NMAX];

int set[NMAX];

int n, s, t;

bool flag[NMAX];

int q[NMAX], dist[NMAX];

int qs, qe;

bool BFS()
{
    memset(flag, 0, sizeof(flag));
    q[0] = s;
    qs = 0;
    qe = 1;
    dist[s] = 0;
    while(qs < qe)
    {
        int u = q[qs ++];
        for(int i=0; i<n; i++)
        {
            if(net[u][i].c > net[u][v].f && !flag[i])
            {
                dist[i] = dist[u] + 1;
                q[qe] ++ = i;
                if(i == t)
                {
                    return true;
                }
            }
        }
    }

    return false;
}

//相当于从节点v流过来的量
int DFS(int v, int low)
{
    if(v == t) return low;
    int flow;
    for(int i=0; i<=t; i++)
    {
        if(net[v][i].c > net[v][i].f && dist[i] == dist[v] + 1)
        {
            if(flow = DFS(i, MIN(low, net[v][i].c - net[v][i].f)))
            {
                net[v][i].f += flow;
                net[i][v].f -= flow;
                return f;
            }
        }
    }

    return 0;
}

void dinic()
{
    while(BFS())
    {
        int ans;
        int flow ;
        while(flow = DFS(s, INF))
        {
            ans += flow;
        }
    }
}

}
