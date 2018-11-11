//
// Created by yurunyang on 18-11-7.
//

#include <fcntl.h>
#include <memory.h>
#include <errno.h>
#include <unistd.h>
#include "restorefromfile.h"

BPlusTree Restore(char *filename,BPlusTree Root) {

    Root = Initialize();
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
        //printf("%d\n",result);
        //bfpqueue->size_ =__BFPQUEUE_SIZE;
        //printf("size %d",bfpqueue->size_);
        for(int i=0;i<bfpqueue->size_;i++)
        {
            printf("%d\n",bfpqueue->data[i].id);
        }
        //
        rebuildBtree(Root,bfpqueue,0);
        break;
        //

        if(result!=200*__BFPQUEUE_SIZE)
        {
            int result2 =pread(fd,bfpqueue,result,offset);
            bfpqueue->size_=result/200;
            printf("size : %d",bfpqueue->size_);


            rebuildBtree(Root,bfpqueue,0);


            break;
        }
        offset+=200*__BFPQUEUE_SIZE;
    }

    return  Root;
}

int  rebuildBtree(BPlusTree T,bfpqueue_t *bfpqueue,int j) {

    T->id=bfpqueue->data[j].id;
    T->KeyNum=bfpqueue->data[j].KeyNum_;
    for(int i=0;i<T->KeyNum;i++)
    {
        T->Key[i] = bfpqueue->data[j].Key_[i];
        T->Value[i] = bfpqueue->data[j].Value_[i];
        if(bfpqueue->data[j].ChildLists_[i]<=80000000)
        {
            BPlusTree ChildNode = Initialize();
            rebuildBtree(ChildNode,bfpqueue,bfpqueue->data[j].ChildLists_[i]);
            T->Children[i]=ChildNode;
        } else
            continue;
    }


    return 0;
}

int RecursionRebuild(BPlusTree Root, BFP bfp) {

    

}
