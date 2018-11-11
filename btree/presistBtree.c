//
// Created by yurunyang on 18-11-6.
//

#include <stdbool.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <memory.h>
#include "bplustree.h"
#include "presistBtree.h"
#include "myque.h"

int hasopened = 0;

void NodeBuffer(struct BFPqueue * bfPqueue_, const BPlusTree T) {


        if(bfPqueue_==NULL)
            assert(bfPqueue_!=NULL);

        int keyNum = T->KeyNum;
        if(bfPqueue_->size_>=__BFPQUEUE_SIZE)
        {
            //WRITE bfPqueue TO FILE



            WriteBFPqueToFile("btree.db",bfPqueue_,100);

            bfPqueue_->size_=0;
            bfPqueue_->head_=0;
            bfPqueue_->tail_=0;

        }
        {
            bfPqueue_->data[bfPqueue_->tail_].KeyNum_ = keyNum;
            bfPqueue_->data[bfPqueue_->tail_].id=T->id;
            //bfPqueue_[bfPqueue_->tail_].data->id=T->id;
            for(int i=0;i<keyNum;i++)
            {
                bfPqueue_->data[bfPqueue_->tail_].Key_[i] = T->Key[i];
                bfPqueue_->data[bfPqueue_->tail_].Value_[i] =T->Value[i];
                if(T->Next != NULL)
                    bfPqueue_->data[bfPqueue_->tail_].Next_ = T->Next->id;
                else
                    bfPqueue_->data[bfPqueue_->tail_].Next_ = UINT64_MAX;

                if(T->Children[i]!=NULL)
                    bfPqueue_->data[bfPqueue_->tail_].ChildLists_[i] = T->Children[i]->id;
                else
                    bfPqueue_->data[bfPqueue_->tail_].ChildLists_[i] = UINT64_MAX;
            }


            //printf("id:%d\n",T->id);
            //printf("sizeof %d ",sizeof(bfPqueue_->data[bfPqueue_->tail_]));
            //printf("%d",sizeof(bfPqueue_->data));
            bfPqueue_->size_++;
            //printf("%d\n",bfPqueue_->size_);
            bfPqueue_->tail_++;//= (bfPqueue_->tail_+1) % __BFPQUEUE_SIZE;

        }



}



void PersistBtree(const BPlusTree Root) {

    myque_t *que = myque_init();
    //bfpqueue_t *tmp = Root;
    struct BFPqueue *bfPqueue = BFPqueue_init();

    myque_append(que, Root);
    BPlusTree tmp ;
    while(!myque_isempty(que)) {
        tmp = myque_top(que);
        myque_pop(que);


        NodeBuffer(bfPqueue,tmp);
        //printf("tmp id : %d\n",tmp->id);
        //tmp->id = __initIDval++;


        for(int i = 0; i < M + 1; i++) {
            if(tmp->Children[i] == NULL) {
                continue;
            }

            if(myque_append(que, tmp->Children[i]) == -1) {
                printf("queue is not long enough.\n");
                exit(-1);
            }
        }
    }
    WriteBFPqueToFile("btree.db",bfPqueue,bfPqueue->size_);
    free(bfPqueue);
    myque_destory(que);

}


bfpqueue_t * BFPqueue_init()
{
    bfpqueue_t * data = (bfpqueue_t*)malloc(sizeof(bfpqueue_t));
    assert(data);

    data->size_=0;
    data->tail_=data->head_=0;
    return data;

}

int WriteBFPqueToFile(char *filename, bfpqueue_t *bfPqueue,int size) {

    if(hasopened==0)
    {
        remove(filename);
        hasopened =1;
    }

    int fd = open(filename,O_RDWR | O_CREAT | O_APPEND,00664);

    if(fd == -1){
        printf("%s  ",strerror(errno));
        printf("openFailed\n");
        return -1;
    }
        //return -1;
    write(fd,bfPqueue->data,200*size);
    printf("write completed\n ");
    close(fd);
    return 0;
}

//int myque_pop(struct BFPqueue *que)
//{
//    if(myque_isfull(que)) {
//        return -1;
//    }
//
//    que->size_--;
//    que->head_ = (que->head_ + 1) % __BFPQUEUE_SIZE;
//
//    return 0;
//}

//BFP myque_top(bfpqueue_t *que)
//{
//    return que->data[que->head_];
//}

//bool myque_isempty(bfpqueue_t *que)
//{
//    return que->head_ == que->tail_;
//}


// 其实这里是有问题的, 我给你一改
//bool myque_isfull(bfpqueue_t *que)
//{
//    return que->head_ == (que->tail_ + 1) % __BFPQUEUE_SIZE;
//}
