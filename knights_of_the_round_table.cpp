#include <cstdio>
#include <cstdlib>
#include <cstring>

#include "common.h"

using namespace std;

/**
 *  圆桌武士  POJ2942
 */

namespace knights_of_the_round_table {

struct Edge {
    //节点属于哪个联通分量
    int belongto;
    //对于关节点很有可能属于多个连通分量，next指向的是下一个连通分量
    Edge *next;

    Edge(int u, int v):belongto(v), next(P[u]){}
} *P[NMAX];

//part 代表第i个节点在某个联通分量中是否启用
int G[NMAX][NMAX], used[NMAX], part[NMAX],deep[NMAX], anc[NMAX], open[NMAX], color[NMAX];

//num 连通分量的个数
int n, m, num, top;

void readData()
{
    int a, b;
    for(int i=0; i<m; i++)
    {
        scanf("%d%d", &a, &b);
        G[a][b] = 1;
    }
    for(int i=1; i<=n; i++)
    {
        G[i][i] = 1;
    }

    for(int i=1; i<=n; i++)
    {
        for(int j=1; j<=n; j++)
        {
            G[0][i] = G[i][j];
        }

        //将邻接矩阵结构变为了邻接表的形式
        for(int j=1; j<=n; j++)
        {
            if(!G[0][j])
            {
                G[i][++G[i][0]] = j;
            }
        }
    }
}

void DFS(int s, int father, int d)
{
    anc[s] = deep[s] = d;
    used[s] = 1;
    open[top ++] = s;
    //G[s][0]存放总数。具体值从1开始
    for(int i=1; i<=G[s][0]; i++)
    {
        int j = G[s][i];
        //找到了一条回路
        if(used[j] == 1 && j != father)
        {
            anc[s] = MIN(anc[s], deep[father]);
        }
        else if(used[j] == 0)
        {
            DFS(j, s, d+1);
            anc[s] = MIN(anc[s], anc[j]);
        }
        /**
          *
          * 下面这段if判断可以放到used[j]==0的elseif里面。提高性能。因为如果走上面的第一个if代表子节点可以不通过它达到它的祖先，该节点一定不是关键节点
          **/
        //关节点
        if(anc[j] >= deep[s])
        {
            num ++;
            P[s] = new Edge(s, num);
            //链表头插法  将第num个连通分量与它的组成节点关联起来
            for(int k=open[top]; k!=j; P[k] = new Edge(k, num))
            {
                k = open[--top];
            }
        }
    }
    //可加可不加
    used[s] = 2;
}

bool OddCycle(int s, int color)
{
    
}

int Calculate()
{
    int count = 0;
    memset(used, 0, sizeof(used));
    for(int i=1; i<=num; i++)
    {
        memset(part, 0, sizeof(part));
        for(int j=1; j<=n; j++)
        {
            for(Edge* e = P[j]; e; e = e->next)
            {
                if(e->belongto == i)
                {
                    part[j] = 1;
                    break;
                }
            }
        }

        //每个节点都要做一次染色处理
        for(int j=1; j<=n; j++)
        {
            if(part[j])
            {

            }
        }
    }
}

}
