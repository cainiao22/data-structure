#include <cstdio>
#include <cstring>
#include <deque>
#include "common.h"

using namespace std;


/**
 *  预留推进算法求解最大网络流
 */

namespace power_network {


int n, np, nc, m;

//残留网络
int resi[MAX][MAX];

deque<int> q;

//高度
int h[MAX];

//余留
int ef[MAX];

int s, t;

//顶点数量
int V;


void push_relabel()
{
    int i, j;
    int sum = 0;
    for(i=1; i<= V; i++)
        h[i] = 0;

    h[s] = V;
    ef[s] = INF;
    ef[t] = -INF;
    q.push_front(s);
    while(!q.empty())
    {
        int u = q.front();
        q.pop_front();
        for(i=1; i<= V; i++)
        {
            int p = MIN(resi[u][i], ef[u]);
            if(p > 0 && (u == s || h[u] - h[i] == 1))
            {
                ef[u] -= p;
                ef[i] += p;
                resi[u][i] -= p;
                resi[i][u] += p;
                if(i == t) sum += p;
                if(i != t && i != s)
                {
                    q.push_back(i);
                }
            }
        }

        if(ef[u] > 0 && u != s && u != t)
        {
            h[u] += 1;
            q.push_back(u);
        }
    }
}

}
