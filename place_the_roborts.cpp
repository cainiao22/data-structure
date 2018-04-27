#include <cstdio>
#include <cstdlib>
#include <cstring>

#include "common.h"

using namespace std;


/**
 *  ZOJ1654 放置机器人
 *
 *  匈牙利算法求解二分图的最大匹配
 */

namespace place_the_roborts {

int g[NMAX][NMAX];

//x的匹配
int cx[NMAX];
//y的匹配
int cy[NMAX];

//访问标志
int flag[NMAX];



//地图 o代表空地 *代表草地 #代表墙壁
char map[NMAX][NMAX];

//地图的长宽
int m, n;

//水平的块和垂直的块
int xs[NMAX][NMAX], ys[NMAX][NMAX];

//水平块和垂直块的个数
int nx, ny;

int maxMatrix()
{
    int sum = 0;
    memset(cx, -1, sizeof(cx));
    memset(cy, -1, sizeof(cy));
    for(int i=0; i<nx; i++)
    {
        if(cx[i] == -1)
        {
            memset(flag, 0, sizeof(flag));
            sum += path(i);
        }
    }

    return sum;
}

/**
 * @brief path dfs
 * @param u
 * @return
 */
int path(int u)
{
    for(int v=0; v<ny; v++)
    {
        if(!g[u][v] || flag[v]) continue;
        //放这里，避免下一层path的时候把它又算上
        flag[v] = 1;
        if(cy[v] == -1 || path(cy[v]))
        {
            cx[u] = v;
            cy[v] = u;
            return 1;
        }

    }

    return 0;
}


int run()
{
    memset(xs, 0, sizeof(xs));
    memset(ys, 0, sizeof(ys));
    //块序号
    int number = 0;
    //按照地图构建水平和垂直块
    for(int i=0; i<m; i++)
    {
        //是否有墙,使用这个标识可以使免块与块之间的序号是连续的，避免发生断层
        int flag = 1;
        for(int j=0; j<n; j++)
        {
            if(map[i][j] == 'o')
            {
                //如果有墙
                if(flag == 1) number ++;
                xs[i][j] = number;
                flag = 0;

            }else if(map[i][j] =='#')
            {
                flag = 1;
            }

        }
    }

    xn = number;

    number = 0;
    for(int j=0; j<n; j++)
    {
        int flag = 1;
        for(int i=0; i<m; i++)
        {
            if(map[i][j] == 'o')
            {
                if(flag == 1) number ++;
                ys[i][j] = number;
                flag = 0;
            }
            else if(map[i][j] == '#')
            {
                flag = 1;
            }
        }
    }

    yn = number;

    memset(g, 0, sizeof(g));

    for(int i=0; i<m; i++)
    {
        for(int j=0; j<n; j++)
        {
            //只要这个区域有值，必然是一块空地，ys同理，也一定会有值
            if(xs[i][j])
            {
                g[xs[i][j]][ys[i][j]] = 1;
            }
        }
    }

    return maxMatrix();
}

}
