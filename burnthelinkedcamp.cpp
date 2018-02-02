#include <cstdio>
#include <cstdlib>
#include <cstring>

using namespace std;

namespace burnthelinkedcamp {


#define INF 0x7fffffff
#define MAXN 1000
#define MAXM 1000


//一共n个大营。从i-j最少有多少士兵。相当于边的数量，一共m条
int n, m;

//第i个大营最多有k个士兵
int c[MAXN];
int dist[MAXN];

//前i个士兵的总数
int d[MAXN];

//边的序号
int ei;

struct Edge {
    int u, v, w;
} edges[MAXM];

void init()
{
    ei = 0;
    for(int i=0; i<=n; i++)
    {
        dist[i] = INF;
    }
    dist[n] = 0;
    d[0] = 0;
}

bool bellman_ford()
{
    //这里顶点个数是n+1,所以如果经过其他点到x。最多经过n-1个
    for(int i=0; i<n; i++)
    {
        for(int k=0; k<ei; k++)
        {
            if(dist[edges[k].v] > dist[edges[k].u] + edges[k].w)
            {
                dist[edges[k].v] = dist[edges[k].u] + edges[k].w;
            }
        }
    }

    for(int k=0; k<ei; k++)
    {
        if(dist[edges[k].u] + edges[k].w < dist[edges[k].v])
        {
            return false;
        }
    }

    return true;

}




}
