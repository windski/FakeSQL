//
// Created by windsky_1 on 2018/8/2.
//

// 把你所有的友元函数定义全部放到这个底下吧..
// 这个头文件就是放一些声明的..
// public friends 23333

#ifndef PUB_FRIENDS_HPP_
#define PUB_FRIENDS_HPP_

namespace utils {

    //template<class key_type, class value_type>
    class Manager;

    //template <class key_type,class value_type>
    class key_value_pair_for_middle_node;

    //template <class key_type,class value_type>
    class leaf_node;

    //template <class key_type,class value_type>
    class key_value_pair_for_middle_node_which_next_node_is_leaf_node;

    //template <class key_type,class value_type>
    class middle_node;


    //template <class key_type,class value_type>
    class key_value_pair;

    //template <class key_type,class value_type>
    struct points_struct
    {
        int flag = 0;
        middle_node * middle_node_point;
        leaf_node * leaf_node_point;
    };

    //template <class key_type, class value_type>
    void _split_leaf_node(middle_node * parent_node,leaf_node * leaf_node1);

    //template <class key_type, class value_type>
    middle_node * _split_middle_node(middle_node * middle_node1,leaf_node * leaf_node1);
    middle_node *  _split_middle_node(middle_node * middle_node1);

}


#endif // PUB_FRIENDS_HPP_
