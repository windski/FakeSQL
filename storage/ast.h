//
// Created by falleuion on 8/17/18.
//

#ifndef AST_H_
#define AST_H_

#ifdef __cplusplus
extern "C" {
#endif
#include "commons.h"

#include <strings.h>

//enum atom_types
//{
//    AT_NUMBER, AT_STRING, AT_IDENTIFIER, AT_CONDITION
//};
//
//struct _ast_node_opts;
//struct _ast_node_sexp;
//
//typedef struct _ast_node_sexp ast_node_sexp;
//
//typedef struct _ast_node_opts ast_node_opts;

// structure `ast_node_atom'
// This should be the node corresponding to the terminator.Its type can be the `number',
// `string'. `table reference' etc.
//typedef struct
//{
//    enum atom_types type;
//    union
//    {
//        long number;
//        char *string;
//        int subtok;
//    } value;
//
//} ast_node_atom;
//
//// This function will generate a new item of the teminator
//// Return: the structure of `ast_node_atom' on success.
//ast_node_atom *
//new_atom_node(enum atom_types type, void *v);
//
//void
//delete_atom_node(ast_node_atom *node);
//
//void
//print_node_atom(ast_node_atom *node);
//
// This function will add the parameter @v to the @node
//void
//add_atom_to_sexp(ast_node_sexp *_node, ast_node_atom *_atom);
//
//enum sexp_types
//{
//    ST_ATOM, ST_LIST, ST_NONE
//};
//
//struct _ast_node_sexp
//{
//    enum sexp_types type;
//    union
//    {
//        ast_node_atom *atom;
//    } value;
//    struct _ast_node_sexp *next;
//};
//
//void
//print_node_sexp(ast_node_sexp *node);
//
//ast_node_sexp *
//new_sexp_node(enum sexp_types type, void *v);
//
//void
//delete_sexp_node(ast_node_sexp *node);
//
//enum opts_types
//{
//    OP_WHERE, OP_SELECT, OP_GROUPBY, OP_HAVING, OP_ORDERBY, OP_LIMIT, OP_INTO_LIST
//};
//
//struct _ast_node_opts
//{
//    enum opts_types type;
//    union
//    {
//        ast_node_atom *atom;
//    } value;
//};
//
//ast_node_opts * new_opts_node(enum opts_types type, void *v);
//void delete_opts_node(ast_node_opts *node);

// ---------- this following structure will be used as operator such as `SELECT', `CREATE', `INSERT' etc. -------


enum DataType
{
    DT_BIT, DT_TINYINT, DT_SMALLINT, DT_MEDINT, DT_INT, DT_INTEGER, DT_BIGINT, DT_REAL, DT_DOUBLE, DT_FLOAT,
    DT_DECIMAL, DT_DATE, DT_TIME, DT_TIMESTAMP, DT_DATETIME, DT_YEAR, DT_CHAR, DT_VARCHAR, DT_BINARY,
    DT_TINYBLOB, DT_BLOB, DT_MEDBLOB, DT_VARBIN, DT_LONGBLOB,   DT_TEXT, DT_TINYTEXT, DT_MEDTEXT, DT_LONGTEXT
};


struct _TablList;
struct _NameList;
struct _kv_pair;
struct _SqlOpts;
struct _DefOpts;
struct _ExprVarCon;
struct _DelSetceOpts;
struct _Express;

struct _OprtNode
{
    // This member is used to mark the SQL command.
    enum OprtType type_;
    
    /** The structure contains 'sql table' that users reference. It should be a list type.
     * In case users are specified in `name.name'
     */
    struct _TablList *table_;

    // universalList_ 是一个非常诡异的`List', 因为它已经被我改的面目全非了...
    // Sql 语句实在太复杂了...感觉自己很难找到一种特别规整的树来把它的逻辑结构很有层次的表示出来...
    struct
    {
        // 它只用于create table语句...在其他语句里面很难复用
        struct _DefOpts *defOpts_;

        // 它应该是column 的reference...名字起的有问题...
        struct _NameList *tableNameList_;

        // This is a container. It storage the `ExprVar' in the default...
        struct _ExprVarCon *exprVarCon_;
    } universalList_;
    
    struct _SqlOpts *options_;
};

/**
 * The whole logical relation of the `oprt_node' struct should probably be the following.
 * Each of the three children of the `operator' will be a structure, and the `options' node
 * may NOT exist.
 *                    ,------.
 *                    | root |
 *                    `------'
 *                       |                          Are you a artist ???
 *                  ,----------.
 *                  | operator |
 *                 ,`----------'.
 *        ,______,'      |       `---------.
 *  ,---------. ,-----------------.  ,-----------.
 *  | options | | name_table list |  | name list |
 *  `---------' `-----------------'  `-----------'
 */


// linked list is easy to implement. at the same time it's useful.
struct _kv_pair {
    char first_[32];
    char second_[32];
    struct _kv_pair *next;
};

struct _DataType {
    uint32_t type_;
    uint64_t size_;
    uint8_t uz_;        // meaning unsigned or fill with zero..
    uint8_t isBin_;
};

struct _DefOpts {
    // struct _kv_pair *kvPair_;
    char nameRef_[32];
    int attri_;
    struct _DataType dataType_;

    struct _DefOpts *next;
};

struct _NameList {
    char ref_[32];
    struct _NameList *next;
};


struct _TablList {
    struct {
        // The `name_' MUST be set, and the `subColumns_' may point the null.
        char name_[32];
        char subColumns_[32];
    } _TablRef;
    struct _TablList *next;
};

// 全称应该是: delete sentence options...帮助记忆...
struct _DelSetceOpts {
    uint8_t optsDel_;       // 标志诸如`QUICK', `LOW PRIORITY' 等选项..

    // opt_where
    struct _Express;
    // opt_limit
};


struct _SqlOpts {
    struct _NameList *optColName_;

    /* 下面的成员用于delete语句使用 */
    struct _DelSetceOpts *delOpts_;
};

// alias...
typedef struct _NameList columns_list_t;

// 如果`ref_sec' 没有参数,直接将它设置味 `NULL' 就好
struct _TablList *new_tabl_list(char *ref_fir, char *ref_sec);
void add_tabl_list(struct _TablList *head, char *ref);
void del_tabl_list(struct _TablList *list);

struct _OprtNode *new_oprt_node(enum OprtType type);
void del_oprt_node(struct _OprtNode *node);

columns_list_t *new_NameList_node();
void add_NameList_node(columns_list_t *head, const char *ref);
void del_NameList_node(columns_list_t *root);


// kv_pair 目前一直还没有用到..select语句完成后将计划其移除
struct _kv_pair *new_kvPair_node(char *key, char *value);
void add_kvPair_node(struct _kv_pair *list, char *key, char *value);
void del_kvPair_node(struct _kv_pair *kv);

struct _DefOpts *new_DefOpts_node();
void del_DefOpts_node(struct _DefOpts *node);

struct _SqlOpts *new_SqlOpts_node();
void del_SqlOpts_node(struct _SqlOpts *node);


struct _DelSetceOpts *new_DelSetceOpts_node();
void del_DelSetceOpts_node(struct _DelSetceOpts *root);

// TODO:parser 里的expr规则需要重新建立树...
struct _ExprVar {
    uint8_t type_;
    char data_[16];
    // 这里必须建立标准的二叉树, 不能使用诡异的树了,23333.
    // 二叉树的作用当然是作为求值使用.
    struct _ExprVar *ltree_;        // expr ast-tree 的左子树
    struct _ExprVar *rtree_;        // expr ast-tree 的右子树
};

// structure `_ExprVar' 's container..
struct _ExprVarCon {
    struct _ExprVar *data_;
    struct _ExprVarCon *next;
};

struct _ExprVarCon *new_ExprVarCon_node();
void add_ExprVar_node(struct _ExprVarCon *root, struct _ExprVar *node);
void del_ExprVarCon_node(struct _ExprVarCon *);

struct _ExprVar *new_Expr_node();
void del_ExprVar_node(struct _ExprVar *node);

#ifdef __cplusplus
} // extern "C"
#endif


#endif //AST_H_
