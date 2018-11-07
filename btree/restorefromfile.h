//
// Created by yurunyang on 18-11-7.
//

#ifndef BPLUSTREE_RESTOREFROMFILE_H
#define BPLUSTREE_RESTOREFROMFILE_H

#include "bplustree.h"
#include "presistBtree.h"

/*用来restore的函数, 会调用rebuildBtree这个函数*/
BPlusTree Restore(char * filename);

/*从bfpqueue中rebuildBtree*/
int rebuildBtree(BPlusTree T,BFP bfp);

int rebuildNode()

#endif //BPLUSTREE_RESTOREFROMFILE_H
