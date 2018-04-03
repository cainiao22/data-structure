#include <cstdio>
#include <cstring>
#include <cmath>
#include "common.h"


using namespace std;

namespace budget {

#define N 100

#define KN 100
#define KM 100

struct Edge {
    int c, f, low, x, y;
    Edge *next, *bak;

    Edge(){}
    Edge(int c, int f, int low, int x, int y) : c(c), f(f), low(low), x(x), y(y){}

    void* operator new(size_t size, void* p)
    {
        return p;
    }

} *E[N];

struct Node {
    int low, high;
};

int s, t, m;

int Q[N], D[N];

//当前的顶点及路径
Edge *cur[N], *path[N];

Edge *base, *data, *it;

//每个格子的限制条件
Node limit[N][N];

int sumn[KN], summ[KM], in[N], out[N];

//方阵的行列
int kn, km;

void DFS()
{
    memset(D, -1, sizeof(D));
    int i, j, p1 = 0, p2 = 0;
    Q[p1] = s;
    D[s] = 0;
    while(1)
    {
        i = Q[p1 ++];
        for(Edge* e = E[i]; e; e = e->next)
        {
            if(e->c == 0) continue;
            //行节点是0-kn+1,列节点是kn+2-kn+km+2
            //因为图的构造方式是S流入行节点。再从行节点流入列。最后列节点入T,
            //既然是深度优先搜索，想让增广路前进的话。就需要y坐标
            int j = e->y;
            if(D[j] == -1)
            {
                Q[p2 ++] = j;
                D[j] = D[i] + 1;
                 if(j == T) return;
            }
        }

        if(p1 == p2) break;
    }
}

//TODO 未完成 没看懂

int maxFlow()
{
    int i, k, mink, d, flow = 0, path_n;
    while(1)
    {
        DFS();
        if(D[T] == -1) break;
        memcpy(cur, E, sizeof(E));
        path_n = 0;

        i = s;
        while(1)
        {
            if(i == t)
            {
                mink = 0;
                d = INF;
                for(k=0; k<path_n; k++)
                {
                    if(path[k]->c < d)
                    {
                        d = path[k]->c;
                        mink = k;
                    }
                }


            }
        }
    }

    return 0;
}

int setLimit(int x, int y, char op, int v)
{
    if(op == '=')
    {
        if(v > limit[x][y].high || v < limit[x][y].low)
        {
            return 0;
        }
        limit[x][y].low = limit[x][y].high = v;
    }
    else if(op == '>')
    {
        limit[x][y].low = MAX(limit[x][y].low, v + 1);
    }
    else if(op == '<')
    {
        limit[x][y].high = MIN(limit[x][y].high, v - 1);
    }

    if(limit[x][y].low > limit[x][y].high)
    {
        return 0;
    }
    return 1;
}


int build()
{
    int i, j, T, ok = 1;
    //读取行列数
    scanf("%d%d", &kn, &km);
    for(i=1; i<=kn; i++) scanf("%d", &sumn[i]);
    for(i=1; i<=km; i++) scanf("%d", &summ[i]);
    for(i=1; i<=kn; i++)
    {
        for(j=1; j<=km; j++)
        {
            limit[i][j].low = 0;
            limit[i][j].high = INF;
        }
    }
    scanf("%d", &T);
    while(T --)
    {
        int x, y, v;
        //不是因为>=,而是因为所有字符串的末尾都有一个'\0'
        char op[2];
        scanf("%d%d%s%d\n", &x, &y, op, &v);
        //所有节点都必须有这个限制
        if(!x && !y)
        {
            for(i=1; i<=kn; i++)
            {
                for(j=1; j<=km; j++)
                {
                    if(!setLimit(i, j, op[0], v))
                    {
                        ok = 0;
                    }
                }
            }
        }
        else if(!x && y)
        {
            for(i=1; i<=kn; i++)
            {
                if(!setLimit(i, y, op[0], v))
                {
                    ok = 0;
                }
            }
        }
        else if(x && !y)
        {
            for(i=1; i<=km; i++)
            {
                if(!setLimit(x, i, op[0], v))
                {
                    ok = 0;
                }
            }
        }else if(!setLimit(x, y, op[0], v))
        {
            ok = 0;
        }
    }

    return ok;
}

void solve()
{
    int i, j, n, x, y, c;
    if(!build())
    {
        return;
    }
    memset(E, 0, sizeof(E));
    S = 0;
    T = kn + km + 3;
    n = kn + km + 2;

    memset(in, 0, sizeof(in));
    memset(out, 0, sizeof(out));
    data = new Edge[5*n*n];
    base = data;
    for(i=1; i<=kn; i++)
    {
        for(j=1; j<=km; j++)
        {
           x = i + 1;
           y = kn + j + 1;
           c = limit[i][j].high;
           u = limit[i][j].low;
        }
    }


}

int run()
{
    int T;
    scanf("%d", &T);
    while(T --)
        solve();
    return 0;
}

}
