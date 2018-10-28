//
// Created by yurunyang on 18-10-18.
//

#ifndef THE_NEW_FAKE_SQL_B_TREE_NODES_WITHOUT_TEMPLETE_H
#define THE_NEW_FAKE_SQL_B_TREE_NODES_WITHOUT_TEMPLETE_H

#include <deque>
#include "string"
#include "pub_friends.hpp"


using namespace std;
namespace utils {

    class key_value_pair_for_middle_node
    {
    public:
        std::string key;
        middle_node *value;

    public:
        key_value_pair_for_middle_node(std::string key=NULL,middle_node *value=NULL);

        string getkey(void){ return key;};

        middle_node * getvalue(void){ return  value;}

        void set_key(string set_key);

        void set_value(middle_node *set_value);

        off64_t update_key();

        friend bool operator< ( key_value_pair_for_middle_node &s1, key_value_pair_for_middle_node &s2);


    };






    class key_value_pair_for_middle_node_which_next_node_is_leaf_node
    {

    public:
        string key;
        leaf_node *value;

        key_value_pair_for_middle_node_which_next_node_is_leaf_node
                (string key=NULL,leaf_node *value = NULL);

        string getkey(void){
            return key;
        }

        leaf_node * getvalue(void){
            return value;
        }

        void set_key(string set_key);

        void set_value(leaf_node* set_value)
        {
            value = set_value;
        }

        void update_key();

        friend bool operator< (key_value_pair_for_middle_node_which_next_node_is_leaf_node&s1,
                               key_value_pair_for_middle_node_which_next_node_is_leaf_node &s2);


    };

    class  middle_node{
    private:
        middle_node * parent_node;
        utils::Manager * manager = nullptr;
        int flag = -1;
        int used_pairs = 0;
        string Maxkey;

        deque<key_value_pair_for_middle_node> key_value_pair_for_middle_node_t;
        deque<key_value_pair_for_middle_node_which_next_node_is_leaf_node>
                key_value_pair_for_middle_node_which_next_node_is_leaf_node_t;


    public:
        middle_node(middle_node * parent_node_ = nullptr){}

        void set_manager(Manager * manager);

        void set_parent_node(middle_node *parent_node);

        string updatekey();

        string get_key(int front_or_back = 0);

        middle_node  * get_value_of_middle_node();

        leaf_node * get_value_of_leaf_node();

        void delete_pair();

        int user_paires(){
            return  used_pairs;
        }

        points_struct * searchkey(string key);

        middle_node * getParent_node();

        int insert(string  key , middle_node * value);

        int insert(string  key , leaf_node * value);

        void sort();
    };

    /////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////
    ///////下面是叶子节点类


    class key_value_pair{
    public:

        string key;
        off64_t value;
    public:
        key_value_pair(string key,off64_t value):key(key),value(value){

        }
        string  getkey(void) { return key ; }
        off64_t getvalue(void) { return  value; }
        void set_key(string  set_key)
        {
            key = set_key;
        }

        void set_value(off64_t set_value )
        {
            value = set_value;
        }
    };

    class leaf_node{
    private:
        string  Max_key;
        //friend void _split(middle_node<key_type,value_type> * parent_node,leaf_node<key_type,value_type> * leaf_node1=nullptr);
        middle_node * parent_node ;//= new middle_node<key_type>;  //父亲节点
        leaf_node  * brother_node ;//= new leaf_node<key_type,value_type>;
        //deque<int> v = deque<int>(10, 0);
        //deque< key_value_pair<key_type,value_type> >  key_value_pairs  = deque< key_value_pair<key_type,value_type> >(1);
        deque<key_value_pair> key_value_pairs;
        int used_pairs;

    public:
        leaf_node(middle_node * parent_node= nullptr,
                  leaf_node * brother_node = nullptr);


        string pop_key(int flag=0);

        off64_t  pop_value();

        int insert(string key,off64_t value);
        void set_parent(middle_node * parent_node);

        middle_node * get_parent_node(){
            return parent_node;
        };


        int delete_pair(string  key="0");

        string get_key();

        void _sort();

        off64_t searchkey(string key);

        friend bool operator< (key_value_pair &s1 ,  key_value_pair &s2);

    };



    ////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////下面是公用的友元函数//////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////


}
#endif //THE_NEW_FAKE_SQL_B_TREE_NODES_WITHOUT_TEMPLETE_H
