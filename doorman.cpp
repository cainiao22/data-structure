#include <cstdio>
#include <cstring>

using namespace std;


namespace doorman {


int readLine(char* s)
{
    int L;
    for(L = 0; (s[L] = getchar()) != '\n' && s[L] != EOF; L++)   ;
    s[L] = '\0';

    return L;
}

int run()
{
    int i, j;
    char buf[100];
    //M起始位置。N房间总数
    int M, N;
    //每个房间的门的数量
    int door[20];

    while(readLine(buf))
    {
        //代表开始
        if(buf[0] == 'S')
        {
            //%*s代表忽略第一个字符串
            sscanf(buf, "%*s %d %d", &M, &N);
            int doors = 0;
            for(i = 0; i<N; i++)
            {
               readLine(buf);
               int k = 0;
               while(sscanf(buf + k, "%d", &j) == 1)
               {
                   door[i] ++;
                   door[j] ++;
                   while(buf[k] && buf[k] == ' ') k ++;
               }
            }

            int odd = 0, even = 0; //奇数、偶数个数
            for(i=0; i<N; i++)
            {
                if(door[i] % 2)
                    odd ++;
                else
                    even ++;
            }

            if(odd == 0 || (odd == 2 && door[M] == 1 && door[0] == 1 && M != 0))
            {
                    printf("ok it's very good");
            }
             else
            {
                printf("sorry is wrong");
            }

        }
    }
    return 0;
}


}
