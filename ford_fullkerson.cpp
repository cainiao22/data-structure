#include <cstdio>
#include <cstring>


using namespace std;


/**
 * 一般增广路求解最大网络流  (标号法)
 */


namespace ford_fullkerson {


#define MAXN 1000
#define INF 0x7fffffff

#define MIN(a, b) (a) < (b) ? (a) : (b)

int n, m;

struct ArcType
{
    int c, f;
};

ArcType Edge[MAXN][MAXN];

//顶点标号状态 -1 未标号 0 已标号未检查  1 已标号已检查
int flag[MAXN];

//倒向追踪，前一个顶点
int pre[MAXN];

//可改进量
int alpha[MAXN];

int queue[MAXN];

int qs, qe; //队头和队尾

void ford()
{
    while(1)
    {
        //初始化为-1
        memset(flag, 0xff, sizeof(flag));
        memset(pre, 0xff, sizeof(pre));
        memset(alpha, 0xff, sizeof(alpha));

        qs = qe = 0;
        flag[0] = 1;
        alpha[0] = INF;
        queue[qe] = 0;
        while(qs < qe && flag[n-1] != -1)
        {
            int v = queue[qs];
            qs ++;
            for(int i=0; i<n; i++)
            {
                if(flag[i] == -1)
                {
                    //正向
                    if(Edge[v][i].c < INF  && Edge[v][i].f < Edge[v][i].c)
                    {
                        flag[i] = 0;
                        pre[i] = v;
                        alpha[i] = MIN(alpha[v], Edge[v][i].c - Edge[v][i].f);
                        queue[qe] = i;
                        qe ++;
                    }
                    //逆向
                    else if(Edge[i][v].c < INF && Edge[i][v].f > 0)
                    {
                        pre[i] = -v;
                        alpha[i] = MIN(alpha[v], Edge[i][v].f);
                        flag[i] = 0;
                        queue[qe] = i;
                        qe ++;
                    }
                }

                flag[v] = 1;

            }
        }

        if(flag[n-1] == -1 || alpha[n-1] == 0) break;

        //倒向追踪
        int k1 = n-1, k2 = pre[k1];
        int a = alpha[k1];
        while(k1 != 0)
        {
            if(Edge[k2][k1] < INF)
                Edge[k2][k1].f += a;
            else
                Edge[k1][k2] -= a;
            k1 = k2;
            k2 = pre[k1];
        }

        int maxFlow = 0;
        for(int i=0; i<n; i++)
        {
            for(int j=0; j<n; j++)
            {
                if(i == 0 && Edge[i][j].c < INF)
                    maxFlow += Edge[i][j].f;
                printf("%d->%d: %d", i, j, Edge[i][j].f);
            }
        }

        printf("max flow %d\n", maxFlow);

    }
}


}
