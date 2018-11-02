//
// Created by falleuion on 10/1/18.
//


#ifndef HYPERFINE_STRUCTURE_HPP
#define HYPERFINE_STRUCTURE_HPP

#include "commons.h"
#include <vector>
#include <string>

namespace Quantum {

// 这里是数据库sql应该拥有的变量类型.
// 用枚举变量便于你后面使用 `switch-case'
enum _DeclType {
    DE_INT, DE_SMALLINT, DE_INTEGER, DE_TINYINT, DE_CHAR, DE_VARCHAR, DE_DATE, DE_DECIMAL, DE_NUMERIC
};

struct _ColType {
    enum _DeclType type_;
    int size_;
};

struct _ColAttr {
    // 这个列是否是主键
    bool isPrimary_;

    // 这个能不能为空
    bool isAbleNull_;

    // 自动增加
    bool isAutoInc_;

    // 不知道什么用的index
    bool isIndex_;
};


struct TableName {
    std::string nameRef_;

    // something else....maybe...
};

struct ColumnsName {
    // 第一个自然就是列名
    std::string colRef_;

    // 下面的这俩变量主要还是针对于create table...
    // 对于其他语句的时候可能没什么用... 这里可能直接全部置 `0'.
    struct _ColType colType_;

    struct _ColAttr colAttr_;

    // the value....
    std::string colVal_;
};

struct SqlOptions {
    char test_;
};

struct _HyperfineStructure
{
    /**操作符类型...suck as `SELECT', `CREATE', `INSERT'.
     * 但他们不是简单的直接这样使用,它们在枚举里面的名字是有TS前缀的...比如`TS_SELECT'. `TS_CREATE'
     * `TS' 前缀意思是 test, 没啥特别含义...后面可能会改掉..
     */
    enum OprtType opType_;

    // 表名, 数据库名字直接给你应该就好了.这个没有什么特别的讲究,
    std::vector<struct TableName> tableListRef_;

    // 下面的这个应该是columns...
    std::vector<struct ColumnsName> colListRef_;

    // 其他的sql选项, 先列出来, 不知道有没有用.后面看看再修改...
    struct SqlOptions sqlOption_;
};

typedef struct _HyperfineStructure HyfineStruct_t;

} // end of Quantum


#endif //HYPERFINE_STRUCTURE_HPP
