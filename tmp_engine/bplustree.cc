#include "bplustree.h"
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <cstdio>
#include <cstring>
#include <cassert>

#include <algorithm>

namespace bplustree {

static const int _NO_PARENT = -1;
static const int _UNAVALIABLE = -1;

    BplusTree::BplusTree()
        : root_p(0), free_list(), cur_parent(nullptr)
    {
        tree_fd = ::open("index.db", O_CREAT | O_RDWR, 0644);
        cur_offset = create_root();
    }

    BplusTree::~BplusTree()
    {
        ::close(tree_fd);
    }

    off_t
    BplusTree::create_root()
    {
        cur_node = std::make_shared<struct tree_node *>(alloc_node(_NO_PARENT));
        static char buff[sizeof(struct tree_node) + 1];
        memcpy(buff, cur_node.get(), sizeof(struct tree_node));

        if (write(tree_fd, buff, sizeof(struct tree_node)) < 0) {
            perror("tree node create failed");
            exit(-1);
        }

        off_t self_offt = ftello(conv2file_p(tree_fd));
        (*cur_node)->self_ = self_offt;
        (*cur_node)->leaf_flag_ = true;

        return self_offt;
    }

    struct tree_node *
    BplusTree::alloc_node(int parent)
    {
        struct tree_node *root = new struct tree_node;
        root->leaf_flag_ = false;
        root->parent_ = parent;
        root->next_leaf_ = -1;

        for (int i = 0; i < _CHILDREN_NUMS - 1; i++) {
            root->keys_[i] = _UNAVALIABLE;
        }

        for (int i = 0; i < _CHILDREN_NUMS; i++) {
            root->children_[i] = _UNAVALIABLE;
        }

        return root;
    }

    struct tree_node
    BplusTree::get_root(void) const
    {
        struct tree_node tmp;
        int size;
        if((size = pread(tree_fd, &tmp, 1, root_p)) < 0) {
            perror("get root node failed");
            exit(-1);
        }

        return tmp;
    }

    void
    BplusTree::insert(int key, char *value)
    {
        assert(cur_offset != 0);

        struct tree_node node = get_root();
        if(is_leaf(node)) {
            // TODO: Just insert into the leaf node if it not full...
        }
    }


    int
    BplusTree::seek_node(off_t node)
    {
        cur_node = std::make_shared<struct tree_node *>(new struct tree_node);


        return 0;
    }

} // end of bplustree


