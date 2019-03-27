#include "bplustree.h"
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <cstdio>
#include <cstring>
#include <cassert>

#include <algorithm>

namespace bplustree {

    tree_node::tree_node(off_t parent) :
            leaf_flag_(false), parent_(parent),
            next_leaf_(-1), values_(nullptr),
            keynum_(0)
    {
        for(auto &i : keys_) {
            i = _UNAVALIABLE;
        }

        for(auto &i : children_) {
            i = _UNAVALIABLE;
        }
    }


    BplusTree::BplusTree()
        : root_p(0), free_list(), cur_parent(-1),
        cur_node(-1), root(-1)
    {
        tree_fd = ::open("./index.db", O_CREAT | O_RDWR, 0644);
        cur_offset = create_root();
        // storage the root_node offset.
        root_p = cur_offset;
    }

    BplusTree::~BplusTree()
    {
        ::close(tree_fd);
    }

    off_t
    BplusTree::create_root() noexcept
    {
        assert(&root);

        static char buff[sizeof(struct tree_node) + 1];
        memcpy(buff, &root, sizeof(struct tree_node));

        if (write(tree_fd, buff, sizeof(struct tree_node)) < 0) {
            perror("tree node create failed");
            exit(-1);
        }

        off_t self_offt = ftello(conv2file_p(tree_fd));
        root.self_ = self_offt;
        root.leaf_flag_ = true;

        return self_offt;
    }

    struct tree_node
    BplusTree::get_root(void) const
    {
//        struct tree_node tmp(-1);
//        ssize_t size;
//        if((size = pread(tree_fd, &tmp, 1, root_p)) < 0) {
//            perror("get root node failed");
//            exit(-1);
//        }

        return root;
    }

    void
    BplusTree::insert(int key, char *value)
    {
        assert(cur_offset != 0);
        assert(value != nullptr);

        struct tree_node node = get_root();
        if(is_leaf(node)) {
            // TODO: Just insert into the leaf node if it not full...
        }
    }


    int
    BplusTree::seek_node(off_t node)
    {
        assert(&cur_node);

        ssize_t size;
        if((size = pread(tree_fd, &cur_node, 1, node)) < 0) {
            perror("seek node failure");
            return -1;
        }

        return 0;
    }

    int
    BplusTree::search(const int key) const noexcept
    {

    }

} // end of bplustree


