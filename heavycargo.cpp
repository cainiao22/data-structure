#include <cstdio>
#include <cstdlib>
#include <cstring>

using namespace std;

/**
 *
 * 重型运输 弗洛伊德算法 求解每个顶点到其他顶点最长路径
 *
 **/

namespace heavycargo {

#define MAXCITIES 256
#define INF 0x7fffffff

#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))


char city[MAXCITIES][30];
int w[MAXCITIES][MAXCITIES];
char start[30], end[30];

int numcities;
int n, r; //城市数量和道路数量
int limit; //载重

int i, j, k;


int index(char* s)
{
    for(i=0; i<numcities; i++)
    {
        if(!strcasecmp(city[i], s)) return i;
    }

    strcpy(city[i], s);
    numcities ++;
    return i;
}

int read_case()
{
    scanf("%d, %d", &n, &r);
    numcities = 0;
    for(i=0; i<n; i++)
    {
        for(j=0; j<n; j++)
        {
            if(i == j)
            {
                w[i][j] = 0;
            }
            else
            {
                w[i][j] = INF;
            }
        }
    }
    for(i=0; i<r; i++)
    {
        scanf("%s, %s, %d", start, end, &limit);
        int u = index(start);
        int v = index(end);
        w[u][v] = limit;
        w[v][u] = limit;
    }
}


void resolve_case()
{
    for(k=0; k<n; k++)
    {
        for(i=0; i<n; i++)
        {
            for(j=0; j<n; j++)
            {
                w[i][j] = MAX(w[i][j], MIN(w[i][k], w[k][j]));
            }
        }
    }
}


}
