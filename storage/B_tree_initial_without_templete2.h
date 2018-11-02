//
// Created by yurunyang on 18-10-19.
//

#ifndef THE_NEW_FAKE_SQL_B_TREE_INITIAL_WITHOUT_TEMPLETE_H
#define THE_NEW_FAKE_SQL_B_TREE_INITIAL_WITHOUT_TEMPLETE_H


#include <iostream>
#include <string>
#include "B_tree_nodes_without_templete2.h"
#include "hyperfine_structure.cpp"
#include <cassert>
#include <memory>

namespace utils {

    typedef std::shared_ptr<middle_node *> middle_node_s_pt;
    typedef std::shared_ptr<leaf_node *> leaf_node_s_pt;
    typedef std::weak_ptr<middle_node *> middle_node_w_pt;

    class Manager {
    private:
        int whether_initialed;
        middle_node_s_pt root;
        int maxdeepth; //表示当前这棵树的层数

    public:
        Manager(std::string key);
        Manager(const char *);

        void update_root(middle_node *newroot);

        void updata();

        middle_node *initial_B_tree(std::string key);

        off64_t data_search(std::string key);

        int insert_data(std::string  key,off64_t value);
    };

} // end of utils

#endif //THE_NEW_FAKE_SQL_B_TREE_INITIAL_WITHOUT_TEMPLETE_H
