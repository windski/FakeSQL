#ifndef BPLUSTREE_H_
#define BPLUSTREE_H_

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdint.h>
#include <assert.h>

#define M (10)
#define LIMIT_M_2 (M % 2 ? (M + 1)/2 : M/2)
// 下面是内存对齐大小,后面为了调优应该需要改动.
#ifndef __ALIGN
#define __ALIGN 8
#endif


typedef struct BPlusNode *BPlusTree,*Position;
typedef int KeyType;
typedef int ValueType;
struct BPlusNode{
    uint64_t id;
    int KeyNum;
    KeyType Key[M + 1];
    ValueType Value[M+1];
    BPlusTree Children[M + 1];
    BPlusTree Next;
}__attribute__((aligned(__ALIGN)));



/* 初始化 */
extern BPlusTree Initialize();
/* 插入 */
extern BPlusTree Insert(BPlusTree T,KeyType Key,ValueType value);
/* 删除 */
extern BPlusTree Remove(BPlusTree T,KeyType Key);
/* 销毁 */
extern BPlusTree Destroy(BPlusTree T);


/*搜索节点*/
extern ValueType SearchKey(BPlusTree T,KeyType key);
/* 遍历节点 */
extern void Travel(BPlusTree T);
/* 遍历树叶节点的数据 */
extern void TravelData(BPlusTree T);

#endif /* BPlusTree_h */
