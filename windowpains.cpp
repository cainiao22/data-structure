#include <iostream>
#include <string.h>

using namespace std;

#define N   4

int screen[N][N];//屏幕快照最后显示的内容
string cover[N][N]; //可以覆盖i,j位置的窗口集合
bool exist[10]; //窗口类型
int id[10]; //入度
bool g[10][10]; //邻接矩阵
int t; //屏幕上出现的不同种类的窗口

string s;

//统计覆盖i,j窗口的集合
void calc()
{
    for(int i=0; i<10; i++)
    {
        for(int j=0; j<10; j++)
        {
            cover[i][j].erase();
        }
    }

    for(int i=1; i<=9; i++)
    {
        int j = (i-1)/3;
        int k = (i-1)%3;

        cover[j][k] += char(i + '0');
        cover[j][k+1] += char(i + '0');
        cover[j+1][k] += char(i + '0');
        cover[j+1][k+1] += char(i + '0');
    }
}

//读入屏幕快照数据
void init()
{
    //sizeof代表的是字节大小
    memset(exist, 0, sizeof(exist));
    memset(id, 0, sizeof(id));
    memset(g, 0, sizeof(g));

    t = 0;
    int k;
    for(int i=0; i<N; i++)
    {
        for(int j=0; j<N; j++)
        {
            cin>> k;
            screen[i][j] = k;
            if(!exist[k])
            {
                exist[k] = true;
                k ++;
            }
        }
    }
}

//构建有向图
void build()
{
    for(int i=0; i<N; i++)
    {
        for(int j=0; j<N; j++)
        {
            for(int p=0; p<cover[i][j].size(); p++)
            {
                if(!g[screen[i][j]][cover[i][j][p] - '0'] && screen[i][j] != cover[i][j][p] - '0')
                {
                    g[screen[i][j]][cover[i][j][p] - '0'] = true;
                    id[cover[i][j][p] - '0'] ++;
                }
            }
        }
    }
}

//检查环
bool check()
{
    for(int k=0; k<t; k++)
    {
        int i = 1;
        while(!exist[i] || (i <= 9 && id[i] > 0))
        {
            i ++;
        }

        //明明还有节点没有处理，但是此时没有入度为0的了，必然存在环
        if(i > 9)
        {
            return false;
        }
        exist[i] = false;
        //对以该边为起始位置的边入度进行减一
        for(int j=1; j<=9; j++)
        {
            if(exist[j] && g[i][j])
            {
                id[j] --;
            }
        }
    }

    return true;
}

int mainY(int argc, char *argv[])
{
    calc();
    init();
    build();
    bool result = check();
    if(result)
    {
        cout<<"SUCCESS";
    }
    else
    {
        cout<<"FAILED";
    }

    return 0;
}

