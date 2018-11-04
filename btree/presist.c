#include "presist.h"
#include <assert.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int openfile(const char *src)
{
    assert(src != NULL);
    int fd = open(src, O_CREAT | O_RDWR, 0664);
    if(fd == -1) {
        perror("Couldn't open the file.");
        exit(-1);
    }

    return fd;
}


void closefile(int fd)
{
    assert(fd != 0);
    close(fd);
}

static BPlusTree findleaf(const BPlusTree root)
{
    assert(root != NULL);
    if(root->Children[0] == NULL) {
        return root;
    }
    return findleaf(root->Children[0]);
}


static int tavelleaf(BPlusTree root, struct BPlusNode (*data)[BUFFMAX])
{
    assert(root != NULL);
    assert(data != NULL);

    BPlusTree tmp = root;
    int i = 0;
    while(tmp != NULL) {
        for(int j = 0; i < BUFFMAX && j < root->KeyNum; i++, j++) {
            (*data)[i] = *(root);
        }
    
        tmp = tmp->Next;
    }
    // 返回值纪录一共记录了多少个数据
    return i;
}

int presist_tree(int fd, const BPlusTree root)
{
    struct BPlusNode data[BUFFMAX];

    BPlusTree leaf = findleaf(root);

    int blocks = tavelleaf(leaf, &data);

    ssize_t size = 0;
    char buf[sizeof(struct BPlusNode)];
    for(int i = 0; i < blocks; i++) {
        // write to the file
        memcpy(buf, &data[i], sizeof(buf));
        if((size = write(fd, buf, sizeof(buf))) == -1) {
            perror("write error");
            closefile(fd);
            return -1;
        }

        memset(buf, 0, sizeof(buf));
    }
    return 0;
}


