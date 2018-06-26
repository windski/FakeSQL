//
// Created by yurunyang on 18-6-23.
//
#ifndef B_TREE_INITIAL_HPP
#define B_TREE_INITIAL_HPP


#include "B-tree_nodes.hpp"
#include "iostream"
#include "string"
namespace  utlis{

    template <typename key_type,typename value_type>
    middle_node<key_type,value_type> * initial_B_tree(key_type key)
    {
        middle_node<key_type,value_type> * root =  new middle_node<key_type,value_type>;
        middle_node<key_type,value_type> * child_1 = new middle_node<key_type,value_type>;
        leaf_node<key_type,value_type> * leaf_node1 = new leaf_node<key_type,value_type>;
        root->insert(key,child_1);
        child_1->insert(key,leaf_node1);
        return  root;
    }



}

#endif
