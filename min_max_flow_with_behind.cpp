#include <cstdio>
#include <cstring>
#include <cmath>

#include "common.h"

using namespace std;

namespace min_max_flow_with_be {

struct ArcType {
    int b, c, f;
} AccEdge[NMAX + 2][NMAX + 2], Edge[NMAX][NMAX + 2];



int pre[NMAX + 2];
int flag[NMAX + 2];
int alpha[NMAX + 2];
int queue[NMAX + 2];

int v;

int qs, qe;

int m, n;

void ford(ArcType network[][NMAX + 2], int s, int t, int max)
{
    while(1)
    {
        memset(flag, -1, sizeof(flag));
        memset(pre, -1, sizeof(pre));
        memset(alpha, -1, sizeof(alpha));
        qs = qe = 0;

        flag[s] = 0;
        alpha[s] = INF;

        queue[qe ++] = s;

        while(qs < qe && flag[t] == -1)
        {
            v = queue[qs ++];
            for(int i=s; i<t; i++)
            {
                if(flag[i] == -1)
                {
                    if(network[v][i].c < INF && network[v][i].f < network[v][i].c)
                    {
                        alpha[i] = MIN(alpha[v], network[v][i].c < network[v][i].f);
                        flag[i] = 1;
                        queue[qe ++] = i;
                        pre[i] = v;
                    }
                    else if(network[i][v].c < INF && network[i][v].f > network[i][v].b)
                    {
                        flag[i] = 0;
                        pre[i] = -v;
                        alpha[i] = MIN(alpha[i], network[i][v].f - network[i][v].b);
                        queue[qe ++] = i;
                    }
                }
            }

            flag[v] = 1;
        }

        if(flag[t] == -1 || alpha[t] == 0) break;
        int k1 = t, k2 = abs(pre[t]);
        int a = alpha[t];
        while(1)
        {
            if(network[k2][k1].c < INF)
            {
                network[k2][k1].f += a;
            }
            else
            {
                network[k1][k2].f -= a;
            }
            if(k2 == s) break;
            k1 = k2; k2 = abs(pre[k1]);
        }
    }

    int maxFlow = 0;
    for(int i=s; i<=t; i++)
    {
        for(int j=s; j<=t; j++)
        {
            if(i == s && network[i][j].f < INF)
            {
                maxFlow += network[i][j].f;
            }else if(i == s && network[j][i].f < INF)
            {
                maxFlow -= network[j][i].f;
            }
        }
    }
}

//构造伴随网络
void accompany()
{
    int s = 0, t= n+1;
    memcpy(AccEdge, Edge, sizeof(Edge));
    for(int i=1; i<=n; i++)
    {
        int sumA = 0, sumB = 0;
        for(int j=0; j<=n; j++)
        {
            //出流
            if(AccEdge[i][j].b < INF) sumA += AccEdge[i][j].b;
            //入流
            if(AccEdge[j][i].b < INF) sumB += AccEdge[j][i].b;
        }
        AccEdge[0][i].c = sumB;
        AccEdge[0][i].b = AccEdge[0][i].f = 0;
        AccEdge[i][n+1].c = sumA;
        AccEdge[i][n+1].b = AccEdge[i][n+1].f = 0;
    }

    for(int i=1; i<=n; i++)
    {
        for(int j=1; j<=n; j++)
        {
            if(AccEdge[i][j].c < INF)
            {
                AccEdge[i][j].c = AccEdge[i][j].c - AccEdge[i][j].b;
                AccEdge[i][j].b = 0;
            }
        }
    }
    AccEdge[s][t].b = 0;
    AccEdge[s][t].c = INF_LIMITED;

    AccEdge[t][s].b = 0;
    AccEdge[t][s].c = INF_LIMITED;

    ford(AccEdge, 0, n+1, -1);

    bool feasible = 1;
    for(int i=0; i<=n+1; i++)
    {
        if(AccEdge[0][i].c != INF && AccEdge[0][i].f != AccEdge[0][i].c)
        {
            feasible = 0;
            break;
        }
    }
    if(feasible == 0)
    {
        printf("%s\n", "there no available path");
        return;
    }

    for(int i=1; i<=n; i++)
    {
        for(int j=1; j<=n; j++)
        {
            if(Edge[i][j].c != INF)
            {
                Edge[i][j].f = AccEdge[i][j].f + Edge[i][j].b;
            }
        }
    }
    //求最大流
    ford(Edge, s, t, 0);

    //求最小流 先还原到可行流
    for(int i=1; i<=n; i++)
    {
        for(int j=1; j<=n; j++)
        {
            if(Edge[i][j].c != INF)
            {
                Edge[i][j].f = AccEdge[i][j].f + Edge[i][j].b;
            }
        }
    }

    //s和t调换位置
    int b, f, c;
    for(int i=1; i<=n; i++)
    {
        b = Edge[1][i].b;
        f = Edge[1][i].f;
        c = Edge[1][i].c;

        Edge[1][i].b = Edge[n][i].b;
        Edge[1][i].f = Edge[n][i].f;
        Edge[1][i].c = Edge[n][i].c;

        Edge[n][i].b = b;
        Edge[n][i].f = f;
        Edge[n][i].c = c;
    }

    ford(Edge, 1, n, 1);

}

}
