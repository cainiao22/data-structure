#include <cstdio>
#include <cstring>

using namespace std;

/**
 *
 * 弗洛莱算法。核心：桥是最后选择。
 *
 */


namespace fleury {

#define MAXN 100

struct Stack {
    int top;
    int node[MAXN];
} s;

int Edge[MAXN][MAXN];
int n;


void dfs(int start)
{
    s.node[s.top ++] = start;
    for(int i=0; i<MAXN; i++)
    {
        if(Edge[start][i] > 0)
        {
            Edge[start][i] = 0;
            Edge[i][start] = 0;
            dfs(i);
            //因为求的是欧拉回路。出去了不可能再回退
            break;
        }
    }
}

void Fleury(int start)
{
    int i, b;
    s.top = 0;
    s.node[s.top] = start;
    while(s.top >= 0)
    {
        b = 0;
        for(i=0; i<n; i++)
        {
            if(Edge[s.node[s.top]][i] > 0)
            {
                b = 1;
                break;
            }
        }

        if(b)
        {
            s.top --;
            dfs(s.node[s.top + 1]);
        }
        else
        {
            printf("%d", s.node[s.top]);
            s.top --;
        }
    }
}

}
