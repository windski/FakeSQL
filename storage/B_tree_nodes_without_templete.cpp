//
// Created by yurunyang on 18-10-18.
//

#include <iostream>
#include <algorithm>
#include "B_tree_nodes_without_templete.h"
#include "B_tree_initial_without_templete.h"


using namespace utils;
namespace  utils{

    key_value_pair_for_middle_node::key_value_pair_for_middle_node
            (std::string key, middle_node *value):
            key(key),value(value){}

    void key_value_pair_for_middle_node::set_key(string set_key) {
        key = set_key;


    };

    void key_value_pair_for_middle_node::set_value(middle_node *set_value) {
        value = set_value;

    };


    off64_t  key_value_pair_for_middle_node::update_key() {

        string   maxvalue;
        maxvalue = value->updatekey();
    }

    key_value_pair_for_middle_node_which_next_node_is_leaf_node::key_value_pair_for_middle_node_which_next_node_is_leaf_node(
            string key, leaf_node *value):key(key),value(value) {

    }

    void key_value_pair_for_middle_node_which_next_node_is_leaf_node::set_key(string set_key) {
        key = set_key;

    }

    void key_value_pair_for_middle_node_which_next_node_is_leaf_node::update_key() {

            key= value->get_key();

    }

//    middle_node::middle_node(middle_node *_parent_node)
//            : parent_node(parent_node) {};

    void middle_node::set_manager(Manager *manager) {
        this->manager = manager;

    }

    void middle_node::set_parent_node(middle_node *parent_node) {
        this->parent_node = parent_node;
    }

    string middle_node::updatekey() {

        if (flag == 1) {

            typename deque<key_value_pair_for_middle_node_which_next_node_is_leaf_node >::iterator item1 =
                    key_value_pair_for_middle_node_which_next_node_is_leaf_node_t.begin();

            while (item1 != key_value_pair_for_middle_node_which_next_node_is_leaf_node_t.end() - 1) {
                item1->update_key();
                item1++;
            }

            sort();

            int stl_size = key_value_pair_for_middle_node_which_next_node_is_leaf_node_t.size();

            if (stl_size > 0) {
                typename deque<key_value_pair_for_middle_node_which_next_node_is_leaf_node >::iterator item =
                        key_value_pair_for_middle_node_which_next_node_is_leaf_node_t.end() - 1;

                //cout << item->key << "Maxkey" << endl;

                this->Maxkey = item->key;
                return Maxkey;

            } else
            {
                this->Maxkey= to_string(-2147483648);
                return to_string(-2147483648);
            }

        } else {


            deque<key_value_pair_for_middle_node>::iterator item1 = key_value_pair_for_middle_node_t.begin();

            while (item1 != key_value_pair_for_middle_node_t.end()) {
                Maxkey = item1->update_key();
                item1++;
            }


            int stl_size = key_value_pair_for_middle_node_t.size();

            //cout<< stl_size <<"   stl_size "<<endl;

            if (stl_size > 0) {
                deque<key_value_pair_for_middle_node >::iterator item =
                        key_value_pair_for_middle_node_t.end() - 1;
                //cout << item->key << "Maxkey" << endl;
                this->Maxkey = item->key;

                //cout<< item->key<<"Maxkey"<<endl;

                return Maxkey;

            } else
            {
                //cout <<"else"<<endl;
                return "aaaaaaaaaaaaaa";
            }

        }
    }


    string middle_node::get_key(int front_or_back) {
        if(flag==1)
        {
            if(front_or_back==0)
            {
                typename deque<key_value_pair_for_middle_node_which_next_node_is_leaf_node >::iterator item =
                        key_value_pair_for_middle_node_which_next_node_is_leaf_node_t.begin();
                return item->getkey();
            }
            if(front_or_back==1)
            {
                typename deque<key_value_pair_for_middle_node_which_next_node_is_leaf_node >::iterator item =
                        key_value_pair_for_middle_node_which_next_node_is_leaf_node_t.end()-1;
                return item->getkey();
            }

        }
        if(flag==0)
        {
            if(front_or_back==0)
            {
                typename deque< key_value_pair_for_middle_node > ::iterator item =key_value_pair_for_middle_node_t.begin();
                return item->getkey();
            }
            if(front_or_back==1)
            {
                typename deque< key_value_pair_for_middle_node > ::iterator item =key_value_pair_for_middle_node_t.end()-1;
                return item->getkey();
            }

        }
    }


    middle_node * middle_node::get_value_of_middle_node() {
        deque< key_value_pair_for_middle_node > ::iterator item =key_value_pair_for_middle_node_t.begin();
        return item->getvalue();
    }


    leaf_node * middle_node::get_value_of_leaf_node()
    {
        deque<key_value_pair_for_middle_node_which_next_node_is_leaf_node>::iterator iter
                = key_value_pair_for_middle_node_which_next_node_is_leaf_node_t.begin();

        return iter->getvalue();
    };


    void middle_node::delete_pair() {
        if (flag==0)
        {
            key_value_pair_for_middle_node_t.pop_front();
            used_pairs--;
        } else{
            key_value_pair_for_middle_node_which_next_node_is_leaf_node_t.pop_front();
            used_pairs--;
        }
    }


    points_struct * middle_node::searchkey(string key) {

        points_struct * points_struct_t = new points_struct;

        if(flag ==0)
        {

            deque< key_value_pair_for_middle_node > ::iterator item
                    =key_value_pair_for_middle_node_t.begin();

            while(item != key_value_pair_for_middle_node_t.end())
            {
                if(item->getkey() >= key)
                {
                    //cout<<item->getkey()<<endl;                                                      //
                    points_struct_t->flag =1;      //找到的是中间节点                                //
                    points_struct_t->leaf_node_point= nullptr;                                      //
                    points_struct_t->middle_node_point=item->getvalue();                             //
                    return points_struct_t;
                }
                item++;
            }
            //cout<<1<<endl;
            points_struct_t->flag=0;  //没有找到相关节点
            points_struct_t->middle_node_point= nullptr;
            points_struct_t->middle_node_point= nullptr;
            return points_struct_t;
        } else
        {

             deque<key_value_pair_for_middle_node_which_next_node_is_leaf_node>::iterator item
                    = key_value_pair_for_middle_node_which_next_node_is_leaf_node_t.begin();

            while(item != key_value_pair_for_middle_node_which_next_node_is_leaf_node_t.end())
            {
                if(item->getkey() >= key)
                {
                    points_struct_t->flag=2; //找到的是叶子节点
                    points_struct_t->leaf_node_point=item->getvalue();
                    points_struct_t->middle_node_point = nullptr;
                    return points_struct_t;
                }
                item++;

            }
            points_struct_t->flag=0;
            points_struct_t->middle_node_point= nullptr;
            points_struct_t->middle_node_point= nullptr;
            return points_struct_t;
        }


    }

    middle_node * middle_node::getParent_node() {

        if(this->parent_node==NULL)
        {
            middle_node * new_root = new middle_node;
            this->updatekey();
            new_root->insert(this->get_key(1),this);
            this->set_parent_node(new_root);
            (this->manager)->update_root(new_root);
            cout<<"parent_node has set"<<endl;


        }
        return parent_node;
    }

    int middle_node::insert(string  key , middle_node * value) {
        if(flag==1 )
            return 1; //子节点不可同时存在既有叶子节点又有中间节点的情况
        if(used_pairs>=10)
        {
            middle_node * new_middle_node = new middle_node;
            new_middle_node =  _split_middle_node(this);

            string new_middle_node_maxkey = new_middle_node->get_key(1);
            //cout<<size<<":size"<<endl;
            string leaf_node1_maxkey = value->get_key(1);
            if(new_middle_node_maxkey>= leaf_node1_maxkey)
            {
                new_middle_node->insert(value->get_key(1),value);
                value->set_parent_node(new_middle_node);
            } else
            {
                this->insert(value->get_key(1),value);
                value->set_parent_node(this);
            }

            return 0;
        }
        key_value_pair_for_middle_node_t.push_back( key_value_pair_for_middle_node  (key,value));
        value->set_parent_node(this);
        flag = 0;
        //this->key=key;
        this->used_pairs+=1;
        this->updatekey();
        sort();
        return 0;
    }

    int middle_node::insert(string  key , leaf_node * value) {
        if (flag == 0)
            return 1; //子节点不可同时存在既有叶子节点又有中间节点的情况

        middle_node *new_middle_node = new middle_node;
        if (used_pairs >= 10) {
            //cout<<"middle node has full,the key is "<<key<<endl;

            new_middle_node = _split_middle_node(this, value);
            //sort();

            string new_middle_node_maxkey = new_middle_node->get_key(1);
            //cout<<size<<":size"<<endl;
            string leaf_node1_maxkey = value->get_key();
            if (new_middle_node_maxkey >= leaf_node1_maxkey) {
                new_middle_node->insert(value->get_key(), value);
                value->set_parent(new_middle_node);
            } else {
                this->insert(value->get_key(), value);
                value->set_parent(this);
            }
            return 0;
        }
            ////////////////
            ///////////////下面的可能要剪掉
            value->set_parent(this);
            key_value_pair_for_middle_node_which_next_node_is_leaf_node_t.push_back
                    (key_value_pair_for_middle_node_which_next_node_is_leaf_node(key, value));
            flag = 1;
            //this->key= key;
            this->used_pairs += 1;
            sort();
            this->updatekey();
            return 1;

    }

    void middle_node::sort()
    {
        if(flag ==0)
            std::sort(key_value_pair_for_middle_node_t.begin()
                    ,key_value_pair_for_middle_node_t.end());
        if(flag ==1)
            std::sort(key_value_pair_for_middle_node_which_next_node_is_leaf_node_t.begin(),
                      key_value_pair_for_middle_node_which_next_node_is_leaf_node_t.end());
    }

    middle_node::~middle_node() {

        cout<<"delete middle_node --->>";
        delete parent_node;
        //delete manager;
        cout<<"delete succeed"<<endl;

    }




    /////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////
    ///////下面是叶子节点类


    leaf_node::
    leaf_node(middle_node * parent_node,
                         leaf_node * brother_node):parent_node(parent_node),brother_node(brother_node)
    {
        used_pairs=0;
        Max_key = "0";
        this->parent_node = parent_node;
        this->brother_node = brother_node;
    };


    string leaf_node::pop_key(int flag)
    {
        if(flag==0) {
         deque<key_value_pair>::iterator item = key_value_pairs.begin();
            return item->getkey();
        } else{
            typename  deque<key_value_pair>:: iterator item = key_value_pairs.end()-1;
            return item->getkey();
        }
    }

    off64_t leaf_node::pop_value() {
        deque<key_value_pair>::iterator item = key_value_pairs.begin();
        return item->getvalue();
    }

    
    int leaf_node::insert(string key, off64_t value) {
        if(used_pairs>=10)
        {

            // cout<<"this node has full,the key is "<<key<<endl;

            //leaf_node  *leaf_node1 = new leaf_node(parent_node);

            _split_leaf_node(parent_node,this);               //??????????
            parent_node->updatekey();
            _sort();
            Max_key = (key_value_pairs.end()-1)->key;
            return  -1 ;  //insert successed



            //return 0;  //该叶子节点已满,插入失败
        } else
        {
            //cout<<key<<endl;
            key_value_pair new_pair(key,value);  //初始化一个新的key_value_pair
            key_value_pairs.push_back(new_pair);   //加入到key_value_pairs 的deque 中
            used_pairs++;                       //当前已使用的pair加1
            _sort();
            Max_key = (key_value_pairs.end()-1)->key;
            return  1 ;  //insert successed
        }
    }
    
    
    void leaf_node::set_parent(middle_node *parent_node) {
        this->parent_node = parent_node;

    }

    int leaf_node::delete_pair(string key) {

        if(key == "0")
        {
            key_value_pairs.pop_front();
            used_pairs--;
            return 1;
        }
        deque< key_value_pair >::iterator iter= key_value_pairs.begin();
        while(iter!=key_value_pairs.end())
        {
            if(iter->getkey()==key)
            {
                iter->set_key("NULL");
                iter->set_value(-1);
                key_value_pairs.erase(iter);
                used_pairs--;
                //cout<<"delete";
                break;
            } else iter++;
        }
    }
    
    string leaf_node::get_key() {
        return  (key_value_pairs.end()-1)->getkey();
    }
    
    void leaf_node::_sort() {
        sort(key_value_pairs.begin(),key_value_pairs.end());

    }
    
    off64_t leaf_node::searchkey(string key) {
        deque<key_value_pair>::iterator item =  key_value_pairs.begin();
        while(item!=key_value_pairs.end())
        {
            if(item->getkey() == key)
            {
                //cout<<item->getkey();
                return item->getvalue();
            }
            item++;
        }
        return 0;
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////下面是公用的友元函数//////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////



    void  _split_leaf_node(middle_node* parent_node,leaf_node * leaf_node1)
    {

        leaf_node * new_leaf_node = new leaf_node();
        //parent_node->insert()
        //new_leaf_node->insert(key,value);
        for(int i=0;i<8;i++)
        {



            new_leaf_node->insert(leaf_node1->pop_key(),leaf_node1->pop_value());
            //cout<<"delete:"<<leaf_node1->pop_key()<<endl;
            leaf_node1->delete_pair();
        }

        parent_node->insert(new_leaf_node->pop_key(1),new_leaf_node);


    }

    middle_node * _split_middle_node(middle_node * middle_node1,leaf_node * leaf_node1) {


        middle_node *new_middle_node = new middle_node();
        for (int i = 0; i < 8; i++) {
            new_middle_node->insert(middle_node1->get_key(), middle_node1->get_value_of_leaf_node());
            middle_node1->delete_pair();
        }
        (middle_node1->getParent_node())->insert(new_middle_node->get_key(1), new_middle_node);
        return new_middle_node;
    }


    middle_node *  _split_middle_node(middle_node * middle_node1)
    {

        middle_node * new_middle_node = new middle_node;
        for(int i=0;i<8;i++)
        {
            new_middle_node->insert(middle_node1->get_key(),middle_node1->get_value_of_middle_node());
            middle_node1->delete_pair();
        }

//        middle_node  *parentttt =  middle_node1->getParent_node();
//        parentttt->insert(new_middle_node->get_key(1),new_middle_node);
//        int a;

        middle_node1->getParent_node()->insert(new_middle_node->get_key(1),new_middle_node);
        return  new_middle_node;
    }




    //template <typename key_type,typename value_type>   //叶节点内的sort函数
    bool operator< (key_value_pair  &s1 ,  key_value_pair  &s2)
    {
        return s1.key<s2.key;
    }

    leaf_node::~leaf_node() {

        cout<<"delete leaf_node---->>";

//        delete brother_node;
        cout<<"delete succeed"<<endl;

    }


    //template <typename key_type,typename value_type>                        //中间节点内的用于sort的友元函数
    bool operator< ( key_value_pair_for_middle_node  &s1, key_value_pair_for_middle_node  &s2)
    {
        return s1.key<s2.key;
    }

    key_value_pair_for_middle_node::~key_value_pair_for_middle_node() {

        cout<<"delete key_value_pair_for_middle_node---->>";
        //delete value;
        cout<<"delete succeed"<<endl;
    }

    //template <typename key_type,typename value_type>                     //下一个节点是叶子节点的中间节点的用于sort的友元函数
    bool operator< (key_value_pair_for_middle_node_which_next_node_is_leaf_node  &s1,
                    key_value_pair_for_middle_node_which_next_node_is_leaf_node  &s2)
    {
        return s1.key<s2.key;
    }

    key_value_pair_for_middle_node_which_next_node_is_leaf_node::~key_value_pair_for_middle_node_which_next_node_is_leaf_node() {

        cout<<"delete key_value_pair_for_middle_node_which_next_node_is_leaf_node --->>";
        //delete value;
        cout<<"delete succeed"<<endl;

    }


}



















