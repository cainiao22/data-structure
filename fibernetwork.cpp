#include <cstdio>
#include <cstdlib>
#include <cstring>

using namespace std;


/**
 *  光纤网络
 */

namespace fibernewwork {

#define MAXN 100
#define INF 0x7fffffff

int m[MAXN][MAXN];

int n;

int A, B;  //代表A、B两个站点

char str[27]; //最后一位要存放'/0'
char ch;

void run()
{
    while(scanf("%d", &n) && n)
    {
        memset(m, 0, sizeof(m));
        //输入A、B两个站点
        while(scanf("%d, %d", &A, &B))
        {
            //输入连接AB站点的公司
            while(scanf("%s", str))
            {
                //小窍门
                for(int i=0; str[i]; i++)
                {
                    m[A][B] |= 1 << (str[i] - 'a');
                }
            }
        }

        //floyd算法
        for(int k=0; k<n; k++)
        {
            for(int i=0; i<n; i++)
            {
                for(int j=0; j<n; j++)
                {
                    if(k == i || k == j) continue;
                    m[i][j] |= m[i][k] & m[k][j];
                }
            }
        }

        //查询
        while(scanf("%d, %d", &A, &B))
        {
            for(ch='a'; ch<='z'; ch ++)
            {
                if(m[A][B] & (1 << (ch - 'a')))
                    putchar(ch);
                if(!m[A][B])
                    putchar('-');
            }
            putchar('\n');
        }
        putchar('\n');



    }
}


}
