#ifndef BPLUSTREE_H_
#define BPLUSTREE_H_

#include <unistd.h>
#include <sys/types.h>
#include <list>

#include <memory>


#define conv2file_p(f) (fdopen((f), "rw"))


namespace bplustree {

static const int _CHILDREN_NUMS = 100;


struct tree_node {
    bool leaf_flag_;
    off_t self_;
    off_t parent_;
    int keynum_;
    int keys_[_CHILDREN_NUMS - 1];
    char values_[_CHILDREN_NUMS][32];
    off_t children_[_CHILDREN_NUMS];
    off_t next_leaf_;
};

inline bool is_leaf(struct tree_node &node)
{
    return node.leaf_flag_;
}

class BplusTree
{
private:
    off_t root_p;
    off_t cur_offset;
    off_t file_size;
    std::list<off_t> free_list;
    int tree_fd;
    std::shared_ptr<struct tree_node *> cur_node, cur_parent;

    off_t create_root();
    struct tree_node *alloc_node(int parnet);
    int destroy_node(struct tree_node *node);

    struct tree_node get_root(void) const;

    // The function will load the structure of node to `cur_node'
    // may set the `cur_parent'?
    int seek_node(off_t node);
public:
    explicit BplusTree();
    ~BplusTree();
    void insert(int key, char *value);
    int search(int ) const;

};

} // end of bplustree

#endif

