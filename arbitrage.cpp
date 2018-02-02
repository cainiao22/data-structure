#include<cstdlib>
#include<cstdio>
#include<cstring>

using namespace std;

/**
 *
 * 套汇问题
 *
 **/

namespace arbitrage {


#define MAXN 100
#define MAXM 1000
#define max(a, b) ((a) > (b) ? (a) : (b))
#define INF 0x7fffffff

//汇率关系
struct exchange {
    int ci, cj;
    double cij;
} ex[MAXM];

//存放货币名称
char name[MAXM][20], a[20], b[20];

//读入的汇率
double x;
//最大汇率
double maxdist[MAXN];

int flag; //是否存在套汇

int m, n;


int readcase()
{
    scanf("%d", &n);
    if(n <= 0)
    {
        return 0;
    }
    //读入n个货币名称
    for(int i=0; i<n; i++)
    {
        scanf("%s", name[i]);
    }
    scanf("%d", &m);
    for(int i=0; i<m; i++)
    {
        scanf("%s, %lf, %s", a, &x, b);
        int j = 0, k = 0;
        for(j; strcmp(a, name[j]); j++) ;
        for(k; strcmp(b, name[k]); k++) ;

        ex[j].ci = j;
        ex[j].cj = k;
        ex[j].cij = x;
    }

    return 1;

}

void bellman(int v0)
{
    flag = 0;
    //兑换不了的话可以假设他们的汇率为0，这样求最大的时候就会忽略它们。
    memset(maxdist, 0, sizeof(maxdist));

    //自己兑换自己汇率为1
    maxdist[v0] = 1;

    for(int k=1; k<n; k++)
    {
        for(int i=0; i<m; i++)
        {
            if(maxdist[ex[i].ci] * ex[i].cij > maxdist[ex[i].cj])
            {
                maxdist[ex[i].cj] = maxdist[ex[i].ci] * ex[i].cij;
            }
        }
    }

    if(maxdist[v0] > 1.0)
    {
        flag = 1;
    }

}

}
