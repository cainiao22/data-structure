#include <cstdio>
#include <cstdlib>
#include <cstring>
#include "common.h"

using namespace std;

/**
 *  求解关节点  ZOJ 1119
 */

namespace spf {

int Edge[NMAX][NMAX];
int visited[NMAX];

//顶点数目
int nodes;

int dfn[NMAX];
int low[NMAX];

int son;
int subnets[NMAX];

int tmpdfn;

/**
 * @brief dfs 求解关键点
 * @param u
 */
void dfs(int u)
{
    for(int v=0; v<nodes; v++)
    {
        if(Edge[u][v])
        {
            if(!visited[v])
            {
                visited[v] = 1;
                tmpdfn ++;
                dfs[v] = low[v] = tmpdfn;
                dfs(v);
                low[u] = MIN(low[u], low[v]);
                if(low[v] >= dfn[u])
                {
                    if(u != 1)
                    {
                        subnets[u] ++;
                    }
                    else
                    {
                        son ++;
                    }
                }
            }
            else
            {
                low[u] = MIN(low[u], dfn[v]);
            }

        }
    }
}

}
