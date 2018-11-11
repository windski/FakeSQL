//
// Created by yurunyang on 18-11-6.
//

#ifndef BPLUSTREE_PRESISTBTREE_H
#define BPLUSTREE_PRESISTBTREE_H

#define  __BFPQUEUE_SIZE 8000000

#include "bplustree.h"
typedef struct BPlusNode_for_Persist BFP;
struct BPlusNode_for_Persist
{
    uint64_t  id;
    int KeyNum_;
    KeyType Key_[M + 1];
    ValueType Value_[M + 1];
    uint64_t ChildLists_[M + 1];
    uint64_t Next_;
};


typedef struct BFPqueue
{
    BFP data[__BFPQUEUE_SIZE];
    int head_;
    int tail_;
    int size_;
}bfpqueue_t;


/*将遍历到的节点放到缓冲区中*/
extern void NodeBuffer(bfpqueue_t * bfPqueue_,const BPlusTree T);

extern bfpqueue_t * BFPqueue_init();

extern void PersistBtree(const BPlusTree Root);

extern int WriteBFPqueToFile(char * filename,bfpqueue_t * bfPqueue,int size);



#endif //BPLUSTREE_PRESISTBTREE_H
