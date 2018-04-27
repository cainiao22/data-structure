#include <cstdio>
#include <cstdlib>
#include <cstring>

#include "common.h"

using namespace std;

/**
 *  ZOJ1364 机器调度
 */


namespace machine_schedule{

//A、B两台机器的工作模式数量
int nx, ny;

//作业数量
int jobNum;

int g[NMAX][NMAX];

//A、B两台机器对应的匹配
int cx[NMAX], cy[NMAX];

//两台机器的访问状态
int sx[NMAX], sy[NMAX];


int path(int u)
{
    for(int v=0; v<ny; v++)
    {
        //有连边而且未访问
        if(g[u][v] && !sy[v])
        {
            sy[v] = 1;
            if(cy[v] == -1 || path(sy[v]))
            {
                sx[u] = v;
                sy[v] = u;

                return 1;
            }
        }
    }

    return 0;
}

int solve()
{
    int ans = 0;
    memset(cx, -1, sizeof(cx));
    memset(cy, -1, sizeof(cy));

    for(int u=0; u<nx; u++)
    {
        memset(sy, 0, sizeof(sy));
        if(!cx[u])
        {
            ans += path(u);
        }
    }

    return ans;
}

}
