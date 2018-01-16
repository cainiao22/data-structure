#include<cstdlib>
#include<cstdio>
#include<cstring>

using namespace std;

/**
 * 关键路径求解
 *
 **/


#define MAXN 100 //顶点个数的最大值
#define MAXM 200 //边个数的最大值

typedef struct ArcNode {
    int no, dur, to; //序号、持续时间、下一个节点
    struct ArcNode* next;

} ArcNode;

int n, m; //定点个数、边个数

ArcNode* list1[MAXN]; //出边表
ArcNode* list2[MAXN]; //入边表

int count1[MAXN]; //顶点的出度
int count2[MAXN]; //顶点的入度


int Ee[MAXN]; //各个事件最早开始时间
int El[MAXN]; //各个事件最迟开始时间

int e[MAXM]; //各个活动最早开始时间
int L[MAXM]; //各个活动最迟开始时间


void CritialPath()
{
    //拓扑排序
    int top = -1;
    memset(Ee, 0, sizeof(Ee));
    //一共有n个顶点
    for(int i=0; i< n; i++)
    {
        //用数组模拟链表
        if(count1[i] == 0)
        {
            count1[i] = top;
            top = i;
        }
    }

    ArcNode* temp;
    for(int i=0; i<n; i++)
    {
        if(top == -1)
        {
            printf("error the graph has a circle");
            return;
        }
        int j = top;
        top = count1[j];
        temp = list1[j];
        while(temp != NULL)
        {
            int k = temp->to;
            if(-- count1[k] == 0)
            {
                count1[k] = top;
                top = k;
            }
            if(Ee[j] + temp->dur > Ee[k])
            {
                Ee[k] = Ee[j] + temp->dur;
            }
            temp = temp->next;
        }

        //逆拓扑排序
        top = -1;
        temp = NULL;
        for(int i=0; i<n; i++)
        {
            El[i] = Ee[i];
        }
        for(int i=0; i<n; i++)
        {
            if(count2[i] == 0)
            {
                count2[i] = top;
                top = i;
            }
        }

        for(int i=0; i<n; i++)
        {
            if(top == -1)
            {
                printf("error the graph has a circle");
                return;
            }
            int j = top;
            temp = list2[j];
            top = count2[j];
            while(temp != NULL)
            {
                int k = count2[temp->to];
                if(--count2[k] == 0)
                {
                    count2[k] = top;
                    top = k;
                }
                //这里面j是该节点本身，k是该节点的上一级，上一级的最迟开始时间是我的最迟开始时间-上一级到我的时间，取最小值
                if(El[j] - temp->dur < El[k])
                {
                    El[k] = El[j] - temp->dur;
                }

            }




        }

    }

}

int main()
{
    int i, v, u, w; //序号、起点、终点、权重
    scanf("%d,%d", &n, &m);

    memset(list1, 0, sizeof(list1));
    memset(list2, 0, sizeof(list2));
    memset(count1, 0, sizeof(count1));
    memset(count2, 0, sizeof(count2));

    ArcNode *temp1, *temp2;
    for(i=0; i<m; i++)
    {
        scanf("%d,%d,%d", &u, &v, &w);
        count1[u] ++;
        temp1 = new ArcNode;
        temp1->to = v;
        temp1->no = i + 1;
        temp1->dur = w;
        temp1->next = list1[v];
        list1[v] = temp1;

        count2[v] ++;
        count2[v] ++;
        temp2 = new ArcNode;
        temp2->no = i + 1;
        temp2->to = u;
        temp2->dur = w;
        temp2->next = list2[v];
        list2[v] = temp2;

    }

    CritialPath();




}
