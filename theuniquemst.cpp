#include <cstdio>
#include <cstdlib>

using namespace std;

/**
 * 判断最小生成树是否唯一
 *  1、判断图当中是否有权重相等的边，如果有的话标记出来。
 *  2、执行一遍最小生成树算法。将用到的边标记下来。
 *  3、遍历所有边。如果遇到使用过的而且标记了存在相同权重的边的话。将此边排除，再次执行一遍最小生成树算法
 *  4、将两次mst算法生成的权重比较，看大小是否相等。相等的话代表存在多个最小生成树。不相等的话将删除的边的标记置回来。
 *  5、继续遍历。从新从第三步开始。直到所有边都遍历结束。
 */

namespace theuniqueMST {

#define MAXN 1000 //点的最大个数
#define MAXM 2000 //边的最大个数


struct Edge {
    int u, v, w;
    bool equal, del, used;
} edges[MAXM];


int parent[MAXN];
int m, n;
bool first;

void UFSet()
{
    for(int i=0; i<n; i++)
    {
        parent[i] = -1;
    }
}

int find(int x)
{
    int s;
    for(s=x; parent[x] >= 0; s = parent[s]) ;

    while(s != x)
    {
        int temp = parent[x];
        parent[x] = s;
        x = temp;
    }

    return s;
}


void Union(int R1, int R2)
{
    int r1 = find(R1);
    int r2 = find(R2);

    int tmp = r1 + r2;
    //parent跟节点的值是负数。parent[r1] > parent[r2]说明r2的子节点比r1的子节点多
    if(parent[r1] > parent[r2])
    {
        parent[r1] = r2;
        parent[r2] = tmp;
    }else{
        parent[r2] = r1;
        parent[r1] = tmp;
    }

}


int cmp(const void* a, const void* b)
{
    Edge* e1 = (Edge*) a;
    Edge* e2 = (Edge*) b;
    return e1->w - e2->w;
}

int Kruskal()
{
    int sumweight = 0, num = 0;
    UFSet();
    for(int i=0; i<m; i++)
    {
        if(edges[i].del) continue;

        int u = edges[i].u;
        int v = edges[i].v;
        if(find(u) != find(v))
        {
            sumweight += edges[i].w;
            Union(u, v);
            if(first)   edges[i].used = true;
            num ++;
        }
        //最小连通图的边数量必须是n-1
        if(num >= n-1) break;
    }

    return sumweight;
}


int run()
{
    int u, v, w;
    int t, i, j, k;//t代表测试样本数量
    scanf("%d", &t);
    for(i=0; i<t; i++)
    {
        scanf("%d, %d", &n, &m);
        for(j=0; j<m; j++)
        {
            scanf("%d, %d, %d", &, &v, &w);
            edges[j].u = u-1;
            edges[j].v = v-1;
            edges[j].w = w;
            edges[j].used = edges[j].del = edges[j].equal = false;

        }

        for(j = 0; j<m; j++)
        {
            for(k = 0; k<m; k++)
            {
                if(j == k) continue;
                if(edges[j].w == edges[k].w)
                {
                    edges[j].equal = true;
                }
            }
        }

        qsort(edges, sizeof(edges[0]), sizeof(edges)/sizeof(edges[0]), cmp);
        int weight1 = Kruskal();
        for(j=0; j<m; j++)
        {
            if(edges[j].equal && edges[j].used)
            {
                edges[j].del = true;
                int weight2 = Kruskal();
                if(weight1 == weight2)
                {
                   break;
                }
                edges[j].del = false;
            }
        }
        if(j >= m -1)
        {
            printf("unique !!!");
        }
        else
        {
            printf("not unique !!!");
        }
    }
}



}
