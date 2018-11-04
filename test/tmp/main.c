#include <stdio.h>
#include <time.h>
#include "bplustree.h"

int main(int argc, const char * argv[]) {
    int i;
    BPlusTree T;
    T = Initialize();
    
    clock_t c1 = clock();
    i = 36000000;
    while (i > 0)
        T = Insert(T, i--);
    i = 5000001;
    while (i < 36000000)
        T = Insert(T, i++);
    
    i = 36000000;
    while (i > 1000)
        T = Remove(T, i--);
    
    Travel(T);
    Destroy(T);
    
    clock_t c2 = clock();
    
    printf("\n用时： %lu秒\n",(c2 - c1)/CLOCKS_PER_SEC);
}
