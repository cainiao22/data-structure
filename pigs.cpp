#include <cstdio>
#include <cstdlib>
#include <cstring>

using namespace std;

/**
 *
 * 麦克卖猪问题  增广路标号算法
 *
 */


namespace pigs {

#define INF 0x7fffffff

#define MIN(a, b) (a) < (b) ? (a) : (b)

#define MAXN 5 //顾客
#define MAXM 5 //猪圈

//m是猪圈数量，n是顾客数量
int m, n;


//pre初始时候为-2，标识未标号，用来代替flag
int pre[MAXN];


int flag[MAXN];

//源点和汇点
int s, t;
int customer[MAXN + 2][MAXN + 2]; //相当于容量
int flow[MAXN + 2][MAXN + 2];  //相当于实际流量


//初始化流量 构造网络流
void init()
{
    memset(customer, 0, sizeof(customer));
    memset(flow, 0, sizeof(flow));

    int house[MAXM + 2];
    int last[MAXM]; //每个猪圈的最后一位顾客
    scanf("%d %d", &m, &n);
    s = 0;
    t = n + 1;
    for(int i=0; i<m; i++)
    {
        scanf("&d", &house[i]);
    }

    //顾客手中钥匙数量
    int num = 0;
    //猪圈编号
    int k = 0;
    for(int i=1; i<=n; i++)
    {
        //输入顾客手中钥匙数量
        scanf("%d", &num);
        for(int j=0; i<num; j++)
        {
            scanf("%d", &k);
            if(last[k] == 0)
            {
                //假如该顾客是第k个猪圈的第一位的话，将猪圈数量全部给他
                //因为一个顾客可能是多个猪圈的第一个客户所以用加法
                customer[s][i] += house[k];
            }
            else
            {
                customer[last[k]][i] = INF;
            }
            last[k] = i;
        }
        //输入顾客预计买几头猪。作为汇点的入边
        scanf("%d", &customer[i][t]);

    }
}

void ford()
{

    //每个顶点的改进量
    int minFlow[MAXN + 2];
    //模拟对列
    int queue[MAXN + 2];
    int qs, qe;
    for(int i=0; i<MAXN; i++)
    {
        for(int j=0; j<MAXN; j++)
            flow[i][j] = 0;
    }
    minFlow[0] = INF;
    while(1)
    {
        qs = qe = 0;
        queue[qe ++] = 0;
        for(int i=0; i<=t; i++)
        {
            pre[i] = -2;
        }
        //源点的前置为-1
        pre[0] = -1;
        //对列不空而且汇点没有标号
        //下面这个循环只是一次标号
        while(qs < qe && pre[t] == -2)
        {
            int u = queue[qs ++];
            for(int i=1; i<=t; i++)
            {
                if(pre[i] == -2 && flow[u][i] < customer[u][i])
                {
                    minFlow[i] = MIN(minFlow[i], customer[u][i] - flow[u][i]);
                    pre[i] = u;
                    queue[qe ++] = i;
                }
            }

        }

        if(pre[t] == 2) break;
        int v = t, u = pre[v];
        while(u != -1)
        {
            flow[u][v] += minFlow[v];
            flow[v][u] -= minFlow[v];
        }
    }

    int sum = 0;
    for(int i=0; i<t+1; i++)
    {
        sum += flow[i][t];
    }

    printf("%d\n", sum);
}




}
