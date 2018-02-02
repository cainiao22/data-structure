#include <cstdio>
#include <cstring>

using namespace std;


namespace playonwords {

#define INF 0x7fffffff
#define MAXN 1000

//顶点的出度和入度
int od[26], id[26];

int parent[26];

struct Edge {
    int u, v;
} edges[MAXN];

void UFSet()
{
    for(int i=0; i<26; i++)
    {
        parent[i] = -1;
    }
}

int findParent(int x)
{
    int s = x;
    while(parent[s] != -1)
    {
        s = parent[s];
    }
    int temp = x;
    while(x != s)
    {
        temp = parent[x];
        parent[x] = s;
        x = temp;
    }

    return s;
}


}
