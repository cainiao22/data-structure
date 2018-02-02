#include <cstdio>
#include <cmath>
#include <cstdlib>

using namespace std;

/**
 *
 *  这个算法本质是 逐步插入回路法
 *
 *
 */

namespace code {

#define M 1000

int list[M]; //输入密码前n-1位对应的位置
int stack[M * 10];
char ans[M * 10];

int s, a;


//v 相当于输入的密码。 m 密码的前n-1位最大数
void search(int v, int m)
{
    int w;
    while(list[v] < 10)
    {
        w = 10 * v + list[v];
        list[v] ++;
        stack[s ++] = w;
        v = w % m;
    }
}

int run()
{
    int n, m, i, v;
    while(scanf("%d", &n) != EOF && n != 0)
    {
        if(n == 1)
        {
            printf("0123456789\n");
            return 0;
        }
        for(i=0; i<M; i++) list[i] = 0;
        m = pow(10.0, n-1);
        s = 0;
        a = 0;
        v = 0;
        search(v, m);
        for(i=0; i<n; i++) printf("%c", '0');
        for(i=0; i<s; i++)
            printf("%d", stack[i]);
        printf("\n");
        while(s)
        {
            v = stack[-- s];
            ans[a ++] = v % 10 + '0';
            search(v / 10, m);
        }

        for(i=0; i<n; i++) printf("%c", '0');

        while (a) {
            printf("%c", ans[-- a]);
        }
        printf("\n");
        return 0;
    }
}

}
