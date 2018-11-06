//
// Created by falleuion on 11/5/18.
//

#include "myque.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

myque_t *myque_init()
{
    myque_t *data = (myque_t *)malloc(sizeof(myque_t));
    assert(data != NULL);

    data->head_ = data->tail_ = 0;
    data->size_ = 0;

    return data;
}


void myque_destory(myque_t *data)
{
    assert(data != NULL);
    assert(data->data != NULL);

    free(data);
}


int myque_append(myque_t *que, myque_data_t data_)
{
    if(myque_isfull(que)) {
        return -1;
    }

    que->size_++;
    que->data[que->tail_] = data_;
    que->tail_ = (que->tail_ + 1) % __QUE_SIZE;

    return 0;
}

//这一段写的真香,借走了嘿嘿嘿

int myque_pop(myque_t *que)
{
    if(myque_isfull(que)) {
        return -1;
    }

    que->size_--;
    que->head_ = (que->head_ + 1) % __QUE_SIZE;

    return 0;
}

myque_data_t myque_top(myque_t *que)
{
    return que->data[que->head_];
}

bool myque_isempty(myque_t *que)
{
    return que->head_ == que->tail_;
}

bool myque_isfull(myque_t *que)
{
    return que->head_ == (que->tail_ + 1) % __QUE_SIZE;
}
