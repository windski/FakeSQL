//
// Created by yurunyang on 18-10-15.
//

#include "interfaceManager.h"
#include "pub_friends.hpp"
utils::InterfaceManager::~InterfaceManager() {
    delete BTreeManager;
    delete BasicReadWrite;

}

utils::InterfaceManager::InterfaceManager(char *dbfilenamepath, string initialkey)
        :filepath(dbfilenamepath),initialKey(initialkey) {
        BTreeManager = new Manager("zzzzz");
        BasicReadWrite = new basic_read_write(filepath);

}

int utils::InterfaceManager::insert_Into_Bson(const Quantum::HyfineStruct_t &hy_p) {

    bson_::bson_couple * bsonCouple = new bson_::bson_couple;
    vector<Quantum::ColumnsName>::size_type  attrNums = (hy_p.colListRef_).size();

    enum _DeclType {
        DE_INT=0, DE_SMALLINT, DE_INTEGER, DE_TINYINT, DE_CHAR, DE_VARCHAR, DE_DATE, DE_DECIMAL, DE_NUMERIC
    }dataType_;

    enum OprtType
    {
        TS_CREATE=0, TS_INSERT, TS_SELECT, TS_DELETE
    }oprtType_;


    int k;
    //opy = (enum _DeclType)k;

    oprtType_ = (enum OprtType)k;
    switch (oprtType_)
    {

        case TS_INSERT:{
            string primaryKey;

            for(int i =0;i<attrNums;i++)
            {
                dataType_ = (enum _DeclType)hy_p.colListRef_[i].colType_.type_;

                switch (dataType_)
                {
                    case DE_CHAR: {
                        if(hy_p.colListRef_[i].colAttr_.isPrimary_)
                            primaryKey = hy_p.colListRef_[i].colVal_;
                        bsonCouple->insert_UTF8_value(hy_p.colListRef_[i].colRef_,
                                                      hy_p.colListRef_[i].colVal_);
                        break;
                    }
                    case DE_INT: {

                        if(hy_p.colListRef_[i].colAttr_.isPrimary_)
                            primaryKey = hy_p.colListRef_[i].colVal_;
                        bsonCouple->insert_int32_value(hy_p.colListRef_[i].colRef_,
                                                       hy_p.colListRef_[i].colValINT_);
                    };
                }
            }

            uint8_t *bsonBuf_ = bsonCouple->getBsonBuf();
            off64_t keyIntoTree =  this->BasicReadWrite->write_bsonCouple(bsonBuf_);
            BTreeManager->initial_B_tree("");
            BTreeManager->insert_data(primaryKey,keyIntoTree);
        }

        case TS_CREATE:{

        }

        case TS_SELECT:{

        }

        case TS_DELETE:{

        }


    }














    return 0;
}

