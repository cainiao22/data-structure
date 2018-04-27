#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <vector>

#include "common.h"

using namespace std;

/**
 *
 * 破坏有向图  POJ2125
 * 最小点权覆盖问题
 */


namespace destory_the_graph {

struct Edge {
    int next, c, f, other;
} N;

vector<Edge> map[NMAX];
vector<int> level_map[NMAX];

vector<int> ans;

int q[NMAX], pre[NMAX];

void add(int u, int v, int c)
{
    N.next = v;
    N.c = c;
    N.other = map[v].size();
    N.f = 0;
    //存放的是N的副本
    map[u].push_back(N);

    N.next = u;
    N.c = 0;
    N.f = 0;
    N.other = map[u].size() - 1;

    map[v].push_back(N);
}

/**
 * @brief BFS 构建层次网络，给每个节点定义一个level值，如果流量可以从v到u.必须满足level_u = level_v - 1
 */
void BFS()
{
    int head = 0, tail = 0, cur, i;
    for(i=0; i<NMAX; i++)
    {
        level_map[i].clear();
    }
    memset(level, -1, sizeof(level));
    q[tail ++] = s;
    level[s] = 0;
    while (head < tail) {
        cur = q[head];
        for(i=0; i<map[cur].size(); i++)
        {
            N = map[cur][i];
            if(N.c > N.f)
            {
                if(level[N.next] == -1)
                {
                    level[N.next] = level[cur] + 1;
                    level_map[cur].push_back(i);
                }
            }
        }
    }

    return level[t] != -1;
}

int Dinic()
{
    int i, j, ans = 0, len;
    while(BFS())
    {
        memset(hash, 0, sizeof(hash));
        while(!hash[s])
        {
            d[s] = INF;
            pre[s] = -1;
            for(i= s; i != t && i != -1; i = j)
            {
                len = level_map[i].size();
                while(len && hash[level_map[i][len-1]])
                {
                    level_map[i].pop_back();
                    len --;
                }
                if(!len)
                {
                    hash[i] = 1;
                    j = pre[i];
                    continue;
                }

                j = map[i][level_map[i][len - 1]].next;
                pre[j] = i;
                d[j] = MIN(d[i], map[i][level_map[i][len - 1]].c - map[i][level_map[i][len - 1]].f);
            }

            if(i == t)
            {
               ans += d[t];
               while(i != s)
               {
                   j = pre[i];
                   len = level_map[j][level_map[j].size()-1];
                   map[j][len].f += d[t];
                   if( map[j][len].f == map[j][len].c ) level_map[j].pop_back();
                   map[i][map[j][len].other].f -= d[t];
                   i = j;
               }
            }
        }
    }

    return ans;
}

}
