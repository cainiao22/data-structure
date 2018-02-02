#include<cstdlib>
#include<cstdio>
#include<cstring>
#include<queue>

using namespace std;

/**
 *
 * 奶牛party
 *
 **/

namespace slivercowparty {


#define INF 0x7fffffff
#define MAXM 1000
#define MAXN 1000


struct ArcNode {
    int u, v, w;
    ArcNode* next;
} edge[MAXN], redge[MAXN], temp[MAXN * 2];

int pos;

int ecost[MAXN];
int N, M, W, src, Q[MAXN];

bool visited[MAXN]; //标志数组代表该节点是否被访问

void SPFA(int direction)
{
    //h代表当前头节点在Q中的位置下标。h代表Q中元素的总数量
    int h, t, u, i;

    //当前遍历节点
    ArcNode* ptr;

    memset(visited, 0, sizeof(visited));
    for(int i=0; i<N; i++)
    {
        ecost[i] = INF;
    }

    Q[0] = src;
    ecost[src] = 0;
    h = 0;
    t = 1;
    while(h != t)
    {
        u = Q[h];
        h ++;
        if(direction)
            ptr = edge[u].next;
        else
            ptr = redge[u].next;

        while(ptr)
        {
            if(ecost[ptr->v] > ecost[u] + ptr->w)
            {
                if(!visited[ptr->v])
                {
                    Q[t] = ptr->v;
                    t ++;
                    visited[ptr->v] = true;
                }
                ecost[ptr->v] = ecost[u] + ptr->w;
            }
        }
    }

}

void insert(const int &x, const int &y, const int &w)
{
    ArcNode* ptr = &temp[pos ++];
    ptr->u = x;
    ptr->v = y;
    ptr->w = w;
    ptr->next = edge[x].next;
    edge[x].next = ptr;

    ptr = &temp[pos ++];
    ptr->u = y;
    ptr->v = x;
    ptr->w = w;
    ptr->next = redge[y].next;
    redge[y].next = ptr;
}

void run()
{
    int x, y, w;
    int ans[MAXN];
    while(scanf("%d, %d, %d", &N, &M, &src) !=EOF)
    {
        pos = 0;
        memset(ans, 0, sizeof(ans));
        for(int i=0; i<MAXN; i++)
        {
            edge[i].next = NULL;
            redge[i].next = NULL;
        }
        for(int i=0; i<M; i++)
        {
            scanf("%d, %d, %d", &x, &y, &w);
            insert(x, y, w);
        }

        SPFA(1);
        for(int i=0; i<N; i++)
        {
            //这里不用判断是不是也可以？因为ecost[src] = 0;
            if(i == src) continue;
            ans[i] += ecost[i];
        }
        SPFA(0);
        for(int i=0; i<N; i++)
        {
            ans[i] += ecost[i];
        }
    }
}


}
