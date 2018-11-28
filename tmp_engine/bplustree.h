#ifndef BPLUSTREE_H_
#define BPLUSTREE_H_

#include <unistd.h>
#include <sys/types.h>
#include <list>


#define conv2file_p(f) (fdopen((f), "rw"))


namespace bplustree {

static const size_t _CHILDREN_NUMS = 100;


struct tree_node {
    bool leaf_flag_;
    off_t parent_;
    int keys_[_CHILDREN_NUMS - 1];
    off_t children_[_CHILDREN_NUMS];
    off_t next_leaf_;
};

class BplusTree
{
private:
    off_t root_p;
    off_t cur_offset;
    std::list<off_t> free_list;
    int tree_fd;

    off_t create_root();
    struct tree_node *alloc_node(int parnet);
    int destroy_node(struct tree_node *node);
public:
    explicit BplusTree();
    ~BplusTree();
    int insert(int );
    int search(int ) const;

};

} // end of bplustree

#endif

