//
// Created by yurunyang on 18-11-6.
//

#include <stdbool.h>
#include "bplustree.h"
#include "presistBtree.h"


void NodeBuffer(struct BFPqueue * bfPqueue_, const BPlusTree T) {


        if(bfPqueue_==NULL)
            assert(bfPqueue_!=NULL);

        int keyNum = T->KeyNum;
        if(bfPqueue_->size_>=__BFPQUEUE_SIZE)
        {
            //WRITE bfPqueue TO FILE

            bfPqueue_->size_==0;
            bfPqueue_->head_==0;
            bfPqueue_->tail_==0;

        } else
        {
            bfPqueue_->data[bfPqueue_->tail_].id=T->id;
            //bfPqueue_[bfPqueue_->tail_].data->id=T->id;
            for(int i=0;i<keyNum;i++)
            {
                bfPqueue_->data[bfPqueue_->tail_].Key_[i] = T->Key[i];
                bfPqueue_->data[bfPqueue_->tail_].Value_[i] =T->Value[i];
                if(bfPqueue_->data[bfPqueue_->tail_].Next_)
                    bfPqueue_->data[bfPqueue_->tail_].Next_ = T->Next->id;
                if(bfPqueue_->data[bfPqueue_->tail_].ChildLists_[i])
                    bfPqueue_->data[bfPqueue_->tail_].ChildLists_[i] = T->Children[i]->id;
            }


            bfPqueue_->size_++;
            bfPqueue_->tail_++;//= (bfPqueue_->tail_+1) % __BFPQUEUE_SIZE;

        }



}

void PersistBtree(const BPlusTree Root) {

    Position Tmp;
    int i;
    if (Root == NULL)
        return ;
    printf("All Data:");
    Tmp = Root;

    bfpqueue_t * bfpque = BFPqueue_init();

    while (Tmp->Children[0] != NULL)
    {
        NodeBuffer(bfpque,Tmp);
        Tmp = Tmp->Children[0];

    }
    /* 第一片树叶 */
    while (Tmp != NULL){
        i = 0;
        while (i < Tmp->KeyNum)
        {
            NodeBuffer(bfpque,Tmp);
            printf(" %d",Tmp->Key[i++]);


        }
        Tmp = Tmp->Next;
    }

}


bfpqueue_t * BFPqueue_init()
{
    bfpqueue_t * data = (bfpqueue_t*)malloc(sizeof(bfpqueue_t));
    assert(data);

    data->size_=0;
    data->tail_=data->head_=0;
    return data;

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

//bool myque_isfull(bfpqueue_t *que)
//{
//    return que->tail_ == __BFPQUEUE_SIZE - 1 + que->head_;
//}
