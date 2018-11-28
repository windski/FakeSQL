#include "bplustree.h"
#include <sys/stat.h>
#include <fcntl.h>
#include <cstdio>

namespace bplustree {

static const int _NO_PARENT = -1;

    BplusTree::BplusTree()
        : root_p(0), free_list()
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
        struct tree_node *root = alloc_node(_NO_PARENT);
        write(tree_fd, root, sizeof(struct tree_node));
        return ftello(conv2file_p(tree_fd));
    }

    struct tree_node *
    BplusTree::alloc_node(int parent)
    {
        struct tree_node *root = new struct tree_node;
        root->leaf_flag_ = false;
        root->parent_ = parent;
        root->next_leaf_ = -1;

        return root;
    }


    int
    BplusTree::insert(int value)
    {
        // TODO: complete

        return 0;
    }

} // end of bplustree


