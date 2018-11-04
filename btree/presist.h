#ifndef PRESIST_H_
#define PRESIST_H_

#include "bplustree.h"

#define BUFFMAX 1024

extern int openfile(const char *src);

extern void closefile(int fd);

extern int presist_tree(int fd, const BPlusTree root);

extern int restore_tree(int fd, BPlusTree root);

#endif //end of PRESIST_H_
