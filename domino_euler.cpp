#include <cstdio>
#include <cstring>

using namespace std;

/**
 * 获取欧拉回路。多米诺骨牌
 */

namespace domino_euler {

#define VNUM 6
#define MAXN 100

struct EdgeNode {
    int vdjvex; //边的另一个顶点(因为边是直接跟在起始顶点后面的，所以想要另一个顶点的话。直接拿它所在的数组位置就好)
    int EdgeNo; //边序号
    int flag; //翻转标识
    struct EdgeNode* nextedge;
};

//各顶点的边链表 这里的顶点代表的骨牌的点数
EdgeNode* EdgeLink[VNUM + 1];

//标识边是否被访问
int visited[MAXN];

//存放访问路径。也就是结果
int path[MAXN];

int pi;

//骨牌数量
int N;

void createGL()
{
    int i;
    EdgeNode* p1, *p2;

    int v1, v2;
    memset(visited, 0, sizeof(visited));
    for(i=0; i<VNUM; i++) EdgeLink[i] = NULL;

    int number = 1;
    for(i=1; i<=N; i++)
    {
        scanf("%d %d", &v1, &v2);
        p1 = new EdgeNode;
        p2 = new EdgeNode;

        p1->EdgeNo = number;
        p1->flag = 1;
        p1->nextedge = EdgeLink[v1];
        EdgeLink[v1] = p1;

        p2->EdgeNo = number;
        p2->flag = -1;
        p2->nextedge = EdgeLink[v2];
        EdgeLink[v2] = p2;

        number ++;
    }

}

void DFSL(int start)
{
    while(pi <= N)
    {
        EdgeNode *p = EdgeLink[start];
        while(p != NULL)
        {
            if(!visited[p->EdgeNo])
            {
                visited[p->EdgeNo] = 1;
                if(p->flag)
                {
                    path[pi] = p->EdgeNo;
                }
                else
                {
                    path[pi] = - p->EdgeNo;
                }
                pi ++;
                DFSL(p->nextedge->EdgeNo);
            }
            else
            {
                p = p->nextedge;
            }
        }
    }
}

void Domino()
{
    int JDnum = 0; //奇数顶点个数
    int start1, start2;

    EdgeNode* p;
    for(int i=0; i<VNUM; i++)
    {
        int Dnum = 0;
        p = EdgeLink[i];
        while(p != NULL)
        {
            Dnum ++;
            p = p->nextedge;
        }
        if(Dnum % 2)
        {
            JDnum ++;
            start1 = i;
        }
        if(Dnum) start2 = i;
    }

    if(JDnum != 0 && JDnum != 2)
    {
        printf("NO solution");
        return;
    }

    if(JDnum == 2)
    {
        DFSL(start1);
    }
    else
    {
        DFSL(start2);
    }
}

void deleteLG()
{
    for(int i=0; i<VNUM; i++)
    {
        EdgeNode* p = EdgeLink[i];
        while(p != NULL)
        {
            EdgeLink[i] = p->nextedge;
            delete(p);
            p = EdgeLink[i];
        }
    }
}





}
