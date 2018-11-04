//
// Created by yurunyang on 18-10-18.
//

#include <iostream>
#include <algorithm>
#include "B_tree_nodes_without_templete.h"
#include "B_tree_initial_without_templete.h"
#include <cstring>

namespace utils {

    key_value_pair_for_middle_node::key_value_pair_for_middle_node(std::string key,
            middle_node *value)
        : key(key), value(value)
    {
    }

    void
    key_value_pair_for_middle_node::set_key(std::string set_key)
    {
        key = set_key;
    }

    void
    key_value_pair_for_middle_node::set_value(middle_node *set_value)
    {
        value = set_value;
    }


    off64_t
    key_value_pair_for_middle_node::update_key()
    {
        std::string maxvalue;
        maxvalue = value->updatekey();

        // TODO: return a value ???
        // 你不写返回,安我先随便写一个.....
        return (off64_t)1;
    }


    key_value_pair_for_middle_node_which_next_node_is_leaf_node::
        key_value_pair_for_middle_node_which_next_node_is_leaf_node(
                std::string key, leaf_node *value)
        : key(key), value(value)
    {}

    void
    key_value_pair_for_middle_node_which_next_node_is_leaf_node::
        set_key(std::string set_key)
    {
        key = set_key;
    }

    void 
    key_value_pair_for_middle_node_which_next_node_is_leaf_node::
    update_key()
    {
        key= value->get_key();
    }


    middle_node::middle_node(middle_node *_parent_node)
        : parent_node(_parent_node), manager(nullptr),
        flag(-1), used_pairs(0)
    {
    }

    void
    middle_node::set_manager(Manager *manager)
    {
        this->manager = manager;
    }

    void
    middle_node::set_parent_node(middle_node *parent_node)
    {
        this->parent_node = parent_node;
    }

    std::string
    middle_node::updatekey()
    {
        if (flag == 1) {
            auto item1 = kvpair_for_midnode_which_nextnode_is_leafnode.begin();

            while (item1 !=
                    kvpair_for_midnode_which_nextnode_is_leafnode.end() - 1) {

                item1->update_key();
                item1++;
            }

            sort();

            int stl_size = kvpair_for_midnode_which_nextnode_is_leafnode.size();

            if (stl_size > 0) {
                auto item =
                    kvpair_for_midnode_which_nextnode_is_leafnode.end() - 1;

                // 直接把成员属性放在public下...这是c??,那还不如直接写struct...
                // 已经换成了getkey()
                this->Maxkey = item->getkey();
                return Maxkey;
            } else {
                this->Maxkey = std::to_string(-2147483648);
                return std::to_string(-2147483648);
            }
        } else {
            auto item1 = kvpair_for_middle_node.begin();

            while(item1 != kvpair_for_middle_node.end()) {
                Maxkey = item1->update_key();
                item1++;
            }

            int stl_size = kvpair_for_middle_node.size();

            //std::cout<< stl_size <<"   stl_size "<<std::endl;

            if (stl_size > 0) {
                auto item = kvpair_for_middle_node.end() - 1;
                this->Maxkey = item->getkey();

                return Maxkey;
            } else {
                // return "aaa" ?????
                return "aaaaaaaaaaaaaa";
            }
        }
    }


    std::string middle_node::get_key(int front_or_back)
    {
        // TODO: 这里应该被重新设计!
        if(flag == 1)
        {
            if(front_or_back == 0) {
                std::deque<key_value_pair_for_middle_node_which_next_node_is_leaf_node>::
                    iterator item =
                    kvpair_for_midnode_which_nextnode_is_leafnode.begin();
                return item->getkey();
            }

            if(front_or_back == 1) {
                std::deque<key_value_pair_for_middle_node_which_next_node_is_leaf_node>::
                    iterator item =
                    kvpair_for_midnode_which_nextnode_is_leafnode.end() - 1;
                return item->getkey();
            }
        }

        if(flag == 0) {
            if(front_or_back == 0) {
                std::deque<key_value_pair_for_middle_node>::
                    iterator item = kvpair_for_middle_node.begin();
                return item->getkey();
            }
            if(front_or_back==1)
            {
                std::deque<key_value_pair_for_middle_node>::
                    iterator item = kvpair_for_middle_node.end() - 1;
                return item->getkey();
            }
        }

    }


    middle_node *
    middle_node::get_value_of_middle_node()
    {
        std::deque<key_value_pair_for_middle_node>::
            iterator item = kvpair_for_middle_node.begin();
        return item->getvalue();
    }


    leaf_node * middle_node::get_value_of_leaf_node()
    {
        std::deque<key_value_pair_for_middle_node_which_next_node_is_leaf_node>::
            iterator iter =
                kvpair_for_midnode_which_nextnode_is_leafnode.begin();

        return iter->getvalue();
    }


    void middle_node::delete_pair()
    {
        if (flag == 0) {
            kvpair_for_middle_node.pop_front();
            used_pairs--;
        } else {
            kvpair_for_midnode_which_nextnode_is_leafnode.pop_front();
            used_pairs--;
        }
    }


    points_struct
    middle_node::searchkey(std::string key)
    {
        // TODO:最后没有返回值, 设计有问题, 有个多余的if-else
        points_struct points;
        // 在这里直接初始化, 全为0
        memset(&points, 0, sizeof(points_struct));

        // 找到了, 填写进去返回; 没找到, 直接返回就好
        if(flag == 0) {
            auto item = kvpair_for_middle_node.begin();

            while(item != kvpair_for_middle_node.end()) {
                if(item->getkey() >= key) {
                    points.flag = 1;      //找到的是中间节点
                    points.leaf_node_point= nullptr; 
                    points.middle_node_point = item->getvalue();
                    return points;
                }
                item++;
            }

            return points;
        } else {
            auto item = kvpair_for_midnode_which_nextnode_is_leafnode.begin();

            while(kvpair_for_midnode_which_nextnode_is_leafnode.end() != 
                    item) {
                if(item->getkey() >= key) {
                    points.flag=2; //找到的是叶子节点
                    points.leaf_node_point=item->getvalue();
                    points.middle_node_point = nullptr;
                    return points;
                }
                item++;
            }

            return points;
        }
    }

    middle_node *
    middle_node::getParent_node()
    {
        if(this->parent_node == NULL) {
            middle_node * new_root = new middle_node;
            this->updatekey();

            new_root->insert(this->get_key(1), this);
            this->set_parent_node(new_root);
            
            (this->manager)->update_root(new_root);
            std::cout<<"parent_node has set"<<std::endl;

        }
        return parent_node;
    }

    int
    middle_node::insert(std::string key, middle_node *value)
    {
        if(flag == 1) {
            return 1; //子节点不可同时存在既有叶子节点又有中间节点的情况
        }

        if(used_pairs >= 10) {
            middle_node * new_middle_node = nullptr;
            new_middle_node = _split_middle_node(this);

            std::string new_middle_node_maxkey = new_middle_node->get_key(1);
            std::string leaf_node1_maxkey = value->get_key(1);

            if(new_middle_node_maxkey >= leaf_node1_maxkey) {
                new_middle_node->insert(value->get_key(1),value);
                value->set_parent_node(new_middle_node);
            } else {
                this->insert(value->get_key(1),value);
                value->set_parent_node(this);
            }

            return 0;
        }

        kvpair_for_middle_node.push_back(key_value_pair_for_middle_node(key, value));
        value->set_parent_node(this);

        flag = 0;
        //this->key=key;
        this->used_pairs += 1;
        this->updatekey();
        sort();

        return 0;
    }

    int
    middle_node::insert(std::string key, leaf_node *value)
    {
        if (flag == 0)
            return 1; //子节点不可同时存在既有叶子节点又有中间节点的情况

        middle_node *new_middle_node = nullptr;
        if (used_pairs >= 10) {
            //std::cout<<"middle node has full,the key is "<<key<<std::endl;

            new_middle_node = _split_middle_node(this, value);
            //sort();

            std::string new_middle_node_maxkey = new_middle_node->get_key(1);
            //std::cout<<size<<":size"<<std::endl;
            std::string leaf_node1_maxkey = value->get_key();

            if (new_middle_node_maxkey >= leaf_node1_maxkey) {
                new_middle_node->insert(value->get_key(), value);
                value->set_parent(new_middle_node);
            } else {
                this->insert(value->get_key(), value);
                value->set_parent(this);
            }

            return 0;
        }

            ///////////////下面的可能要剪掉
            value->set_parent(this);
            kvpair_for_midnode_which_nextnode_is_leafnode.push_back(
                    key_value_pair_for_middle_node_which_next_node_is_leaf_node(key, value));
            flag = 1;

            this->used_pairs += 1;
            sort();
            this->updatekey();

            return 1;
    }

    void
    middle_node::sort()
    {
        if(flag == 0) {
            std::sort(kvpair_for_middle_node.begin(),
                    kvpair_for_middle_node.end());
        }

        if(flag == 1)
            std::sort(kvpair_for_midnode_which_nextnode_is_leafnode.begin(),
                    kvpair_for_midnode_which_nextnode_is_leafnode.end());
    }




    /////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////
    ///////下面是叶子节点类


    leaf_node::leaf_node(middle_node * parent_node, leaf_node * brother_node)
        : parent_node(parent_node), brother_node(brother_node)
    {
        used_pairs=0;
        Max_key = "0";
        this->parent_node = parent_node;
        this->brother_node = brother_node;
    }


    std::string
    leaf_node::pop_key(int flag)
    {
        if(flag == 0) {
            std::deque<key_value_pair>::iterator item = key_value_pairs.begin();
            return item->getkey();
        } else {
            std::deque<key_value_pair>::iterator item = key_value_pairs.end() - 1;
            return item->getkey();
        }
    }

    off64_t
    leaf_node::pop_value()
    {
        std::deque<key_value_pair>::iterator item = key_value_pairs.begin();
        return item->getvalue();
    }

    
    int
    leaf_node::insert(std::string key, off64_t value)
    {
        if(used_pairs >= 10) {

            // std::cout<<"this node has full,the key is "<<key<<std::endl;

            //leaf_node  *leaf_node1 = new leaf_node(parent_node);

            _split_leaf_node(parent_node,this);               //??????????
            parent_node->updatekey();
            _sort();
            Max_key = (key_value_pairs.end() - 1)->getkey();

            return  -1 ;  //insert successed
            //return 0;  //该叶子节点已满,插入失败
        } else {
            //std::cout<<key<<std::endl;
            key_value_pair new_pair(key,value);  //初始化一个新的key_value_pair
            key_value_pairs.push_back(new_pair);   //加入到key_value_pairs 的deque 中
            used_pairs++;                       //当前已使用的pair加1
            _sort();
            Max_key = (key_value_pairs.end() - 1)->getkey();
            return  1 ;  //insert successed
        }
    }
    
    
    void
    leaf_node::set_parent(middle_node *parent_node)
    {
        this->parent_node = parent_node;
    }

    int
    leaf_node::delete_pair(std::string key)
    {
        if(key == "0") {
            key_value_pairs.pop_front();
            used_pairs--;
            return 1;
        }

        std::deque<key_value_pair>::iterator iter = key_value_pairs.begin();
        while(iter != key_value_pairs.end()) {
            if(iter->getkey() == key) {
                iter->set_key("NULL");
                iter->set_value(-1);
                key_value_pairs.erase(iter);
                used_pairs--;
                //std::cout<<"delete";
                break;
            } else {
                iter++;
            }
        }

        return -1;
    }
    
    std::string
    leaf_node::get_key()
    {
        return (key_value_pairs.end()-1)->getkey();
    }
    
    void
    leaf_node::_sort()
    {
        sort(key_value_pairs.begin(),key_value_pairs.end());
    }
    

    off64_t
    leaf_node::searchkey(std::string key)
    {
        std::deque<key_value_pair>::iterator item = key_value_pairs.begin();
        while(item != key_value_pairs.end()) {
            if(item->getkey() == key) {
                //std::cout<<item->getkey();
                return item->getvalue();
            }

            item++;
        }

        return 0;
    }

/**
 * 下面是公用的友元函数
 */

    void
    _split_leaf_node(middle_node *parent_node,leaf_node *leaf_node1)
    {
        leaf_node * new_leaf_node = new leaf_node;
        //parent_node->insert()
        //new_leaf_node->insert(key,value);
        for(int i = 0; i < 5; i++) {
            new_leaf_node->insert(leaf_node1->pop_key(),leaf_node1->pop_value());
            //std::cout<<"delete:"<<leaf_node1->pop_key()<<std::endl;
            leaf_node1->delete_pair();
        }

        parent_node->insert(new_leaf_node->pop_key(1),new_leaf_node);
    }

    middle_node *
    _split_middle_node(middle_node *middle_node1, leaf_node *leaf_node1)
    {
        auto new_middle_node = new middle_node;

        for (int i = 0; i < 5; i++) {
            new_middle_node->insert(middle_node1->get_key(),
                    middle_node1->get_value_of_leaf_node());
            middle_node1->delete_pair();
        }

        (middle_node1->getParent_node())->insert(new_middle_node->get_key(1),
                new_middle_node);
        return new_middle_node;
    }


    middle_node *
    _split_middle_node(middle_node *middle_node1)
    {
        auto new_middle_node = new middle_node;

        for(int i = 0; i < 5; i++) {
            new_middle_node->insert(middle_node1->get_key(),
                    middle_node1->get_value_of_middle_node());
            middle_node1->delete_pair();
        }

//        middle_node  *parentttt =  middle_node1->getParent_node();
//        parentttt->insert(new_middle_node->get_key(1),new_middle_node);
//        int a;

        middle_node1->getParent_node()->insert(new_middle_node->get_key(1),new_middle_node);
        return  new_middle_node;
    }


    //template <typename key_type,typename value_type>   //叶节点内的sort函数
    bool
    operator<(key_value_pair &s1, key_value_pair &s2)
    {
        return s1.key < s2.key;
    }


    //template <typename key_type,typename value_type>                        //中间节点内的用于sort的友元函数
    bool
    operator<(key_value_pair_for_middle_node &s1, key_value_pair_for_middle_node &s2)
    {
        return s1.key < s2.key;
    }

    //template <typename key_type,typename value_type>                     //下一个节点是叶子节点的中间节点的用于sort的友元函数
    bool
    operator<(key_value_pair_for_middle_node_which_next_node_is_leaf_node &s1,
            key_value_pair_for_middle_node_which_next_node_is_leaf_node &s2)
    {
        return s1.key<s2.key;
    }

} // end of utils

