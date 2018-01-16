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
int case; //测试编号


int read

}
