//
// Created by falleuion on 8/17/18.
//

#include "ast.h"


#ifdef __cplusplus
# include <cstdio>
# include <cstdlib>
# include <cstring>
# include <cassert>

extern "C" {
#else
# include <stdlib.h>
# include <string.h>
# include <stdio.h>
# include <assert.h>

#endif

//
//ast_node_atom *new_atom_node(enum atom_types type, void *v)
//{
//    ast_node_atom *node = (ast_node_atom *)malloc(sizeof(ast_node_atom));
//    node->type = type;
//
//    switch(type) {
//    case AT_IDENTIFIER:
//    case AT_STRING:
//        node->value.string = (char *) malloc(strlen((char *) v) + 1);
//        strcpy(node->value.string, (char *) v);
//        break;
//    case AT_NUMBER:
//        node->value.number = *((long *) v);
//        break;
//    case AT_CONDITION:
//        node->value.subtok = *((int *)v);
//        break;
//    }
//    return node;
//}
//
//
//void add_atom_to_sexp(ast_node_sexp *_node, ast_node_atom *_item)
//{
//    ast_node_sexp *_next = (ast_node_sexp *)malloc(sizeof(ast_node_sexp));
//    bzero(_next, sizeof(ast_node_sexp));
//    _next->type = ST_NONE;
//    _node->type = ST_LIST;
//
//    _node->value.atom = _item;
//    _node->next = _next;
//    _next->next = NULL;
//}
//
//void delete_atom_node(ast_node_atom* node)
//{
//    switch(node->type) {
//    case AT_IDENTIFIER:
//    case AT_STRING:
//        free(node->value.string);
//        break;
//    case AT_NUMBER:
//        break;
//    }
//    free(node);
//}
//
//void print_node_atom(ast_node_atom* node)
//{
//    if(node->type == AT_IDENTIFIER) {
//        printf("identifier node: %s\n", node->value.string);
//    }
//    else if(node->type == AT_STRING) {
//        printf("string node: %s\n", node->value.string);
//    }
//    else if(node->type == AT_NUMBER) {
//        printf("number node: %ld\n", node->value.number);
//    }
//    else if(node->type == AT_CONDITION) {
//        printf("condition node's type: %d\n", node->value.subtok);
//    }
//    else {
//        printf("unknown atom node");
//    }
//}
//
//ast_node_sexp *new_sexp_node(enum sexp_types type, void *v)
//{
//    ast_node_sexp *node = (ast_node_sexp *)malloc(sizeof(ast_node_sexp));
//    node->type = type;
//    node->next = NULL;
//
//    switch(type) {
//        case ST_ATOM:
//            node->value.atom = (ast_node_atom*) v;
//            break;
//
//    }
//    return node;
//}
//
//void delete_sexp_node(ast_node_sexp *node)
//{
//    switch(node->type) {
//    case ST_ATOM:
//        delete_atom_node(node->value.atom);
//        break;
//    }
//    free(node);
//}
//
//void print_node_sexp(ast_node_sexp *node)
//{
//    if(node->type == ST_ATOM) {
//        printf("node is an atom: ");
//        print_node_atom(node->value.atom);
//    }
//    else {
//        printf("node is a what?\n");
//    }
//}
//
//
//ast_node_opts *new_opts_node(enum opts_types type, void *v)
//{
//    ast_node_opts *node = (ast_node_opts *)malloc(sizeof(ast_node_opts));
//    node->type = type;
//
//    switch(type) {
//    case OP_WHERE:
//        break;
//    }
//}
//
//void delete_opts_node(ast_node_opts *node)
//{
//    switch(node->type) {
//    case OP_HAVING:
//        break;
//    case OP_GROUPBY:
//        break;
//    case OP_LIMIT:
//        break;
//    case OP_ORDERBY:
//        break;
//    case OP_WHERE:
//        break;
//    }
//    free(node);
//}


// ----------------- added on ---------------------

struct _OprtNode *new_oprt_node(enum OprtType type)
{
    struct _OprtNode *root = (struct _OprtNode *)malloc(sizeof(struct _OprtNode));
    assert(root != NULL);
    
    bzero(root, sizeof(struct _OprtNode));
    root->type_ = type;
    return root;
}

void del_oprt_node(struct _OprtNode *node)
{
    assert(node != NULL);

    if(node->table_ != NULL) {
        del_tabl_list(node->table_);
    }
    switch(node->type_) {
    case TS_CREATE:
        del_DefOpts_node(node->universalList_.defOpts_);
        break;
    case TS_INSERT: {
        del_ExprVarCon_node(node->universalList_.exprVarCon_);
//        if(node->universalList_.defOpts_ != NULL) {
//            del_SqlOpts_node(node->universalList_.defOpts_);
//        }
    }
        break;
    default:
        // mei xiang hao
        break;
    }
}


struct _TablList *new_tabl_list(char *ref_fir, char *ref_sec)
{
    struct _TablList *list = (struct _TablList *)malloc(sizeof(struct _TablList));
    assert(list != NULL);

    bzero(list, sizeof(struct _TablList));
    assert(ref_fir != NULL);
    strncpy(list->_TablRef.name_, ref_fir, strlen(ref_fir));
    if(ref_sec != NULL) {
        strncpy(list->_TablRef.subColumns_, ref_sec, strlen((ref_sec)));
    }

    list->next = NULL;
    return list;
}

void add_tabl_list(struct _TablList *head, char *ref)
{

}

void del_tabl_list(struct _TablList *list)
{
    assert(list != NULL);

    struct _TablList *head = list;

    while(list != NULL) {
        free(head);

        list = list->next;
        head = list;
    }
}

// 直接申请两个节点,第一个为`root'节点, 它只存储链表,ref_不放任何东西.
// `root->next' 指向的地方才是链表真正指向的地方
columns_list_t *new_NameList_node()
{
    struct _NameList *tmp = (struct _NameList *)malloc(sizeof(struct _NameList));
    assert(tmp != NULL);

    bzero(tmp, sizeof(struct _NameList));
    tmp->next = NULL;

    return tmp;
}

void add_NameList_node(columns_list_t *node, const char *ref)
{

    struct _NameList *head = (struct _NameList *)malloc(sizeof(struct _NameList));
    assert(head != NULL);
    assert(node != NULL);

    strncpy(head->ref_, ref, strlen(ref));
    head->next = node->next;
    node->next = head;
}

void del_NameList_node(columns_list_t *node)
{
    assert(node != NULL);
    struct _NameList *head = node;

    while(node != NULL) {
        free(head);

        node = node->next;
        head = node;
    }
}


struct _kv_pair *new_kvPair_node(char *key, char *value)
{
    struct _kv_pair *tmp = (struct _kv_pair *)malloc(sizeof(struct _kv_pair));
    assert(tmp != NULL);

    bzero(tmp, sizeof(struct _kv_pair));
    strncpy(tmp->first_, key, strlen(key));
    strncpy(tmp->second_, value, strlen(value));

    tmp->next = NULL;
    return tmp;
}

void add_kvPair_node(struct _kv_pair *list, char *key, char *value)
{
    assert(list != NULL);
    struct _kv_pair *tmp = (struct _kv_pair *)malloc(sizeof(struct _kv_pair));

    strncpy(tmp->first_, key, strlen(key));
    strncpy(tmp->second_, value, strlen(value));

    tmp->next = list->next;
    list->next = tmp;
}

void del_kvPair_node(struct _kv_pair *kv)
{
    assert(kv != NULL);

    struct _kv_pair *head = kv;
    while(kv != NULL) {
        free(head);

        kv = kv->next;
        head = kv;
    }
}

struct _DefOpts *new_DefOpts_node()
{
    struct _DefOpts *node = (struct _DefOpts *)malloc(sizeof(struct _DefOpts));

    bzero(node, sizeof(struct _DefOpts));
//    node->kvPair_ = NULL;
    node->next = NULL;

    return node;
}

void del_DefOpts_node(struct _DefOpts *node)
{
    assert(node != NULL);

//    del_kvPair_node(node->kvPair_);
    struct _DefOpts *head = node->next;
    while(head != NULL) {
        free(node);
        node = head;

        head = head->next;
    }

}


struct _SqlOpts *new_SqlOpts_node()
{
    struct _SqlOpts *node = (struct _SqlOpts *)malloc(sizeof(struct _SqlOpts));
    assert(node != NULL);

    bzero(node, sizeof(struct _SqlOpts));
    return node;
}


void del_SqlOpts_node(struct _SqlOpts *node)
{
    assert(node != NULL);
    del_NameList_node(node->optColName_);
    free(node);
}


struct _ExprVarCon *new_ExprVarCon_node()
{
    struct _ExprVarCon *root = (struct _ExprVarCon *)malloc(sizeof(struct _ExprVarCon));
    assert(root != NULL);

    bzero(root, sizeof(struct _ExprVarCon));
    return root;
}

void add_ExprVar_node(struct _ExprVarCon *root, struct _ExprVar *node)
{
    assert(root != NULL);
    struct _ExprVarCon *head = (struct _ExprVarCon *)malloc(sizeof(struct _ExprVarCon));
    assert(head != NULL);

    head->data_ = node;
    head->next = root->next;
    root->next = head;
}


void del_ExprVarCon_node(struct _ExprVarCon *root)
{
    assert(root != NULL);

    struct _ExprVarCon *tmp = root;
    while(root != NULL) {
        free(tmp);

        root = root->next;
        tmp = root;
    }
}


struct _DelSetceOpts *new_DelSetceOpts_node()
{
    struct _DelSetceOpts *root = (struct _DelSetceOpts *)malloc(sizeof(struct _DelSetceOpts));

    bzero(root, sizeof(struct _DelSetceOpts));
    return root;
}

void del_DelSetceOpts_node(struct _DelSetceOpts *root)
{
    assert(root != NULL);

    free(root);
}


struct _ExprVar *new_Expr_node()
{
    struct _ExprVar *root = malloc(sizeof(struct _ExprVar));

    bzero(root, sizeof(struct _ExprVar));
    return root;
}


#ifdef __cplusplus
}
#endif
