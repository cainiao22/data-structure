#include <cstdio>
#include <cstdlib>
#include <cstring>

#include "common.h"

using namespace std;

/**
 *  求解无向图的割边集 ZOJ 2588
 *
 */

namespace burning_bridges {

struct Node {
    //序号 重边 另一个节点序号
    int id, tag, j;
    Node *next;
};

//顶点数量，边的数量
int n, m;

int nid;

Node mem[NMAX];
int memp;
Node *e[NMAX];

//第index个边是否是桥
int bridge[MMAX];
int nbridge;

int low[NMAX], dfn[NMAX];

int visited[NMAX];

int addEdge(Node e[], int i, int j)
{
    Node *p;
    for(p = e[i]; p != NULL; p = p->next)
    {
        if(p->j == j)
            break;
    }

    if(p != NULL)
    {
        p->tag ++;
        return 0;
    }

    p = &mem[memp ++];
    p->id = i;
    p->j = j;
    p->tag = 0;
    p->next = e[i];
    e[i] = p;

    return 1;
}

void DFS(int i, int father, int depth)
{
    visited[i] = 1;
    dfn[i] = low[i] = depth;
    for(Node* j = e[i]; j != NULL; j = j->next)
    {
        if(visited[j])
        {
            low[i] = MIN(low[i], dfn[j]);
        }
        else
        {
            DFS(j, i, depth + 1);
        }
        low[i] = MIN(low[j], low[i]);

        if(low[j] > dfn[i] && j->tag == 0)
        {
            nbridge ++;
            bridge[j->id] = nbridge;
        }
    }
}

//原版的代码
void DFS_A( int i, int father, int dth )
{
    visited[i] = 1; dfn[i] = low[i] = dth;
    Node *p;
    for( p=e[i]; p!=NULL; p=p->next )
    {
        int j = p->j;
        if( j!=father && visited[j]==1 )
            low[i] = MIN( low[i], dfn[j] );
        if( visited[j]==0 ) //顶点 j 未访问
        {
            DFS( j, i, dth+1 );
            low[i] = MIN( low[i], low[j] );
            if( low[j]>dfn[i] && !p->tag ) //重边不可能是割边
                bridge[p->id] = ++nbridge;
        }
    }
    visited[i] = 2;
}

}
