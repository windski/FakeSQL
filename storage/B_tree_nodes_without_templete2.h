//
// Created by yurunyang on 18-10-18.
//

#ifndef THE_NEW_FAKE_SQL_B_TREE_NODES_WITHOUT_TEMPLETE_H
#define THE_NEW_FAKE_SQL_B_TREE_NODES_WITHOUT_TEMPLETE_H

#include <deque>
#include <string>
#include "pub_friends.hpp"
#include <cassert>
#include <memory>


namespace utils {

    class key_value_pair_for_middle_node
    {
    private:
        std::string key;
        middle_node *value;

    public:
        key_value_pair_for_middle_node(std::string key = NULL,
                middle_node *value = NULL);

        std::string getkey(void) { return key; }

        middle_node *getvalue(void) { return  value; }

        void set_key(std::string set_key);

        void set_value(middle_node *set_value);

        off64_t update_key();

        friend bool operator<(key_value_pair_for_middle_node &s1,
                key_value_pair_for_middle_node &s2);

    };


    class key_value_pair_for_middle_node_which_next_node_is_leaf_node
    {
    private:
        std::string key;
        leaf_node *value;

    public:
        key_value_pair_for_middle_node_which_next_node_is_leaf_node(
                std::string key = NULL,
                leaf_node *value = NULL);

        std::string getkey(void) { return key; }

        leaf_node *getvalue(void) { return value; }

        void set_key(std::string set_key);

        void set_value(leaf_node *set_value) { value = set_value; }

        void update_key();

        friend bool operator<(
               key_value_pair_for_middle_node_which_next_node_is_leaf_node &s1,
               key_value_pair_for_middle_node_which_next_node_is_leaf_node &s2);
    };

    class middle_node
    {
    private:
        middle_node * parent_node;
        utils::Manager * manager;
        int flag;
        int used_pairs;
        std::string Maxkey;

        std::deque<key_value_pair_for_middle_node> key_value_pair_for_middle_node_t;
        std::deque<key_value_pair_for_middle_node_which_next_node_is_leaf_node>
                key_value_pair_for_middle_node_which_next_node_is_leaf_node_t;


    public:
        middle_node(middle_node * parent_node_ = nullptr);

        void set_manager(Manager * manager);

        void set_parent_node(middle_node *parent_node);

        std::string updatekey();

        std::string get_key(int front_or_back = 0);

        middle_node  *get_value_of_middle_node();

        leaf_node *get_value_of_leaf_node();

        void delete_pair();

        int user_paires() { return  used_pairs; }

        points_struct * searchkey(std::string key);

        middle_node * getParent_node();

        int insert(std::string key, middle_node * value);

        int insert(std::string key, leaf_node * value);

        void sort();
    };

    /////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////
    ///////下面是叶子节点类


    class key_value_pair
    {
    private:
        std::string key;
        off64_t value;
    public:
        key_value_pair(std::string key, off64_t value)
            : key(key), value(value)
        {}

        std::string getkey(void) { return key; }
        off64_t getvalue(void) { return  value; }

        void set_key(std::string set_key)
        {
            key = set_key;
        }

        void set_value(off64_t set_value)
        {
            value = set_value;
        }

        friend bool operator<(key_value_pair &, key_value_pair &);
    };


    class leaf_node{
    private:
        std::string  Max_key;
        middle_node *parent_node;
        leaf_node  *brother_node;
        std::deque<key_value_pair> key_value_pairs;
        int used_pairs;

    public:
        leaf_node(middle_node * parent_node= nullptr,
                  leaf_node * brother_node = nullptr);


        std::string pop_key(int flag = 0);

        off64_t  pop_value();

        int insert(std::string key,off64_t value);
        void set_parent(middle_node *parent_node);

        middle_node * get_parent_node(){
            return parent_node;
        }

        int delete_pair(std::string key="0");

        std::string get_key();

        void _sort();

        off64_t searchkey(std::string key);

        friend bool operator< (key_value_pair &s1 ,  key_value_pair &s2);

    };


} // end of utils


#endif //THE_NEW_FAKE_SQL_B_TREE_NODES_WITHOUT_TEMPLETE_H
