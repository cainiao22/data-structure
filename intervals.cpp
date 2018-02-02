#include <cstdio>
#include <cstdlib>
#include <cstring>

using namespace std;


namespace intervals {



#define INF 0x7fffffff
#define MAXN 1000
#define MAXM 1000



struct e {
    int u, v, w;
} edges[MAXM];


//区间个数
int n;

//区间的最大最小值
int mn, mx;

int dist[MAXN];

//初始化函数
void init()
{
    for(int i=0; i<n; i++)
    {
        //差分约束。在这个不等式里面每个值都是小于0的
        dist[i] = 0;
    }

    mn = 1;
    mx = INF;
}

void bellman_ford()
{
    int i, t;
    int f = 1; //循环结束的标志，
    while(f)
    {
        f = 0;
        for(i=0; i<n; i++)
        {
            if(dist[edges[i].v] > dist[edges[i].u] + edges[i].w)
            {
                f = 1;
                dist[edges[i].v] = dist[edges[i].u] + edges[i].w;
            }
        }

        for(i=mn; i<mx; i++)
        {
            t = dist[i-1] + 1;
            if(dist[i] > t)
            {
                dist[i] = t;
                f = 1;
            }
        }

        for(i=mx; i>=mn; i--)
        {
            t = dist[i];
            if(dist[i-1] > t)
            {
                dist[i-1] = t;
                f = 1;
            }
        }
    }
}

void run()
{
    while(scanf("%d", &n))
    {
        int u, v, w;
        int i = 0;
        while(i < n)
        {
            scanf("%d, %d, %d", &u, &v, &w);
            edges[i].v = u - 1;
            edges[i].u = v;
            edges[i].w = -w;
            if(mn > u) mn = u;
            if(mx < v) mx = v;
        }

        bellman_ford();
        printf("%d", dist[mx] - dist[mn-1]);
    }
}

}
