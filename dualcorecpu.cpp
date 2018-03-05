#include <cstdio>
#include <cstring>
#include "common.h"


using namespace std;


/**
 *  双核cpu  最小割定理
 */

namespace dualcorecpu {


struct Edge {
    int u, v, cap, flow;

    Edge(int a = 0, int b = 0, int c = 0, int d = 0)
        : u(a), v(b), cap(c), flow(d){}
};

struct EdgeList {
    //顶点数量
    int start[NMAX];
    int last[NMAX];

    //边的数量
    Edge arch[MMAX];


};

}
