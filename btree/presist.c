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

static BPlusTree findleafparent(const BPlusTree root)
{
    assert(root != NULL);
    if(root->Children[0]->Children[0] == NULL) {
        return root;
    }
    return findleafparent(root->Children[0]);
}


// 这个函数将遍历所有的叶子节点,并将叶子节点的数据放入data里面
static int tavelleafparent(BPlusTree root, struct BPlusNode (*data)[BUFFMAX])
{
    assert(root != NULL);
    assert(data != NULL);

    BPlusTree tmp = root;
    int i = 0;
    struct BPlusNode padding;
    memset(&padding, 0, sizeof(struct BPlusNode));

    for(; i < BUFFMAX; i++) {
        // 遍历一个父节点的所有孩子(也就是该节点下面的所有叶子节点)
        for(int j = 0; j < M + 1; j++, i++) {
            if(tmp->Children[j] == NULL) {
                (*data)[i] = padding;
                continue;
            }
            (*data)[i] = *tmp->Children[j];
        }

        // 一个父节点的所有孩子存好了,得到下一个父节点
        // 没有指向父节点的指针,这麻烦了...
    }

    /* while(tmp != NULL && i < BUFFMAX) {
     *     for(int j = 0; j < M + 1; j++) {
     *
     *     }
     *     (*data)[i] = *tmp;
     *
     *     tmp = tmp->Next;
     *     i++;
     * } */
    // 返回值纪录一共记录了多少个数据
    return i;
}

int presist_tree(int fd, const BPlusTree root)
{
    struct BPlusNode data[BUFFMAX];

    BPlusTree leafparent = findleafparent(root);

    int blocks = tavelleafparent(leafparent, &data);

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


