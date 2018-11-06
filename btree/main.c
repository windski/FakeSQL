#include <stdio.h>
#include <time.h>
#include "bplustree.h"
#include "presistBtree.h"

int main(int argc, const char * argv[])
{
    int i;
    BPlusTree T;
    T = Initialize();
    
    clock_t c1 = clock();
    i = 100;
    for(i = 0;i < 15346; i++) {
        T = Insert(T, i, i);
    }

    FillTreeID(T);

    //PersistBtree(T);

    for(i = 200; i > 0; i--)
    {
        SearchKey(T,i);
    }

    Travel(T);
    Destroy(T);

    clock_t c2 = clock();

    printf("\n用时： %lu秒\n",(c2 - c1)/CLOCKS_PER_SEC);

    return 0;
}
