#include <cstdio>
#include <cstring>
#include "common.h"

using namespace std;

namespace optimal_milking {


//最短距离
int dist[MAX][MAX];

//容量网络
int map[MAX][MAX];

//层次网络
bool sign[MAX][MAX];
bool used[MAX];

//机器数量、奶牛数量、实体总数、机器容量
int k, c, n, M;


//构建容量网络
void build_graph(int min_max)
{
    int i, j;
    memset(map, 0, sizeof(map));
    //源点和汇点都是虚拟出来的。所以源点到每头奶牛的弧容量都是1，每台机器到汇点的弧容量就都是M
    for(i=k+1; i<=n; i++) map[0][i] = 1;
    for(i=1; i<=k; i++) map[i][n+1] = M;

    for(i=k+1; i<=n; i++)
    {
        for(j=1; j<=k; j++)
        {
            if(dist[i][j] < min_max)
            {
                map[i][j] = 1;
            }
        }
    }
}

//构建层次网络
bool BFS()
{
    memset(used, 0, sizeof(used));
    memset(sign, 0, sizeof(sign));

    int queue[10 * MAX] = {0};
    int f, t;
    queue[0] = 0;
    f = 0;
    t = 1;
    while(f < t)
    {
       for(int i=0; i<=n+1; i++)
       {
           if(!used[i] && map[queue[f]][i])
           {
               queue[t ++] = i;
               used[i] = 1;
               //标记路径
               sign[queue[f]][i] = 1;
           }
       }

       f ++;
    }
    //可以到达汇点表示该图有效，否则跳过
    return used[n+1];
}

//dfs求增广
int DFS(int v, int sum)
{
    if(v == n + 1)
        return sum;

    int s = sum;

    for(int i=1; i<= n + 1; i++)
    {
        if(sign[v][i])
        {
            int t = DFS(i, MIN(sum, map[v][i]));
            map[v][i] -= t;
            map[i][v] += t;
            sum -= t;
        }
    }

    return s - sum;
}


int run()
{
    scanf("%d%d%d", &k, &c, &M);
    n = k + c;
    for(int i=1; i<=n; i++)
    {
        for(int j = 1; j<=n; j++)
        {
            scanf("%d", dist[i][j]);
            if(dist[i][j] == 0)
                dist[i][j] = INF;
        }
    }

    for(int i=1; i<=n; i++)
    {
        for(int k=1; k<=n; k++)
        {
            if(dist[i][k] != INF)
                for(int j=1; j<=n; j++)
                {
                    dist[i][j] = MIN(dist[i][j], dist[i][k] + dist[k][j]);
                }
        }
    }

    int left = 0, right = INF;
    while(left < right)
    {
        int ans = 0;
        int mid = (left + right)/2;
        build_graph(mid);
        while(BFS()) ans += DFS(0, INF);
        if(ans >= c) right = mid;
        else left = mid + 1;
    }
    printf("%d\n", right);
    return 0;
}

}
