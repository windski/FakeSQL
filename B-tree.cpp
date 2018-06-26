//
// Created by yurunyang on 18-6-11.
//

#include <vector>
#include <algorithm>
#include "iostream"

using namespace std;
namespace utlis {



    template <class key_type>
    class key_value_pair_for_middle_node;

    template <class key_type,class value_type>
    class leaf_node;

    template <class key_type>
    class key_value_pair_for_middle_node_which_next_node_is_leaf_node;

    template <class key_type>
    class middle_node;






    template <class key_type>
    class key_value_pair_for_middle_node
    {
        typedef middle_node<key_type>  middle_node_t;
    public:

        key_type key;
        middle_node_t * value  ;

        //leaf_node<key_type,int>   *leaf_node1;

    public:
        key_value_pair_for_middle_node(key_type key=nullptr, middle_node_t * value= nullptr):
                key(key),value(value)
        {
//            this->key=key;
//            this->value=value;
        }




        key_type getkey(void) { return key ; }
        middle_node_t * getvalue(void) { return  value; }
        void set_key(key_type  set_key)
        {
            key = set_key;
            //return 0;
        }

        void set_value(middle_node_t * set_value )
        {
            value = set_value;
        }
    };






    template <class key_type>
    class key_value_pair_for_middle_node_which_next_node_is_leaf_node
    {
        typedef middle_node<key_type>  middle_node_t;
    public:

        key_type key;
        //middle_node_t * value  ;

        leaf_node<key_type,int>   * value;

    public:


        key_value_pair_for_middle_node_which_next_node_is_leaf_node
                (key_type key=nullptr, leaf_node<key_type,int> * value= nullptr):
                key(key),value(value)
        {

        }


        key_type getkey(void) { return key ; }
        leaf_node<key_type,int> * getvalue(void) { return  value; }
        void set_key(key_type  set_key)
        {
            key = set_key;
            //return 0;
        }

        void set_value(leaf_node<key_type,int>  * set_value )
        {
            value = set_value;
        }
    };



    template <class key_type>
    class middle_node
    {

    private:
        typedef middle_node<key_type> middle_node_t;

        //middle_node<key_type> * parent_node = new middle_node<key_type>;
        //middle_node_t * parent_node;
        int flag =-1;
        vector< key_value_pair_for_middle_node<key_type> >   key_value_pair_for_middle_node_t ;
        vector< key_value_pair_for_middle_node_which_next_node_is_leaf_node<key_type> >
                key_value_pair_for_middle_node_which_next_node_is_leaf_node_t ;

        //vector< key_value_pair_for_middle_node<key_type> > ;
    public:
        middle_node()//middle_node_t  * _parent_node = nullptr)
        //: parent_node(_parent_node)
        {

        }
        void insert(key_type key , middle_node_t * value)
        {
            if(flag==1)
                return; //子节点不可同时存在既有叶子节点又有中间节点的情况
            key_value_pair_for_middle_node_t.push_back( key_value_pair_for_middle_node <key_type>(key,value));
            flag = 0;
            sort();
        }

        void insert(key_type key , leaf_node<key_type,int> * value)
        {
            if(flag==0)
                return; //子节点不可同时存在既有叶子节点又有中间节点的情况
            key_value_pair_for_middle_node_which_next_node_is_leaf_node_t.push_back
                    ( key_value_pair_for_middle_node_which_next_node_is_leaf_node<key_type>(key,value));
            flag =1;
            sort();
        }



        void sort()
        {
            if(flag ==0)
                std::sort(key_value_pair_for_middle_node_t.begin()
                        ,key_value_pair_for_middle_node_t.end());
            if(flag ==1)
                std::sort(key_value_pair_for_middle_node_which_next_node_is_leaf_node_t.begin(),
                          key_value_pair_for_middle_node_which_next_node_is_leaf_node_t.end());


        }

        friend bool operator< ( key_value_pair_for_middle_node<key_type> &s1, key_value_pair_for_middle_node<key_type> &s2);

                             //下一个节点是叶子节点的中间节点的用于sort的友元函数
        friend bool operator< (key_value_pair_for_middle_node_which_next_node_is_leaf_node<key_type> &s1,
                        key_value_pair_for_middle_node_which_next_node_is_leaf_node<key_type> &s2);




    };




    /////////////////////////////////////////////////////
    /////////////////////////////////////////////////////
    //下面是叶子节点类



    template <class key_type,class value_type>
    class key_value_pair
    {
    private:

        key_type key;
        value_type value;
    public:
        key_value_pair(key_type key=NULL,value_type value=NULL)
        {
            this->key=key;
            this->value=value;
        }
        key_type getkey(void) { return key ; }
        value_type getvalue(void) { return  value; }
        void set_key(key_type  set_key)
        {   key = set_key;
            //return 0;
        }

        void set_value(value_type set_value )
        {
            value = set_value;
        }
    };




    template <class key_type,class value_type>
    class leaf_node
    {
    public:
        middle_node<key_type> * parent_node ;//= new middle_node<key_type>;  //父亲节点
        leaf_node<key_type,value_type> * brother_node ;//= new leaf_node<key_type,value_type>;
        //vector<int> v = vector<int>(10, 0);
        vector< key_value_pair<key_type,value_type> >  key_value_pairs  = vector< key_value_pair<key_type,value_type> >(1);
        int used_pairs;
    public:
        leaf_node(middle_node<key_type> * parent_node= nullptr,
                  leaf_node<key_type,value_type> * brother_node = nullptr)//:parent_node(parent_node),brother_node(brother_node)
        {
            used_pairs=0;
            this->parent_node = parent_node;
            this->brother_node = brother_node;

        };

        int  insert(key_type key ,value_type value)
        {
            if(used_pairs==10)
            {
                return 0;  //该叶子节点已满,插入失败
            } else
            {
                key_value_pair<key_type,value_type> new_pair(key,value);  //初始化一个新的key_value_pair
                key_value_pairs.push_back(new_pair);   //加入到key_value_pairs 的vector 中
                used_pairs++;                       //当前已使用的pair加1
                return  1 ;  //insert successed
            }
        };



        int delete_pair(key_type key)
        {
            typename vector< key_value_pair<key_type,value_type> >::iterator iter= key_value_pairs.begin();
            while(iter!=key_value_pairs.end())
            {
                if(iter->getkey()==key)
                {
                    iter->set_key(-1);
                    iter->set_value(-1);
                    key_value_pairs.erase(iter);
                    used_pairs--;
                    cout<<"delete";
                    break;
                } else iter++;
            }
        }

        key_type get_key()
        {
            return 0;
        }


        void _sort()
        {
            sort(key_value_pairs.begin(),key_value_pairs.end());
        }




        friend bool operator< (key_value_pair<key_type,value_type> &s1 ,  key_value_pair<key_type,value_type> &s2);





    };


    template <typename key_type,typename value_type>   //叶节点内的sort函数
    bool operator< (key_value_pair<key_type,value_type> &s1 ,  key_value_pair<key_type,value_type> &s2)
    {
        return s1.key<s2.key;
    }


    template <typename key_type>                        //中间节点内的用于sort的友元函数
    bool operator< ( key_value_pair_for_middle_node<key_type> &s1, key_value_pair_for_middle_node<key_type> &s2)
    {
        return s1.key<s2.key;
    }

    template <typename  key_type>                       //下一个节点是叶子节点的中间节点的用于sort的友元函数
    bool operator< (key_value_pair_for_middle_node_which_next_node_is_leaf_node<key_type> &s1,
                    key_value_pair_for_middle_node_which_next_node_is_leaf_node<key_type> &s2)
    {
        return s1.key<s2.key;
    }





    template <class key_type>
    class root
    {
        root()
        {

        }
    };


}
