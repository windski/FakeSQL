//
// Created by yurunyang on 2018/8/23.
//

#include "file_read_write_system.h"
#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <cstring>

#include "memory"
#include <unistd.h>

using namespace std;
using  namespace utils;

basic_read_write::basic_read_write(char *namepath) {
    fd = ::open(namepath,O_RDWR,S_IREAD| S_IWUSR); //  only open the file when it has existed
    if(fd == -1)    // if the file not exist
    {
        fd = ::open(namepath,O_RDWR | O_CREAT,S_IREAD|S_IWUSR); // create the datafile
        if(fd == -1)
        {
            std::cout<<"open datafile error"<<std::endl;
            return ;
        }

        //char whethe_initial ='0';
        nowSeek = 0;
        write(fd,&nowSeek,sizeof(nowSeek));
        nowSeek+=8;
        cout<<sizeof(nowSeek);
        //wtdhbw = '0';
    }
    else
    {
        ::read(fd,&nowSeek,sizeof(off64_t));
        cout<<sizeof(nowSeek);

    }

}

basic_read_write::~basic_read_write()
{
    ::close(fd);
};

off64_t basic_read_write::write_bsonCouple(uint8_t *bsonBuf) {
    pwrite(fd,bsonBuf,500,this->nowSeek);
    off64_t  tempSeek_ = nowSeek;
    nowSeek+=500;
    pwrite(fd,&nowSeek,sizeof(off64_t),0);
    return  nowSeek;
}


struct Free
{
    void operator()(void *ptr)
    {
        free(ptr);
    }
};

shared_ptr<uint8_t >  basic_read_write::read_bsonCouple(off64_t seek) {
    std::shared_ptr<uint8_t> bufPtr((uint8_t*) malloc(500),Free());
    pread(fd,bufPtr.get(),500,seek);
    uint8_t * a= bufPtr.get();
    return bufPtr;
}


