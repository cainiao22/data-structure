#include<cstdlib>
#include<cstdio>
#include<cstring>
#include<queue>

using namespace std;

/**
 *  spfa求解单源最短路径。其实是对铂尔曼福特算法的一种改进
 */

namespace spfa {


#define INF 0x7fffffff
#define MAXN 100
#define MAXM 1000

struct Edge {
    int u, v, w;
} edges[MAXM];

int m, n;

struct ArcNode {
    int to, weight;
    struct ArcNode* next;
};

queue<int> Q;

//每个顶点对应一个ArcNode
ArcNode* List[MAXN];

//顶点是否在对列中的标志
int inq[MAXN];
int dist[MAXN];
int path[MAXN];

void SPFA(int v0)
{
    for(int i=0; i<n; i++)
    {
        inq[i] = 0;
        dist[i] = INF;
        path[i] = v0;
    }
    Q.push(v0);
    inq[v0] = 1;
    while(!Q.empty())
    {
       int cur = Q.front();
       Q.pop();
       inq[cur] = 0;
       ArcNode* curNode = List[cur];
       while(curNode != NULL)
       {
            if(dist[curNode->to] > dist[cur] + curNode->weight)
            {
                dist[curNode->to] = dist[cur] + curNode->weight;
                if(!inq[curNode->to])
                {
                    Q.push(curNode->to);
                    inq[curNode->to] = 1;
                }
                path[curNode->to] = cur;
            }

            curNode = curNode->next;
       }
    }
}

}
