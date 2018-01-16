#include<cstdlib>
#include<cstdio>
#include<cstring>

using namespace std;

/**
 *
 * 贝尔曼福德求解单源最短路径，思想类似于kruskal算法
 *
 **/


namespace bellman_ford {



#define INF 0x7fffffff
#define MAXN 100

int Edge[MAXN][MAXN];

int n; //顶点个数
int m; //边的个数

int dist[MAXN]; //最多经历u个顶点可得到的最短距离
int path[MAXN];

void bellman_ford(int v0)
{
    int i, j, k, u;
    for(i=0; i<n; i++)
    {
        //这就相当于经历一个顶点
        dist[i] = Edge[v0][i];
        if(dist[i] != INF)
        {
            path[i] = v0;
        }
    }
    dist[v0] = 0;
    path[v0] = -1;

    //经历2个顶点到经历n-1个顶点
    for(i=2; i<n; i++)
    {
        //到该顶点的距离是否可以缩短
        for(j=0; j<n; j++)
        {
            for(k=0; k<n; k++)
            {
                if(Edge[k][j] != INF && Edge[k][j] + dist[k] < dist[j])
                {
                    dist[j] = Edge[k][j] + dist[k];
                    path[j] = k;
                }
            }
        }
    }

}

void run()
{
    int i, j, k;
    int u, v, w;
    scanf("%d", &n);
    while(1)
    {
        scanf("%d, %d, %d", &u, &v, &w);
        if(u == -1 || v == -1)
        {
            break;
        }
        Edge[u-1][v-1] = w;
    }
    bellman_ford(0);

    int shortest[MAXN];
    for(i=1; i<n; i++)
    {
        printf("%d\t", dist[i]);
        int k = 0;
        memset(shortest, 0, sizeof(shortest));
        shortest[k] = i;
        while(path[shortest[k]] != -1)
        {
            shortest[++k] = path[shortest[k-1]];
        }
        for(j=k; j>=0; j--)
        {
            printf("%d->", shortest[j]);
        }
    }

}

struct PEdge {
    int u, v, w;
} edges[MAXN];

void bellman_ford2(int v0)
{
    int i, j, k, u;
    for(i=0; i<n; i++)
    {
        //这就相当于经历一个顶点
        dist[i] = Edge[v0][i];
        if(dist[i] != INF)
        {
            path[i] = v0;
        }
    }
    dist[v0] = 0;
    path[v0] = -1;

    //经历2个顶点到经历n-1个顶点
    for(i=2; i<n; i++)
    {
        for(j=0; j<m; j++)
        {
            if(edges[j].w + dist[edges[j].u] < dist[edges[j].v])
            {
                dist[edges[j].v] = edges[j].w + dist[edges[j].u];
                path[edges[j].v] = edges[j].u;
            }
        }
    }
}



}


