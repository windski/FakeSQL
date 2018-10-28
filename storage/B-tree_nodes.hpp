////
//// Created by yurunyang on 18-6-11.
////
//
//#ifndef B_TREE_NODES_HPP
//#define B_TREE_NODES_HPP
//
// #include <algorithm>
//#include "iostream"
//#include "string"
//#include "B-tree-initial.hpp"
//#include "B-tree-initial.hpp"
//#include "pub_friends.hpp"          // emmmm...名字有点gay gay的味道...
//
//
//
//using namespace std;
//namespace utils {
//
//
//
//    template <class key_type,class value_type>
//    class key_value_pair_for_middle_node
//    {
//        typedef middle_node<key_type,value_type>  middle_node_t;
//    public:
//
//        key_type key;
//        middle_node_t * value;
//
//
//    public:
//        key_value_pair_for_middle_node(key_type key=NULL, middle_node_t * value = NULL):
//                key(key),value(value)
//        {
////            this->key=key;
////            this->value=value;
//        }
//
//
//        key_type getkey(void) { return key ; }
//        middle_node_t * getvalue(void) { return  value; }
//        void set_key(key_type  set_key)
//        {
//            key = set_key;
//            //return 0;
//        }
//
//        void set_value(middle_node_t * set_value )
//        {
//            value = set_value;
//        }
//
//
//        value_type update_key()
//        {
//            value_type maxvalue ;
//            maxvalue =  value->updatekey();
//            //cout<<key<<endl;
//        }
//
//    };
//
//
//
//
//
//
//    template <class key_type,class value_type>
//    class key_value_pair_for_middle_node_which_next_node_is_leaf_node
//    {
//        typedef middle_node<key_type,value_type>  middle_node_t;
//    public:
//
//        key_type key;
//        //middle_node_t * value  ;
//
//        leaf_node<key_type,value_type>   * value;
//
//    public:
//
//
//        key_value_pair_for_middle_node_which_next_node_is_leaf_node
//                (key_type key = NULL, leaf_node<key_type,value_type> * value = NULL):
//                key(key),value(value)
//        {
//            //update_key();
//            //cout<<"updatekey successful"<<endl;
//        }
//
//
//        key_type getkey(void) { return key ; }
//        leaf_node<key_type,value_type > * getvalue(void) { return  value; }
//        void set_key(key_type  set_key)
//        {
//            key = set_key;
//            //return 0;
//        }
//
//        void set_value(leaf_node<key_type,int>  * set_value )
//        {
//            value = set_value;
//        }
//
//        void update_key()
//        {
//            key = value->get_key();
//            //cout<<key<<endl;
//        }
//
//
//
//    };
//
//
//
//    template <class key_type,class value_type>
//    class  middle_node
//    {
//
//    private:
//        typedef middle_node<key_type,value_type> middle_node_t;
//
//        //middle_node<key_type> * parent_node = new middle_node<key_type>;
//        middle_node_t * parent_node;
//        utils::Manager<key_type,value_type> * manager = nullptr;
//        int flag =-1;
//        int used_pairs =0;
//        key_type Maxkey;
//        deque< key_value_pair_for_middle_node<key_type,value_type> >   key_value_pair_for_middle_node_t ;
//        deque< key_value_pair_for_middle_node_which_next_node_is_leaf_node<key_type,value_type> >
//                key_value_pair_for_middle_node_which_next_node_is_leaf_node_t ;
//
//        //deque< key_value_pair_for_middle_node<key_type> > ;
//    public:
//        middle_node(middle_node_t  * _parent_node = nullptr)
//        : parent_node(_parent_node)
//        {
//        }
//
//        void set_manager(Manager<key_type,value_type> *manager)
//        {
//            this->manager = manager;
//        }
//
//        void set_parent_node(middle_node<key_type,value_type> * parent_node)
//        {
//            this->parent_node = parent_node;
//        }
//
//
//        key_type updatekey() {
//            if (flag == 1) {
//
//                typename deque<key_value_pair_for_middle_node_which_next_node_is_leaf_node<key_type, value_type> >::iterator item1 =
//                        key_value_pair_for_middle_node_which_next_node_is_leaf_node_t.begin();
//
//                while (item1 != key_value_pair_for_middle_node_which_next_node_is_leaf_node_t.end() - 1) {
//                    item1->update_key();
//                    item1++;
//                }
//
//                sort();
//
//                int stl_size = key_value_pair_for_middle_node_which_next_node_is_leaf_node_t.size();
//
//                if (stl_size > 0) {
//                    typename deque<key_value_pair_for_middle_node_which_next_node_is_leaf_node<key_type, value_type> >::iterator item =
//                            key_value_pair_for_middle_node_which_next_node_is_leaf_node_t.end() - 1;
//
//                    //cout << item->key << "Maxkey" << endl;
//
//                    this->Maxkey = item->key;
//                    return Maxkey;
//
//                } else
//                {
//                    this->Maxkey= to_string(-2147483648);
//                    return to_string(-2147483648);
//                }
//
//            } else {
//
//
//                typename deque<key_value_pair_for_middle_node<key_type, value_type>>::iterator item1 = key_value_pair_for_middle_node_t.begin();
//
//                while (item1 != key_value_pair_for_middle_node_t.end()) {
//                    Maxkey = item1->update_key();
//                    item1++;
//                }
//
//
//                int stl_size = key_value_pair_for_middle_node_t.size();
//
//                //cout<< stl_size <<"   stl_size "<<endl;
//
//                if (stl_size > 0) {
//                    typename deque<key_value_pair_for_middle_node<key_type, value_type> >::iterator item =
//                            key_value_pair_for_middle_node_t.end() - 1;
//                    //cout << item->key << "Maxkey" << endl;
//                    this->Maxkey = item->key;
//
//                    //cout<< item->key<<"Maxkey"<<endl;
//
//                    return Maxkey;
//
//                } else
//                {
//                    //cout <<"else"<<endl;
//                    return to_string(-2147483648);
//                }
//
//            }
//        }
//
//        key_type get_key(int front_or_back=0)    //这个参数表示要取的是front还是back
//        {
//            if(flag==1)
//            {
//                if(front_or_back==0)
//                {
//                    typename deque<key_value_pair_for_middle_node_which_next_node_is_leaf_node<key_type, value_type> >::iterator item =
//                            key_value_pair_for_middle_node_which_next_node_is_leaf_node_t.begin();
//                    return item->getkey();
//                }
//                if(front_or_back==1)
//                {
//                    typename deque<key_value_pair_for_middle_node_which_next_node_is_leaf_node<key_type, value_type> >::iterator item =
//                            key_value_pair_for_middle_node_which_next_node_is_leaf_node_t.end()-1;
//                    return item->getkey();
//                }
//
//            }
//            if(flag==0)
//            {
//                if(front_or_back==0)
//                {
//                    typename deque< key_value_pair_for_middle_node<key_type,value_type> > ::iterator item =key_value_pair_for_middle_node_t.begin();
//                    return item->getkey();
//                }
//                if(front_or_back==1)
//                {
//                    typename deque< key_value_pair_for_middle_node<key_type,value_type> > ::iterator item =key_value_pair_for_middle_node_t.end()-1;
//                    return item->getkey();
//                }
//
//            }
//        }
//
//
//        middle_node_t * get_value_of_middle_node()
//        {
//            typename deque< key_value_pair_for_middle_node<key_type,value_type> > ::iterator item =key_value_pair_for_middle_node_t.begin();
//            return item->getvalue();
//        }
//
//
//        leaf_node<key_type,value_type> * get_value_of_leaf_node()
//        {
//            typename  deque<key_value_pair_for_middle_node_which_next_node_is_leaf_node<key_type,value_type>>::iterator iter
//                    = key_value_pair_for_middle_node_which_next_node_is_leaf_node_t.begin();
//
//            return iter->getvalue();
//        };
//
//
//        void delete_pair()
//        {
//            if (flag==0)
//            {
//                key_value_pair_for_middle_node_t.pop_front();
//                used_pairs--;
//            } else{
//                key_value_pair_for_middle_node_which_next_node_is_leaf_node_t.pop_front();
//                used_pairs--;
//            }
//
//        }
//
//
//
//        int user_paires()
//        {
//            return  used_pairs;
//        }
//
//         points_struct<key_type,value_type> *  searchkey(key_type key)
//        {
//            points_struct<key_type,value_type> * points_struct_t = new points_struct<key_type,value_type>;
//
//            if(flag ==0)
//            {
//
//                typename deque< key_value_pair_for_middle_node<key_type,value_type> > ::iterator item
//                        =key_value_pair_for_middle_node_t.begin();
//
//                while(item != key_value_pair_for_middle_node_t.end())
//                {
//                    if(item->getkey() >= key)
//                    {
//                        //cout<<item->getkey()<<endl;                                                      //
//                        points_struct_t->flag =1;      //找到的是中间节点                                //
//                        points_struct_t->leaf_node_point= nullptr;                                      //
//                        points_struct_t->middle_node_point=item->getvalue();                             //
//                        return points_struct_t;
//                    }
//                    item++;
//                }
//                //cout<<1<<endl;
//                points_struct_t->flag=0;  //没有找到相关节点
//                points_struct_t->middle_node_point= nullptr;
//                points_struct_t->middle_node_point= nullptr;
//                return points_struct_t;
//            } else
//            {
//
//                typename deque<key_value_pair_for_middle_node_which_next_node_is_leaf_node<key_type,value_type> >::iterator item
//                        = key_value_pair_for_middle_node_which_next_node_is_leaf_node_t.begin();
//
//                while(item != key_value_pair_for_middle_node_which_next_node_is_leaf_node_t.end())
//                {
//                    if(item->getkey() >= key)
//                    {
//                        points_struct_t->flag=2; //找到的是叶子节点
//                        points_struct_t->leaf_node_point=item->getvalue();
//                        points_struct_t->middle_node_point = nullptr;
//                        return points_struct_t;
//                    }
//                    item++;
//
//                }
//                points_struct_t->flag=0;
//                points_struct_t->middle_node_point= nullptr;
//                points_struct_t->middle_node_point= nullptr;
//                return points_struct_t;
//            }
//
//
//        }
//
//
//        middle_node_t  *  getParent_node()
//        {
//            if(this->parent_node==NULL)
//            {
//                middle_node<key_type,value_type> * new_root = new middle_node<key_type,value_type>;
//                this->updatekey();
//                new_root->insert(this->get_key(1),this);
//                this->set_parent_node(new_root);
//                (this->manager)->update_root(new_root);
//                cout<<"parent_node has set"<<endl;
//
//
//            }
//            return parent_node;
//        }
//
//        //这里也要看
//        int insert(key_type key , middle_node<key_type,value_type> * value)
//        {
//            if(flag==1 )
//                return 1; //子节点不可同时存在既有叶子节点又有中间节点的情况
//            if(used_pairs>=10)
//            {
//                middle_node<key_type,value_type> * new_middle_node = new middle_node<key_type,value_type>;
//                new_middle_node =  _split_middle_node(this);//,value);
//
//                int new_middle_node_maxkey = new_middle_node->get_key(1);
//                //cout<<size<<":size"<<endl;
//                int leaf_node1_maxkey = value->get_key(1);
//                if(new_middle_node_maxkey>= leaf_node1_maxkey)
//                {
//                    new_middle_node->insert(value->get_key(1),value);
//                    value->set_parent_node(new_middle_node);
//                } else
//                {
//                    this->insert(value->get_key(1),value);
//                    value->set_parent_node(this);
//                }
//
//                return 0;
//            }
//            key_value_pair_for_middle_node_t.push_back( key_value_pair_for_middle_node <key_type,value_type>(key,value));
//            value->set_parent_node(this);
//            flag = 0;
//            //this->key=key;
//            this->used_pairs+=1;
//            this->updatekey();
//            sort();
//            return 0;
//        }
//
//
//
//        int insert(key_type key , leaf_node<key_type,value_type> * value)
//        {
//
//            if(flag==0)
//                return 1; //子节点不可同时存在既有叶子节点又有中间节点的情况
//
//            middle_node<key_type,value_type> *new_middle_node = new middle_node<key_type,value_type>;
//            if(used_pairs>=10)
//            {
//                //cout<<"middle node has full,the key is "<<key<<endl;
//
//                 new_middle_node =  _split_middle_node(this,value);
//                //sort();
//
//                int new_middle_node_maxkey = new_middle_node->get_key(1);
//                //cout<<size<<":size"<<endl;
//                int leaf_node1_maxkey = value->get_key();
//                if(new_middle_node_maxkey>= leaf_node1_maxkey)
//                {
//                    new_middle_node->insert(value->get_key(),value);
//                    value->set_parent(new_middle_node);
//                } else
//                {
//                    this->insert(value->get_key(),value);
//                    value->set_parent(this);
//                }
//
//
//                return 0;
//            }
//            ////////////////
//            ///////////////下面的可能要剪掉
//            value->set_parent(this);
//            key_value_pair_for_middle_node_which_next_node_is_leaf_node_t.push_back
//                    ( key_value_pair_for_middle_node_which_next_node_is_leaf_node<key_type,value_type>(key,value));
//            flag =1;
//            //this->key= key;
//            this->used_pairs+=1;
//            sort();
//            this->updatekey();
//            return 1;
//        }
//
//
//
//        void sort()
//        {
//            if(flag ==0)
//                std::sort(key_value_pair_for_middle_node_t.begin()
//                        ,key_value_pair_for_middle_node_t.end());
//            if(flag ==1)
//                std::sort(key_value_pair_for_middle_node_which_next_node_is_leaf_node_t.begin(),
//                          key_value_pair_for_middle_node_which_next_node_is_leaf_node_t.end());
//
//
//        }
//
//        template<key_type, value_type>
//        friend bool operator< ( key_value_pair_for_middle_node<key_type,value_type> &s1, key_value_pair_for_middle_node<key_type,value_type> &s2);
//
//                             //下一个节点是叶子节点的中间节点的用于sort的友元函数
//        template<key_type, value_type>
//        friend bool operator< (key_value_pair_for_middle_node_which_next_node_is_leaf_node<key_type,value_type> &s1,
//                        key_value_pair_for_middle_node_which_next_node_is_leaf_node<key_type,value_type> &s2);
//
//
//
//
//    };
//
//
//
//
//    /////////////////////////////////////////////////////
//    /////////////////////////////////////////////////////
//    //下面是叶子节点类
//
//
//
//
//    template <class key_type,class value_type>
//    class key_value_pair
//    {
//
//    public:
//
//        key_type key;
//        value_type value;
//    public:
//        key_value_pair(key_type key,value_type value)
//        {
//            this->key=key;
//            this->value=value;
//        }
//        key_type getkey(void) { return key ; }
//        value_type getvalue(void) { return  value; }
//        void set_key(key_type  set_key)
//        {
//            key = set_key;
//        }
//
//        void set_value(value_type set_value )
//        {
//            value = set_value;
//        }
//    };
//
//
//
//
//    template <class key_type,class value_type>
//    class leaf_node
//    {
//    private:
//        key_type Max_key;
//        //friend void _split(middle_node<key_type,value_type> * parent_node,leaf_node<key_type,value_type> * leaf_node1=nullptr);
//        middle_node<key_type,value_type> * parent_node ;//= new middle_node<key_type>;  //父亲节点
//        leaf_node<key_type,value_type>  * brother_node ;//= new leaf_node<key_type,value_type>;
//        //deque<int> v = deque<int>(10, 0);
//        //deque< key_value_pair<key_type,value_type> >  key_value_pairs  = deque< key_value_pair<key_type,value_type> >(1);
//        deque<key_value_pair<key_type,value_type>> key_value_pairs;
//        int used_pairs;
//
//
//    public:
//        leaf_node(middle_node<key_type,value_type> * parent_node= nullptr,
//                  leaf_node<key_type,value_type> * brother_node = nullptr):parent_node(parent_node),brother_node(brother_node)
//        {
//            used_pairs=0;
//            Max_key =0;
//            this->parent_node = parent_node;
//            this->brother_node = brother_node;
//        };
//
//        key_type pop_key(int flag=0)
//        {
//            if(flag==0) {
//                typename deque<key_value_pair<key_type, value_type>>::iterator item = key_value_pairs.begin();
//                return item->getkey();
//            } else{
//                typename  deque<key_value_pair<key_type,value_type>>:: iterator item = key_value_pairs.end()-1;
//                return item->getkey();
//            }
//        }
//
//        value_type pop_value()
//        {
//            typename deque<key_value_pair<key_type,value_type>>::iterator item = key_value_pairs.begin();
//            return item->getvalue();
//        }
//
////        key_type updateMaxkey()
////        {
////            return Max_key;
////        }
//
//
//        int  insert(key_type key ,value_type value)
//        {
//            if(used_pairs>=10)
//            {
//
//               // cout<<"this node has full,the key is "<<key<<endl;
//
//                //leaf_node<key_type,value_type> *leaf_node1 = new leaf_node<key_type,value_type>(parent_node);
//
//                _split_leaf_node(parent_node,this);               //??????????
//                parent_node->updatekey();
//                _sort();
//                Max_key = (key_value_pairs.end()-1)->key;
//                return  -1 ;  //insert successed
//
//
//
//                //return 0;  //该叶子节点已满,插入失败
//            } else
//            {
//                //cout<<key<<endl;
//                key_value_pair<key_type,value_type> new_pair(key,value);  //初始化一个新的key_value_pair
//                key_value_pairs.push_back(new_pair);   //加入到key_value_pairs 的deque 中
//                used_pairs++;                       //当前已使用的pair加1
//                _sort();
//                Max_key = (key_value_pairs.end()-1)->key;
//                return  1 ;  //insert successed
//            }
//        };
//
//        void set_parent(middle_node<key_type,value_type> * parent_node)
//        {
//            this->parent_node = parent_node;
//        }
//
//
//        middle_node<key_type,value_type> * get_parent_node()
//        {
//            return  parent_node;
//        };
//
//
//        int delete_pair(key_type key = 0)
//        {
//            if(key == 0)
//            {
//                key_value_pairs.pop_front();
//                used_pairs--;
//                return 1;
//            }
//            typename deque< key_value_pair<key_type,value_type> >::iterator iter= key_value_pairs.begin();
//            while(iter!=key_value_pairs.end())
//            {
//                if(iter->getkey()==key)
//                {
//                    iter->set_key(-1);
//                    iter->set_value(-1);
//                    key_value_pairs.erase(iter);
//                    used_pairs--;
//                    //cout<<"delete";
//                    break;
//                } else iter++;
//            }
//        }
//
//        key_type get_key()
//        {
//            return  (key_value_pairs.end()-1)->getkey();
//        }
//
//
//        void _sort()
//        {
//            sort(key_value_pairs.begin(),key_value_pairs.end());
//        }
//
//
//        value_type searchkey(key_type key)
//        {
//            typename deque<key_value_pair<key_type,value_type>>::iterator item =  key_value_pairs.begin();
//            while(item!=key_value_pairs.end())
//            {
//                if(item->getkey() == key)
//                {
//                    //cout<<item->getkey();
//                    return item->getvalue();
//                }
//                item++;
//            }
//            return 0;
//        }
//
//
//        //friend void _split(middle_node<key_type,value_type> * parent_node,leaf_node<key_type,value_type> * leaf_node1=nullptr);
//        template<key_type, value_type>
//        friend bool operator< (key_value_pair<key_type,value_type> &s1 ,  key_value_pair<key_type,value_type> &s2);
//
//
//
//    };
//
//    ////////////////////////////////////////////////////////////////////////////////////////////////////////////
//    //////////////////////////////////////下面是公用的友元函数//////////////////////////////////////////////////
//    ////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//    template <class key_type,class value_type>
//    void  _split_leaf_node(middle_node<key_type,value_type> * parent_node,leaf_node<key_type,value_type> * leaf_node1)
//    {
//
//            leaf_node<key_type,value_type> * new_leaf_node = new leaf_node<key_type,value_type>();
//            //parent_node->insert()
//            //new_leaf_node->insert(key,value);
//            for(int i=0;i<5;i++)
//            {
//
//
//
//                new_leaf_node->insert(leaf_node1->pop_key(),leaf_node1->pop_value());
//                //cout<<"delete:"<<leaf_node1->pop_key()<<endl;
//                leaf_node1->delete_pair();
//            }
//
//            parent_node->insert(new_leaf_node->pop_key(1),new_leaf_node);
//
//
//    }
//
//
//    template<class key_type,class value_type>
//    middle_node<key_type,value_type> * _split_middle_node(middle_node<key_type,value_type> * middle_node1,leaf_node<key_type,value_type> * leaf_node1)
//    {
//
//
//        middle_node<key_type,value_type> * new_middle_node = new middle_node<key_type,value_type>();
//        for (int i=0;i<5;i++)
//        {
//            new_middle_node->insert(middle_node1->get_key(),middle_node1->get_value_of_leaf_node());
//            middle_node1->delete_pair();
//        }
//
//        //看这里
//        ////////////
////        int size = new_middle_node->get_key(1);
////        cout<<size<<":size"<<endl;
////        int leaf_node1_size = leaf_node1->get_key();
////        if(size>=leaf_node1->get_key())
////        {
////            new_middle_node->insert(leaf_node1_size,leaf_node1);
////        } else
////        {
////            middle_node1->insert(leaf_node1_size,leaf_node1);
////        }
//
//            /////////////
//
//
//
//        (middle_node1->getParent_node())->insert(new_middle_node->get_key(1),new_middle_node);
//        return new_middle_node;
//    }
//
//
//    template  <class key_type,class value_type>
//    middle_node<key_type,value_type> *  _split_middle_node(middle_node<key_type,value_type> * middle_node1) // ,middle_node<key_type,value_type> * middle_node_need_to_be_inserted)
//    {
//
//        middle_node<key_type,value_type> * new_middle_node = new middle_node<key_type,value_type>;
//        for(int i=0;i<5;i++)
//        {
//            new_middle_node->insert(middle_node1->get_key(),middle_node1->get_value_of_middle_node());
//            middle_node1->delete_pair();
//        }
//
////        middle_node<key_type,value_type> *parentttt =  middle_node1->getParent_node();
////        parentttt->insert(new_middle_node->get_key(1),new_middle_node);
////        int a;
//
//          middle_node1->getParent_node()->insert(new_middle_node->get_key(1),new_middle_node);
//        return  new_middle_node;
//    }
//
//
//    template <typename key_type,typename value_type>   //叶节点内的sort函数
//    bool operator< (key_value_pair<key_type,value_type> &s1 ,  key_value_pair<key_type,value_type> &s2)
//    {
//        return s1.key<s2.key;
//    }
//
//
//    template <typename key_type,typename value_type>                        //中间节点内的用于sort的友元函数
//    bool operator< ( key_value_pair_for_middle_node<key_type,value_type> &s1, key_value_pair_for_middle_node<key_type,value_type> &s2)
//    {
//        return s1.key<s2.key;
//    }
//
//    template <typename key_type,typename value_type>                     //下一个节点是叶子节点的中间节点的用于sort的友元函数
//    bool operator< (key_value_pair_for_middle_node_which_next_node_is_leaf_node<key_type,value_type> &s1,
//                    key_value_pair_for_middle_node_which_next_node_is_leaf_node<key_type,value_type> &s2)
//    {
//        return s1.key<s2.key;
//    }
//
//
//}   // end of namespace utils
//
//
//
//
//#endif