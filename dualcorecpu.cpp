#include <cstdio>
#include <cstring>
#include "common.h"


using namespace std;


/**
 *  双核cpu  最小割定理
 */

namespace dualcorecpu {


struct Edge {
    int u, v, cap, flow;
    int next;

    Edge(int a = 0, int b = 0, int c = 0, int d = 0)
        : u(a), v(b), cap(c), flow(d){}
};

struct EdgeList {
    //顶点数量
    int start[NMAX];
    int last[NMAX];

    //边的数量
    Edge arch[MMAX];

    int t, i;

    void clear()
    {
        t = 0;
        for(i = 0; i<NMAX; i++)
        {
            last[i] = -1;
        }
    }

    void push_back(Edge edge)
    {
        edge.next = -1;
        if(last[edge.u] != -1)
        {
            arch[last[edge.u]].next = t;
        }
        else
        {
            start[edge.u] = t;
        }

        last[edge.u] = t;
        t ++;
    }

    void add_arc(Edge edge)
    {
        push_back(edge);
        push_back(Edge(edge.v, edge.u, edge.cap));

    }
} net;

int q[2][NMAX];
//q1相当于对列的头部， q2相当于对列的尾部
int q1[2], q2[2], qnow;

void push_queue(int a)
{
    q[qnow][q2[qnow] ++] = a;

}

int pop_queue()
{
    return q[qnow^1][q1[qnow^1] ++];
}

void switch_queue()
{
    qnow ^= 1;
    q1[qnow] = 0;
    q2[qnow] = 0;
}

bool empty_queue()
{
    return q1[qnow^1] >= q2[qnow^1];
}

int size_queue()
{
    return q2[qnow^1] - q1[qnow^1];
}


int n, m;
int dist[NMAX];
//找到一条增广路后存放节点以及节点数量
int path[NMAX], deep;
int cur[NMAX];


//构建层次网络
bool BFS()
{
    int i, l, u, v;
    for(i=0; i<NMAX; i++) dist[i] = -1;
    dist[i] = 0;
    switch_queue();
    push_queue(0);
    switch_queue();

    while(!empty_queue())
    {
        l = size_queue();
        while(l --)
        {
            u = pop_queue();
            for(i=net.start[u]; i!= -1; i=net.arch[u].next)
            {
                v = net.arch[i].v;
                if(dist[i] == -1 && net.arch[i].cap > net.arch[i].flow)
                {
                    dist[v] = dist[u] + 1;
                    push_queue(v);
                    if(v == n) return true;
                }
            }
        }
        switch_queue();
    }

    return false;
}

//增广路算法求解最大网络流
int dinic()
{
    int i, u, neck, pos, res;
    int maxFlow = 0;

    while(BFS())
    {
        memcpy(cur, net.start, sizeof(cur));
        deep = 0;
        u = 0;
        while(true)
        {
            //存在最短路径增广
            if(u == n)
            {
                neck = INF;
                for(i=0; i<deep; i++)
                {
                    res = net.arch[path[i]].cap - net.arch[path[i]].flow;
                    if(neck > res)
                    {
                        neck = res;
                        pos = i;
                    }
                }
                maxFlow += neck;
                for(i=0; i<deep; i++)
                {
                    //一个奇数、一个偶数。他到底咋存放的？？？
                    net.arch[path[i]].flow += neck;
                    net.arch[path[i]^1].flow -= neck;
                }

                deep = pos;
                u = net.arch[path[deep]].u;
            }

            for(i=cur[u]; i != -1; i = net.arch[i].next)
            {
                if(net.arch[i].cap > net.arch[i].flow && dist[i] + 1 == dist[net.arch[i].v])
                    break;
            }

            cur[u] = i;
            if(i != -1)
            {
                path[deep ++] = i;
                u = net.arch[i].v;
            }
            else
            {
                if(deep == 0) break;
                dist[u] = -1;
                u = net.arch[-- deep].u;
            }
        }
    }

    return maxFlow;
}

}
