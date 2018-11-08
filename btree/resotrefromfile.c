//
// Created by yurunyang on 18-11-7.
//

#include <fcntl.h>
#include <memory.h>
#include <errno.h>
#include <unistd.h>
#include "restorefromfile.h"

BPlusTree Restore(char *filename) {

    BPlusTree  Root = Initialize();
    int fd = open(filename,O_RDONLY);
    if(fd == -1){
        printf("%s  ",strerror(errno));
        printf("openFailed\n");

        // 这里你没发现警告吗? 返回值的类型应该一样啊.最起码给你NULL???
        // 想要错误返回通知调用函数, 你可以在你的头文件里定义 全局变量就好了
        // TODO: fix it!!
//        return -1;
    }


    // WARNING!! 你准备在哪析构??
    // TODO: FIX IT!!
    bfpqueue_t * bfpqueue = (bfpqueue_t*)malloc(sizeof(bfpqueue_t));

    int result=0;
    __off64_t  offset=0;
    while(1)
    {
        result =pread(fd,bfpqueue,200*__BFPQUEUE_SIZE,offset);
        printf("%d\n",result);
        bfpqueue->size_ =__BFPQUEUE_SIZE;

        //
        //
        //

        if(result!=200*__BFPQUEUE_SIZE)
        {
            int result2 =pread(fd,bfpqueue,result,offset);
            bfpqueue->size_=result/200;
            //
            //
            //
            //printf("error\n");
            //printf("%s",strerror(errno));
            break;
        }
        offset+=200*__BFPQUEUE_SIZE;
    }
    int a;
}

int rebuildBtree(BPlusTree T, BFP bfp) {

    T->id=bfp.id;
    T->KeyNum=bfp.KeyNum_;
    for(int i=0;i<bfp.KeyNum_;i++)
    {
        T->Key[i] = bfp.Key_[i];
        T->Value[i] = bfp.Value_[i];
        T->Children[i];
        // TODO: complete it
    }


    return 0;
}
