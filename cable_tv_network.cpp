#include <cstdio>
#include <cstdlib>
#include <cstring>

#include "common.h"

using namespace std;

/**
 *  求解无向图的连通度 POJ 1966
 *
 */

namespace cable_tv_network {

//顶点数量和边的数量
int N, M;

//图
int map[NMAX][NMAX];


int max_flow(int num, int map[][NMAX], int source, int sink)
{
    int queue[NMAX], qe = 0, qt = 0;
    int pre[NMAX];
    int flow[NMAX][NMAX];
    int min_flow[NMAX];
    while(1)
    {
        qe = qt  = 0;
        queue[qt ++] = source;
        memset(pre, -1, sizeof(pre));
        pre[source] = -1;
        while(qe < qt)
        {
            int cur = queue[qe ++];
            for(int i=0; i<num; i++)
            {
                if(pre[i] == -1 && flow[cur][i] < map[cur][i])
                {
                   min_flow[i] = MIN(min_flow[cur], map[cur][i] - flow[cur][i]);
                   pre[i] = cur;
                   queue[tail ++] = i;
                }
            }

            if(pre[sink] != -1)
            {
                int k = sink;
                while(pre[k] != -1)
                {
                    flow[pre[k]][k] += min_flow[k];
                    flow[k][pre[k]] -= min_flow[k];
                    k = pre[k];
                }

                break;
            }
        }

        if(pre[sink] == -1) return ans;
        ans += min_flow[sink];
    }

    return 0;
}

int run()
{
    int a, b;
    while(scanf("%d%d", &N, &M) != EOF)
    {
        memset(map, 0, sizeof(map));
        //将原来的顶点分为两部分v'和v";增加边e(v',v")容量为1
        for(int i=0; i<N; i++)
        {
            map[i][i+N] = 1;
        }

        for(int i=0; i<M; i++)
        {
            scanf("%d%d", &a, &b);
            map[a+N][b] = map[b+N][a] = INF;
        }

        int ans = N;
        for(int i=1; i<=N; i++)
        {
            ans = MIN(ans, max_flow(N*2, map, 0+N, i));
        }

        printf("%d\n", ans);
    }
}

}
