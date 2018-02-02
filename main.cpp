#include <QCoreApplication>
#include <cstdio>
#include <code.cpp>

int main(int argc, char *argv[])
{
    //code::run();

    int flag[10];
    memset(flag, 0xff, sizeof(flag));
    for(int i=0; i<10; i++)
    {
        printf("%d\t", flag[i]);
    }
}
