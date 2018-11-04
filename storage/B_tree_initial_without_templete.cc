//
// Created by yurunyang on 18-10-19.
//

#include "B_tree_initial_without_templete.h"
#include "B_tree_nodes_without_templete.h"

utils::Manager::Manager(std::string key)
    : whether_initialed(0),
    root(initial_B_tree(key))
{
    root->set_manager(this);
}

utils::Manager::Manager(const char *key)
    : Manager(std::string(key))
{
}

void
utils::Manager::update_root(middle_node *newroot)
{
    assert(newroot != nullptr);
    // 原来的root呢?
    delete root;
    root = nullptr;

    root = newroot;
    root->set_manager(this);
    maxdeepth++;
}

void
utils::Manager::updata()
{
    root->updatekey();
}

utils::middle_node *
utils::Manager::initial_B_tree(std::string key)
{
    middle_node *root = new middle_node;
    middle_node *child_1 = new middle_node(root);
    middle_node *child_2 = new middle_node(root);
    leaf_node *leaf_node1 = new leaf_node(child_1);


    //middle_node  *child_2 = new middle_node (root);
    leaf_node *leaf_node2 = new leaf_node(child_2);



    root->insert(key, child_1);
    child_1->insert(key, leaf_node1);
    //root->insert(key+100,child_2);


    root->insert("zzzzzzzzzz", child_2);
    child_2->insert(("zzzzzzzzzz"), leaf_node2);
    leaf_node1->insert(key,0);

    whether_initialed =1;
    maxdeepth =3;

    return root;
}


off64_t
utils::Manager::data_search(std::string key)
{
    assert(root != nullptr);

    middle_node *temp_node = root;
    points_struct point;

    point = temp_node->searchkey(key);
    //cout<<point->flag;
    while(1)
    {

        //#point = temp_node->searchkey(key);
        //break;
        if(point.flag == 0) {
            return -2;
        }

        if(point.flag == 1) {
            point = point.middle_node_point->searchkey(key);
        } else {
            off64_t value ;
            value = point.leaf_node_point->searchkey(key);
            // TODO: 替换全部的cout..
            std::cout << value << std::endl;
            return  value;
        }

    }
}


int
utils::Manager::insert_data(std::string key,off64_t value)
{
    assert(root != nullptr);
    middle_node *temp_root = root;
    points_struct point;
    point = temp_root->searchkey(key);

    while (1) {
        //point = temp_root->searchkey(key);
        if (point.flag == 0) {
            //没有找到相关节点
            if (temp_root->user_paires() >= 10) {
                //split_node
                std::cout << "this node has full2 ,key is " << key << std::endl;
                break;
            } else {
                middle_node *temp_middle_node = new middle_node(*temp_root);

                temp_root->insert(key, temp_middle_node);
                temp_root->updatekey();

                middle_node *tmp = temp_root;
                for (int i = 0; i < maxdeepth - 3; i++) {
                    //计数循环，保持树的平衡
                    middle_node *middle_node2 = new middle_node(temp_middle_node);

                    tmp->insert(key, middle_node2);
                    tmp->updatekey();
                    tmp = middle_node2;
                }

                leaf_node *leaf_node1 = new leaf_node(temp_middle_node);
                leaf_node1->insert(key,value);
                temp_middle_node->insert(key, leaf_node1);
                temp_middle_node->updatekey();
                return 1;
            }
        } else {
            //找到了相关节点
            while (point.flag == 1) {
                point = point.middle_node_point->searchkey(key);
            }
            //差一个计数器用来保证行插入的节点使树的层之间保持平衡
            //                        if(point->flag==0)
            //                        {
            //                            //cout<<2<<endl;
            //                        }

            if (point.flag == 2) {
                int whether_insert_succeed = 0;

                whether_insert_succeed = point.leaf_node_point->insert(key, value);
                if (whether_insert_succeed == -1)
                    //cout<<"digui"<<endl;
                    insert_data(key, value);
                else
                    return 1;

                //point->leaf_node_point->get_parent_node()->updatekey();
                //return 1;
            }
            //if(point)
        }
    }
    return 1;
}


utils::Manager::~Manager()
{
    //TODO: 完成析构函数
}


