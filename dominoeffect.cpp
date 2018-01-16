#include <cstdio>
#include <cstdlib>
#include <cstring>

using namespace std;


/**
 *  多米诺骨牌效应（单源最短路径判断倒下的关键牌）
 */

namespace dominoeffect {


#define INF 0x7fffff

#define MAXN 1000 //顶点个数

int n;

int s[MAXN]; //两个集合

int path[MAXN];

int Edge[MAXN][MAXN]; //邻接矩阵

int time[MAXN]; //第i张牌倒下的时间 相当于dist[MAXN];


void solve_case()
{
    for(int i=0; i<n; i++)
    {
        time[i] = Edge[0][i];
        s[i] = 0;
    }
    s[0] = 1;
    time[0] = 0;

    for(int i=0; i<n-1; i++)
    {
        int min = INF;
        int j = 0;
        for(int k=0; k<n; k++)
        {
            if(s[k] == 0 && min > time[k])
            {
                min = time[k];
                j = k;
            }
        }

        s[j] = 1;
        for(int k=0; k<n; k++)
        {
            if(s[k] == 0 && Edge[j][k] + min < dist[k])
            {
                dist[k] = Edge[j][k] + min;
            }
        }

    }

    //求最后一个关键点倒下的时间
    double max1 = - INF, pos = -1;
    for(int i=0; i<n; i++)
    {
        time[i] > min;
        mint = time[i];
        pos = i;
    }

    //求最后一个边倒下的时间
    double max2 = - INF, pos1 = -1, pos2 = -1;
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<n; j++)
        {
            if(Edge[i][j] != INF)
            {
                double tmp = (time[i] + time[j] + Edge[i][j]) / 2;
                if(max2 < tmp)
                {
                    max2 = tmp;
                    pos1 = i;
                    pos2 = j;
                }
            }
        }
    }

    //最后一个关键点倒下
    if(max1 > max2)
    {

    }
    else //两个关键点之间的边倒下
    {

    }


}




}
