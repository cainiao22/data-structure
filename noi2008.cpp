#include <cstdio>
#include <cstdlib>
#include <cstring>

#include "common.h"

using namespace std;

/**
 * 志愿者招募 最小费用最大流问题
 *
 *
 */

//TODO 未完成。最小费用最大流
namespace zhiyuanzhezhaomu {

struct Edge
{
    //op 是对面 opposite
    Edge *next, *op;
    int t, c, v;
} ES[MMAX], *V[MMAX];


struct Queue
{
    int Q[NMAX], QH, QL, Size;
    bool inq[NMAX];

    void ins(int v)
    {
        if(++QL >= NMAX)
        {
            QL = 0;
        }
        Q[QL] = v;
        inq[QL] = true;
        Size ++;
    }

    int pop()
    {
        int r = Q[QH];
        inq[QH] = false;
        if(++QH >= NMAX)
        {
            QH = 0;
        }
        Size --;
        return r;
    }

    void reset()
    {
        memset(Q, 0, sizeof(Q));
        QH = Size = 0;
        QL = -1;
    }
} Q;

/**
 * @brief N 项目完成需要的天数
 * @brief M 志愿者的种类
 *
 **/
int N, M, S, T, EC = -1;
/**
 * @brief demond  每天至少需要多少人
 * @brief pre
 */
int demond[NMAX], pre[NMAX], sp[NMAX];

Edge *path[NMAX];

void addEdge(int a, int b, int v, int c = INF)
{
    Edge e1 = {V[a], 0, b, c, v}, e2 = {V[b], 0, a, c, -v};
    ES[++EC] = e1;  V[a] = &ES[EC];
    ES[++EC] = e2;  V[b] = &ES[EC];
    V[a]->op = V[b];
    V[b]->op = V[a];
}

void init()
{
    int i, a, b, c;

    scanf("%d%d", &N, &M);
    for(i=0; i<N; i++)
    {
        scanf("%d", &demond[i]);
    }

    for(i=0; i<M; i++)
    {
        scanf("%d%d%d", &a, &b, &c);
        //顶点a到顶点b+1的费用为c
        addEdge(a, b + 1, c);
    }

    S = 0;
    T = N + 2;
    for(i=1; i<=N+1; i++)
    {
        c = demond[i] - demond[i-1];
        if(c > 0)
        {
            addEdge(S, i, c);
        }else
        {
            addEdge(i, T, -c);
        }
        if(i > 1)
        {
            addEdge(i, i-1, 0);
        }
    }
}

bool SPFA()
{
    int u, v;
    for(u=S; u<=T; u++)
    {
        sp[u] = INF;
    }
    Q.reset();
    Q.ins(S);
    pre[S] = -1;
    sp[S] = 0;

    while(Q.Size)
    {
        u = Q.pop();
        for(Edge* k = V[u]; k; k = k->next)
        {
            v = k->t;
            if(k->c > 0 && sp[u] + k->v < sp[v])
            {
                sp[v] = sp[u] + k->v;
                path[u] = k;
                pre[k] = u;
                if(!Q.inq[k])
                {
                    Q.ins(k);
                }
            }
        }

    }
    return sp[T] != INF;
}

int argument()
{
    int i, cost = INF, flow = 0;
    Edge* e;
    for(i=T; pre[i] != -1; i = pre[i])
    {
        e = path[i];
        if(e->c < cost)
        {
            cost = e->c;
        }
    }

    for(i = T; pre[i] != -1; i = pre[i])
    {
        e = path[i];
        e->c -= cost;
        e->op->c += cost;
        flow += e->v * cost;
    }

    return flow;
}

int maxFlow()
{
    init();
    int flow = 0;
    while(SPFA())
    {
        flow += argument();
    }

    return flow;
}

}
