#include<cstdlib>
#include<cstdio>

using namespace std;

namespace kruskal {


/*
 *
 * 并查集
 *
 */

#define N 100  //节点数量
#define M 200 //边的数量

int parents[N]; //父节点

void UFSet()
{
    for(int i=0; i<N; i++)
    {
        parents[N] = -1;
    }
}

int find(int x)
{
    int s;
    for(s = x; parents[s] > 0; s = parents[s]) ;

    //将s到x这条线上面的所有节点父节点全部设置为s;
    while(s != x)
    {
        int tmp = parents[x];
        parents[x] = s;
        x = tmp;
    }

    return s;
}


//不要与union关键字冲突

union Test {

};
void Union(int R1, int R2)
{
    int r1 = find(R1);
    int r2 = find(R2);

    int parent1 = parents[r1];
    int parent2 = parents[r2];

    int tmp = parent1 + parent2;
    if(parent1 > parent2)
    {
        parents[r1] = r2;
        parents[r2] = tmp;
    }
    else
    {
        parents[r2] = r1;
        parents[r1] = tmp;
    }
}


/**
 * 克鲁斯卡尔算法求解最小生成树
 *  以边为主导
 *
 **/

struct Edge {
    int u, v, w; //起点、终点、权重
} edges[M];


int cmp(const void* a, const void *b)
{
    Edge* edge1 = (Edge*) a;
    Edge* edge2 = (Edge*) b;
    //都快忘了还可以这样写
    return (*edge1).w - (*edge2).w;
}

int m, n;

void Kruskal()
{
    int sumweight = 0; //生成树的权值
    int num = 0;      //已经选用的边的数目
    int u, v;         //选用边的两个顶点
    UFSet();

    for(int i=0; i<m; i++)
    {
        u = edges[i].u;
        v = edges[i].v;
        if(find(u) != find(v))
        {
            Union(u, v);
            sumweight += edges[i].w;
            num ++;
        }
        //最小生成树的边的数目一定是顶点数目减一，这是判断退出的条件
        if(num == n - 1) break;
    }

    printf("the min weight of the graph is %d\n", sumweight);
}

/**
 * @brief sort
 * @param p
 * 必须在使用之前声明好
 */
void sort(Edge* p, int (*pf)(const void*, const void *));

void run()
{
    int i, v, u, w; //序号、起点、终点、权重
    scanf("%d,%d", &n, &m);
    for(int i=0; i<m; i++)
    {
        scanf("%d, %d, %d", &u, &v, &w);
        edges[i].u = u;
        edges[i].v = v;
        edges[i].w = w;
    }
    //这里是该方法的主要耗时操作
    sort(edges, cmp);
    Kruskal();
}

/**
 * @brief sort
 * @param p 将函数作为参数传递过来
 */

void sort(Edge* p, int (*pf)(const void*, const void *))
{

}


}
