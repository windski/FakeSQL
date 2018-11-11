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
        return -1;
    }

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
        //
        //

        if(result!=200*__BFPQUEUE_SIZE)
        {
            int result2 =pread(fd,bfpqueue,result,offset);
            bfpqueue->size_=result/200;
            printf("size : %d",bfpqueue->size_);


//            for(int i=0;i<bfpqueue->size_;i++)
//            {
//                printf("%d\n",bfpqueue->data[i].id);
//            }




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
        T->Children[i ];
    }


    return 0;
}

int RecursionRebuild(BPlusTree Root, BFP bfp) {

    

}
