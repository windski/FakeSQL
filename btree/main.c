#include <stdio.h>
#include <time.h>
#include "bplustree.h"
#include "presist.h"

int main(int argc, const char * argv[]) {
    int i;
    BPlusTree T;
    T = Initialize();
    int fd = openfile("test.data");
    
    clock_t c1 = clock();
    i = 100;
    for(i = 0;i < 1534; i++)
        T = Insert(T, i, i);
    for(i = 1534; i > 0; i--)
    {
        SearchKey(T,i);
    }

    
    //Travel(T);
    presist_tree(fd, T);
    Destroy(T);
    
    clock_t c2 = clock();
    
    closefile(fd);
    printf("\n用时： %lu秒\n",(c2 - c1)/CLOCKS_PER_SEC);
}
