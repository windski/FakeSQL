//
// Created by falleuion on 11/5/18.
//

#ifndef MYQUE_H_
#define MYQUE_H_

#include "bplustree.h"

#include <stdbool.h>

#define __QUE_SIZE 20480000
typedef struct BPlusNode * myque_data_t;

typedef struct myque {
    myque_data_t data[__QUE_SIZE];
    int head_;
    int tail_;
    int size_;
} myque_t;

extern myque_t *myque_init();
extern void myque_destory(myque_t *que);
extern int myque_append(myque_t *que, myque_data_t data_);
extern int myque_pop(myque_t *que);
extern myque_data_t myque_top(myque_t *que);
extern bool myque_isempty(myque_t *que);
extern bool myque_isfull(myque_t *que);

#endif //MYQUE_H_
