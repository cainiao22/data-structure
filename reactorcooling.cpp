#include <cstdio>
#include <cstring>
#include <cmath>
#include "common.h"

using namespace std;

/**
 *  核反应堆的冷却系统
 *
 *  有上下界的可行流问题
 */

namespace reactor_cooling {

struct ArcType {
    int b,c,f;
    int no;
};

ArcType Edge[NMAX + 2][NMAX + 2];
ArcType AccEdge[NMAX + 2][NMAX + 2];

int N, M;

int flag[NMAX + 2];
int pre[NMAX + 2];
int alpha[NMAX + 2];

int queue[NMAX + 2];

int qe, qt, v;

int compare(const void* a1, const void* a2){
    return ((ArcType*)a1)->no - ((ArcType*)a2)->no;
}


void ford(ArcType network[][NMAX+2], int s, int t)
{
    while(1)
    {
        memset(pre, -1, sizeof(pre));
        memset(flag, -1, sizeof(flag));
        //最后判断alpha[t]的可改进量用
        memset(alpha, -1, sizeof(alpha));

        qe = qt = 0;
        queue[qt ++] = s;

        while(qe < qt)
        {
            v = queue[qe ++];
            for(int i=0; i<N; i++)
            {
                if(flag[i] == -1)
                {
                    if(network[v][i].c < INF && network[v][i].f < network[v][i].c)
                    {
                        alpha[i] = MIN(alpha[v], network[v][i].c - network[v][i].f);
                        pre[i] = v;
                        flag[i] = 0;
                        queue[qt ++] = i;
                    }
                    else if(network[i][v].f < INF)
                    {
                        alpha[i] = MIN(alpha[v], network[i][v].f - network[i][v].b);
                        pre[i] = -v;
                        flag[i] = 0;
                        queue[qt ++] = i;
                    }
                }
            }
        }

        if(flag[t] == -1 || alpha[t] <= 0)
        {
            break;
        }

        int k1 = t, k2 = abs(pre[t]);
        int min = alpha[t];
        while(1)
        {
            if(Edge[k2][k1].c < INF)
            {
                Edge[k2][k1].f += min;
            }
            else
            {
                Edge[k1][k2].f -= min;
            }
            if(k2 == s) break;
            k1 = k2;
            k2 = abs(pre[k1]);
        }
    }
}

void readcase()
{
    int u, v, b, c;
    scanf("%d%d", &N, &M);
    for(int i=0; i<=N+1; i++)
    {
        for(int j=0; j<=N+1; j++)
        {
            Edge[i][j].c = Edge[i][j].f = Edge[i][j].b = Edge[i][j].no = INF;
        }
    }

    for(int i=1; i<=M; i++)
    {
        scanf("%d%d%d%d", &u, &v, &b, &c);
        Edge[u][v].b = b;
        Edge[u][v].c = c;
        Edge[u][v].f = 0;
        Edge[u][v].no = i;
    }
    
}

void accompany()
{
    memcpy(AccEdge, Edge, sizeof(Edge));
    for(int i=1; i<=N; i++)
    {
        int sumA = 0, sumB = 0;
        for(int j=1; j<=N; j++)
        {
            if(Edge[i][j].b < INF)
            {
                sumA += Edge[i][j].b;
            }
            if(Edge[j][i].b < INF)
            {
                sumB += Edge[j][i].b;
            }
        }

        if(sumA > sumB)
        {
            AccEdge[i][N+1].c = sumA - sumB;
            AccEdge[i][N+1].b = 0;
        }
        else
        {
            AccEdge[0][i].c = sumB - sumA;
            AccEdge[0][i].b = 0;
        }
    }

    for(int i=1; i<=N; i++)
    {
        for(int j=1; j<=N; j++)
        {
            if(Edge[i][j].c < INF)
            {
                AccEdge[i][j].c = Edge[i][j].c - Edge[i][j].b;
                AccEdge[i][j].b = 0;
            }
        }
    }

    //求伴随网络的最大流
    ford(AccEdge, 0, N+1);

    bool fesiable = 1;
    for(int i=1; i<=N+1; i++)
    {
        if(AccEdge[0][i].c != INF && AccEdge[0][i].f != AccEdge[0][i].c)
        {
            fesiable = 0;
            break;
        }
    }

    if(fesiable == 0)
    {
        printf("no rules");
        return;
    }

    for(int i=1; i<=N; i++)
    {
        for(int j=1; j<=N; j++)
        {
            Edge[i][j].f = AccEdge[i][j].f + Edge[i][j].b;
        }
    }
    
    
}



}
