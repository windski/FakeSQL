#ifndef BPLUSTREE_H_
#define BPLUSTREE_H_

#include <unistd.h>
#include <sys/types.h>
#include <list>

#include <memory>


#define conv2file_p(f) (fdopen((f), "rw"))


namespace bplustree {

static const int _CHILDREN_NUMS = 100;
static const int _NO_PARENT = -1;
static const int _UNAVALIABLE = -1;


struct tree_node {
    explicit tree_node(off_t parent);

    bool leaf_flag_;
    off_t self_;
    off_t parent_;
    int keynum_;
    int keys_[_CHILDREN_NUMS - 1];
    char **values_;
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
    struct tree_node cur_node, cur_parent, root;

    off_t create_root() noexcept;

    struct tree_node get_root(void) const;

    // The function will load the structure of node to `cur_node'
    // may set the `cur_parent'?
    int seek_node(off_t node);
public:
    explicit BplusTree();
    ~BplusTree();
    void insert(int key, char *value);
    int search(const int ) const noexcept;

};

} // end of bplustree

#endif

