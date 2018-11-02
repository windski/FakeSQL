//
// Created by yurunyang on 18-10-15.
//

#ifndef THE_NEW_FAKE_SQL_INTERFACEMANAGER_H
#define THE_NEW_FAKE_SQL_INTERFACEMANAGER_H

#include "B_tree_nodes_without_templete2.h"
#include "B_tree_initial_without_templete2.h"
#include "bson_.h"
#include "pub_friends.hpp"
#include "file_read_write_system.h"
using namespace std;
namespace  utils {
    class InterfaceManager {
    private:
        char * filepath;
        string initialKey;
        Manager *BTreeManager;// = new Manager<string, off64_t>("-2147483648");
        basic_read_write *BasicReadWrite ;//= new basic_read_write(".//test.db");

    public:
        InterfaceManager(char* dbfilenamepath,string initialkey);

        ~InterfaceManager();

        int insert_Into_Bson(const Quantum::HyfineStruct_t  &hy_p);

    };
}
#endif //THE_NEW_FAKE_SQL_INTERFACEMANAGER_H
