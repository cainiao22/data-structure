#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>

#include "common.h"

using namespace std;


/**
 *
 * 卡卡的矩阵之旅  最小费用最大流问题
 *
 */

//TODO 未完成 最小费用最大流问题需要重看
namespace matrix_travels {

struct Edge {
    int next;
    int f, c, w;
}N, P;

vector<Edge> map[NMAX];
int s, t, n, k;

int queue[NMAX * 4];

int cost[NMAX];
int pre[NMAX];

bool SPFA()
{
    int i, cur, h = 0, t = 0;
    for(i=0; i<NMAX; i++)
    {
        cost[NMAX] = INF;
    }
    queue[t ++] = s;
    cost[s] = 0;
    pre[s] = -1;

    while(h < t)
    {
        cur = queue[h ++];
        for(i=0; i<map[cur].size(); i++)
        {
            N = map[cur][i];
            if(N.c > N.f && cost[N.next] > cost[cur] + N.w)
            {
                cost[N.next] = cost[cur] + N.w;
                pre[N.next] = cur;
                queue[t ++] = N.next;
            }
        }
    }

    return cost[t] != INF;

}

int argument()
{
    int i, cost = INF;
    for(i=t; pre[i] != -1; i = pre[i])
    {
        if(cost > cost[i])
        {
            cost = cost[i];
        }
    }


}

}
