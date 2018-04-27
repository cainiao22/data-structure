#include <cstdio>
#include <cstdlib>
#include <cstring>

#include "common.h"

using namespace std;

/**
 *  Courses POJ1469
 *  二部图的的最小覆盖点
 */

namespace courses {

//课程数量，学生数量
int P, N;

//课程与学生的匹配关系,
int courses[NMAX][NMAX];

//学生对课程的匹配
int match[NMAX];

int used[NMAX];

int path(int c)
{
    for(int s=0; s < N; s ++)
    {
        if(courses[c][s] && !used[s])
        {
            used[s] = 1;
            //默认认为该节点未匹配或者有可替代节点
            int temp = match[s];
            match[s] = c;
            if(match[s] == -1 || path(match[s]))
            {
                return 1;
            }
            //走到这里说明没有。给它设置回去
            match[s] = temp;
        }
    }
}

int maxMatch()
{
    int sum = 0;
    for(int i=0; i<P; i++)
    {
        memset(used, 0, sizeof(used));
        sum += path(i);
        if(sum == P) break;
    }

    return sum;
}


}
