#include <stdio.h>
#include <time.h>
#include "bplustree.h"
#include "presistBtree.h"
#include "restorefromfile.h"

#include "myque.h"


void *test_thread_myque(void *arg)
{
    myque_t *que = (myque_t *)arg;
    struct BPlusNode tmp;
    for(int i = 0; i < 10; i++) {
        myque_append(que, &tmp);
    }

    while(!myque_isempty(que)) {
        myque_pop(que);
    }
}

void thread_test_case(void)
{
    pthread_t pid[70];

    myque_t *que = myque_init();
    for(int i = 0; i < 70; i++) {
        pthread_create(&pid[i], NULL, test_thread_myque, que);
    }

    for(int i = 0; i < 70; i++) {
        void *ret;
        int r = pthread_join(pid[i], &ret);
        if(r) {
            perror("pthread_join");
        }
    }

    myque_destory(que);
}

int main(int argc, const char * argv[])
{

//    Restore("./btree.db");
//    int i;
//    BPlusTree T;
//    T = Initialize();
//
//    clock_t c1 = clock();
//    //i = 100;
//    for(i = 0;i < 15332; i++) {
//        T = Insert(T, i, i);
//    }
//
//    FillTreeID(T);
//
//    PersistBtree(T);

//    for(i = 200; i > 0; i--)
//    {
//        SearchKey(T,i);
//    }

//    Travel(T);
//    Destroy(T);
//
//    clock_t c2 = clock();
//
//    printf("\n用时： %lu秒\n",(c2 - c1)/CLOCKS_PER_SEC);

    thread_test_case();
    return 0;
}
