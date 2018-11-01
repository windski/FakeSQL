//
// Created by yurunyang on 18-10-19.
//

#ifndef THE_NEW_FAKE_SQL_B_TREE_INITIAL_WITHOUT_TEMPLETE_H
#define THE_NEW_FAKE_SQL_B_TREE_INITIAL_WITHOUT_TEMPLETE_H


#include "iostream"
#include "string"
#include "hyperfine_structure.cpp"
#include "bson_.h"
#include "B_tree_nodes_without_templete.h"
namespace utils {


    class Manager {
    private:
        //typedef middle_node middle_node_t;

        int whether_initialed = 0;
        middle_node *root;
        int maxdeepth; //表示当前这棵树的层数

    public:
        Manager(string key);
        ~Manager();
        void update_root(middle_node *newroot);

        void updata();

        middle_node  * initial_B_tree(string  key);

        off64_t data_search(string  key);

        int insert_data(string  key,off64_t value);
    };
}

#endif //THE_NEW_FAKE_SQL_B_TREE_INITIAL_WITHOUT_TEMPLETE_H
