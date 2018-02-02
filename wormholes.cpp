#include<cstdlib>
#include<cstdio>
#include<cstring>
#include<queue>

using namespace std;

/**
 *
 * 虫洞  判断图中是否存在负权值的回路问题
 *
 **/

namespace wormholes {


#define INF 0x7fffffff
#define MAXN 1000
#define MAXM 1000

//每个顶点的边链表
struct ArcNode {
    int to, weight;
    struct ArcNode* next;
} List[MAXN];

int N, M, W; //农场个数、双向路径个数、单向路径个数

int inq[MAXN]; //每个顶点是否在对列中

queue<int> Q; //对列

int dist[MAXN];

int count[MAXN]; //每个顶点的入队列次数

int path[MAXN];


bool SPFA(int src)
{
    for(int i=0; i<N; i++)
    {
        dist[i] = INF;
        count[i] = 0;
        path[i] = src;
        inq[i] = 0;
    }
    Q.push(src);
    dist[src] = 0;
    count[src] ++;
    path[src] = -1;
    inq[src] = 1;

    while(!Q.empty())
    {
        int cur = Q.front();
        if(count[cur] >= N)
        {
           return true;
        }
        Q.pop();
        inq[cur] = 0;
        ArcNode* ptr = List[cur].next;

        while(ptr)
        {
            if(ptr->weight + dist[cur] < dist[ptr->to])
            {
                dist[ptr->to] = ptr->weight + dist[cur];
                if(!inq[ptr->to])
                {
                    inq[ptr->to] = 1;
                    Q.push(ptr->to);
                    count[ptr->to] ++;
                }
            }
            ptr = ptr->next;
        }
    }

    return false;
}




int run()
{

}





}
