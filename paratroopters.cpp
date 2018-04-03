#include <cstdio>
#include <cstring>
#include <cmath>
#include "common.h"

using namespace std;


/**
 *
 * 伞兵  最小割定理
 *
 *  乘法转加法 loga + logb = log(a*b)
 *
 **/

namespace paratroopters {


struct Node {
    int c, f;
} map[NMAX][NMAX];

int pre[NMAX];
int queue[NMAX];

int s, t;


bool BFS()
{
    int qs, qe, i, j, cur;
    memset(pre, -1, sizeof(pre));
    qs = 0;
    qe = 1;
    queue[qs] = s;

    while(qs < qe)
    {
        cur = queue[qs ++];
        for(i=0; i<NMAX; i++)
        {
            if(pre[i] == -1 && map[cur][i].c > map[cur][i].f)
            {
                queue[qe ++] = i;
                pre[i] = cur;
                if(i == t) return 1;
            }
        }
    }

    return 0;
}

int max_flow()
{
   double maxFlow = 0, min = INF;

   while(BFS())
   {
       for(int i=t; i!=s; i=pre[i])
       {
           min = MIN(min, map[pre[i]][i].c - map[pre[i]][i].f);
       }

       for(int i=t; i!=s; i=pre[i])
       {
           map[pre[i]][i].f += min;
           map[i][pre[i]].f -= min;
       }
       maxFlow += min;
   }

   return maxFlow;

}

int run()
{
    //n行 m列 l个伞兵
    int i, j, n, m, w, l, c, cc;
    scanf("%d", &w);
    while(w --)
    {
        memset(map, 0, sizeof(map));
        scanf("%d%d%d", &m, &n, &l);
        s = 0;
        t = m + n + 1;

        for(i=1; i<=n; i++)
        {
            scanf("%lf", &c);
            map[s][i] = log(c);
        }

        for(i=1; i<=m; i++)
        {
            scanf("%lf", &c);
            map[i+n][t] = log(c);
        }

        for(i=1; i<=l; i++)
        {
            scanf("%d%d", &c, &cc);
            map[c][n + cc] = INF;
        }

        printf("%.4f", max_flow());
    }
}

}
