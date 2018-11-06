#include "bplustree.h"
#include "myque.h"

static KeyType Unavailable = INT_MIN;

static uint64_t __initIDval = 0;

/* 生成节点并初始化 */
static BPlusTree MallocNewNode()
{
    BPlusTree NewNode;
    int i;
    NewNode = malloc(sizeof(struct BPlusNode));
    if (NewNode == NULL)
        exit(EXIT_FAILURE);
    
    pthread_rwlock_init(&NewNode->rwlock, NULL);
    i = 0;

    pthread_rwlock_wrlock(&NewNode->rwlock);
    while (i < M + 1) {
        NewNode->Key[i] = Unavailable;
        NewNode->Value[i] = Unavailable;
        NewNode->Children[i] = NULL;
        i++;
    }

    NewNode->Next = NULL;
    NewNode->KeyNum = 0;

    pthread_rwlock_unlock(&NewNode->rwlock);
    return NewNode;
}

/* 初始化 */
extern BPlusTree Initialize(){
    
    BPlusTree T;    
    if (M < (3)){
        printf("M最小等于3！");
        exit(EXIT_FAILURE);
    }
    /* 根结点 */
    T = MallocNewNode();
    
    return T;
}

static Position FindMostLeft(Position P){
    Position Tmp;
    
    Tmp = P;
    
    while (Tmp != NULL && Tmp->Children[0] != NULL) {
        Tmp = Tmp->Children[0];
    }
    return Tmp;
}

static Position FindMostRight(Position P){
    Position Tmp;
    
    Tmp = P;
    
    while (Tmp != NULL && Tmp->Children[Tmp->KeyNum - 1] != NULL) {
        Tmp = Tmp->Children[Tmp->KeyNum - 1];
    }
    return Tmp;
}

/* 寻找一个兄弟节点，其存储的关键字未满，否则返回NULL */
static Position FindSibling(Position Parent,int i){
    Position Sibling;
    int Limit;
    
    Limit = M;
    
    Sibling = NULL;
    if (i == 0) {
        if (Parent->Children[1]->KeyNum < Limit)
            Sibling = Parent->Children[1];

    } else if (Parent->Children[i - 1]->KeyNum < Limit) {
        Sibling = Parent->Children[i - 1];

    } else if (i + 1 < Parent->KeyNum &&
            Parent->Children[i + 1]->KeyNum < Limit) {

        Sibling = Parent->Children[i + 1];
    }
    
    return Sibling;
}

/* 查找兄弟节点，其关键字数大于M/2 ;没有返回NULL*/
static Position FindSiblingKeyNum_M_2(Position Parent,int i,int *j)
{
    int Limit;
    Position Sibling;
    Sibling = NULL;
    
    Limit = LIMIT_M_2;
    
    if (i == 0) {
        if (Parent->Children[1]->KeyNum > Limit) {
            Sibling = Parent->Children[1];
            *j = 1;
        }
    } else {
        if (Parent->Children[i - 1]->KeyNum > Limit) {
            Sibling = Parent->Children[i - 1];
            *j = i - 1;
        
        } else if (i + 1 < Parent->KeyNum &&
                Parent->Children[i + 1]->KeyNum > Limit) {

            Sibling = Parent->Children[i + 1];
            *j = i + 1;
        }
        
    }
    
    return Sibling;
}

/* 当要对X插入Key的时候，i是X在Parent的位置，j是Key要插入的位置
   当要对Parent插入X节点的时候，i是要插入的位置，Key和j的值没有用
 */
static Position InsertElement(int isKey, Position Parent,Position X,KeyType Key,ValueType  value ,int i,int j)
{
    int k;
    if (isKey) {
        /* 插入key */
        k = X->KeyNum - 1;
        while (k >= j) {
            X->Key[k + 1] = X->Key[k];
            X->Value[k + 1] = X->Value[k];
            k--;
        }

        X->Key[j] = Key;
        X->Value[j]=value;

        if (Parent != NULL)
        {
            Parent->Key[i] = X->Key[0];
            Parent->Value[i] = X->Value[0];
        }

        
        X->KeyNum++;
        
    } else {
        /* 插入节点 */
        
        /* 对树叶节点进行连接 */
        if (X->Children[0] == NULL){
            if (i > 0)
                Parent->Children[i - 1]->Next = X;
            X->Next = Parent->Children[i];
        }
        
        k = Parent->KeyNum - 1;
        while (k >= i){
            Parent->Children[k + 1] = Parent->Children[k];
            Parent->Key[k + 1] = Parent->Key[k];
            Parent->Value[k+1] = Parent->Value[k];
            k--;
        }
        Parent->Key[i] = X->Key[0];
        Parent->Value[i]  = X->Value[0];
        Parent->Children[i] = X;
        
        Parent->KeyNum++;
        
    }
    return X;
}


static Position RemoveElement(int isKey, Position Parent,Position X,int i,int j)
{
    int k,Limit;
    
    if (isKey){
        Limit = X->KeyNum;
        /* 删除key */
        k = j + 1;
        while (k < Limit){
            X->Key[k - 1] = X->Key[k];
            X->Value[k-1] = X->Value[k];
            k++;
        }
        
        X->Key[X->KeyNum - 1] = Unavailable;
        X->Value[X->KeyNum - 1] = Unavailable;
        Parent->Key[i] = X->Key[0];
        Parent->Value[i] = X->Value[0];
        X->KeyNum--;
    }else{
        /* 删除节点 */
        
        /* 修改树叶节点的链接 */
        if (X->Children[0] == NULL && i > 0){
            Parent->Children[i - 1]->Next = Parent->Children[i + 1];
        }
        Limit = Parent->KeyNum;
        k = i + 1;
        while (k < Limit){
            Parent->Children[k - 1] = Parent->Children[k];
            Parent->Key[k - 1] = Parent->Key[k];
            Parent->Value[k-1] = Parent->Value[k];
            k++;
        }
        
        Parent->Children[Parent->KeyNum - 1] = NULL;
        Parent->Key[Parent->KeyNum - 1] = Unavailable;
        Parent->Value[Parent->KeyNum-1] = Unavailable;
        Parent->KeyNum--;
        
    }
    return X;
}

/* Src和Dst是两个相邻的节点，i是Src在Parent中的位置；
 将Src的元素移动到Dst中 ,n是移动元素的个数*/
static Position MoveElement(Position Src,Position Dst,Position Parent,int i,int n){
    KeyType TmpKey;
    ValueType  TmpValue;
    Position Child;
    int j,SrcInFront;
    
    SrcInFront = 0;
    
    if (Src->Key[0] < Dst->Key[0])
        SrcInFront = 1;
    
    j = 0;
    /* 节点Src在Dst前面 */
    if (SrcInFront){
        if (Src->Children[0] != NULL){
            while (j < n) {
                Child = Src->Children[Src->KeyNum - 1];
                RemoveElement(0, Src, Child, Src->KeyNum - 1, Unavailable);
                InsertElement(0, Dst, Child, Unavailable,Unavailable ,0, Unavailable);
                j++;
            }
        }else{
            while (j < n) {
                TmpKey = Src->Key[Src->KeyNum -1];
                TmpValue = Src->Value[Src->KeyNum-1];
                RemoveElement(1, Parent, Src, i, Src->KeyNum - 1);
                InsertElement(1, Parent, Dst, TmpKey,TmpValue, i + 1, 0);
                j++;
            }
            
        }
        
        Parent->Key[i + 1] = Dst->Key[0];
        Parent->Value[i+1] = Dst->Value[0];
        /* 将树叶节点重新连接 */
        if (Src->KeyNum > 0)
            FindMostRight(Src)->Next = FindMostLeft(Dst);
        
    }else{
        if (Src->Children[0] != NULL){
            while (j < n) {
                Child = Src->Children[0];
                RemoveElement(0, Src, Child, 0, Unavailable);
                InsertElement(0, Dst, Child, Unavailable,Unavailable, Dst->KeyNum, Unavailable);
                j++;
            }
            
        }else{
            while (j < n) {
                TmpKey = Src->Key[0];
                TmpValue = Src->Value[0];
                RemoveElement(1, Parent, Src, i, 0);
                InsertElement(1, Parent, Dst, TmpKey,TmpValue, i - 1, Dst->KeyNum);
                j++;
            }
            
        }
        
        Parent->Key[i] = Src->Key[0];
        Parent->Value[i] = Src->Value[0];
        if (Src->KeyNum > 0)
            FindMostRight(Dst)->Next = FindMostLeft(Src);
        
    }
    
    return Parent;
}

static BPlusTree SplitNode(Position Parent,Position X,int i){
    int j,k,Limit;

    Position NewNode;
    
    NewNode = MallocNewNode();
    
    k = 0;
    j = X->KeyNum / 2;
    Limit = X->KeyNum;
    while (j < Limit){
        if (X->Children[0] != NULL){
            NewNode->Children[k] = X->Children[j];

            X->Children[j] = NULL;
        }
        NewNode->Key[k] = X->Key[j];
        NewNode->Value[k] = X->Value[j];
        
        X->Key[j] = Unavailable;
        X->Value[j] = Unavailable;
        
        NewNode->KeyNum++;
        
        X->KeyNum--;
        
        j++;
        k++;
    }
    
    if (Parent != NULL) {
        InsertElement(0, Parent, NewNode, Unavailable,Unavailable, i + 1, Unavailable);
    } else {
        /* 如果是X是根，那么创建新的根并返回 */
        Parent = MallocNewNode();
        InsertElement(0, Parent, X, Unavailable,Unavailable, 0, Unavailable);
        InsertElement(0, Parent, NewNode, Unavailable,Unavailable, 1, Unavailable);
        
        return Parent;
    }
    
    return X;
}

/* 合并节点,X少于M/2关键字，S有大于或等于M/2个关键字*/
static Position MergeNode(Position Parent, Position X,Position S,int i){
    int Limit;
    
    /* S的关键字数目大于M/2 */
    if (S->KeyNum > LIMIT_M_2){
        /* 从S中移动一个元素到X中 */
        MoveElement(S, X, Parent, i,1);
    }else{
        /* 将X全部元素移动到S中，并把X删除 */
        Limit = X->KeyNum;
        MoveElement(X,S, Parent, i,Limit);
        RemoveElement(0, Parent, X, i, Unavailable);
        
        free(X);
        X = NULL;
    }
    
    return Parent;
}

static BPlusTree RecursiveInsert(BPlusTree T, KeyType Key, ValueType value, int i,BPlusTree Parent)
{
    int j,Limit;
    Position Sibling;
    
    /* 查找分支 */
    j = 0;
    while (j < T->KeyNum && Key >= T->Key[j]) {
        /* 重复值不插入 */
        if (Key == T->Key[j])
            return T;
        j++;
    }

    if (j!= 0 && T->Children[0] != NULL) {
        j--;        // why j--??
    }
    
    /* 树叶 */
    if (T->Children[0] == NULL)
        T = InsertElement(1, Parent, T, Key,value, i, j);
    /* 内部节点 */
    else
        T->Children[j] = RecursiveInsert(T->Children[j], Key,value, j, T);
    
    /* 调整节点 */
    
    Limit = M;
    
    if (T->KeyNum > Limit){
        /* 根 */
        if (Parent == NULL){
            /* 分裂节点 */
            T = SplitNode(Parent, T, i);
        }
        else{
            Sibling = FindSibling(Parent, i);
            if (Sibling != NULL){
                /* 将T的一个元素（Key或者Child）移动的Sibing中 */
                MoveElement(T, Sibling, Parent, i, 1);
            }else{
                /* 分裂节点 */
                T = SplitNode(Parent, T, i);
            }
        }
        
    }
    
    if (Parent != NULL)
        Parent->Key[i] = T->Key[0];
    
    
    return T;
}

/* 插入 */
extern BPlusTree Insert(BPlusTree T,KeyType Key,ValueType value){
    return RecursiveInsert(T, Key,value,0, NULL);
}

static BPlusTree RecursiveRemove(BPlusTree T,KeyType Key,int i,BPlusTree Parent){
    
    int j,NeedAdjust;
    Position Sibling,Tmp;
    
    Sibling = NULL;
    
    /* 查找分支 */
    j = 0;
    while (j < T->KeyNum && Key >= T->Key[j]){
        if (Key == T->Key[j])
            break;
        j++;
    }
    
    if (T->Children[0] == NULL){
        /* 没找到 */
        if (Key != T->Key[j] || j == T->KeyNum)
            return T;
    }else
        if (j == T->KeyNum || Key < T->Key[j]) j--;
    
    
    
    /* 树叶 */
    if (T->Children[0] == NULL){
        T = RemoveElement(1, Parent, T, i, j);
    }else{
        T->Children[j] = RecursiveRemove(T->Children[j], Key, j, T);
    }
    
    NeedAdjust = 0;
    /* 树的根或者是一片树叶，或者其儿子数在2到M之间 */
    if (Parent == NULL && T->Children[0] != NULL && T->KeyNum < 2)
        NeedAdjust = 1;
    /* 除根外，所有非树叶节点的儿子数在[M/2]到M之间。(符号[]表示向上取整) */
    else if (Parent != NULL && T->Children[0] != NULL && T->KeyNum < LIMIT_M_2)
        NeedAdjust = 1;
    /* （非根）树叶中关键字的个数也在[M/2]和M之间 */
    else if (Parent != NULL && T->Children[0] == NULL && T->KeyNum < LIMIT_M_2)
        NeedAdjust = 1;
    
    /* 调整节点 */
    if (NeedAdjust){
        /* 根 */
        if (Parent == NULL){
            if(T->Children[0] != NULL && T->KeyNum < 2){
                Tmp = T;
                T = T->Children[0];
                free(Tmp);
                return T;
            }
            
        }else{
            /* 查找兄弟节点，其关键字数目大于M/2 */
            Sibling = FindSiblingKeyNum_M_2(Parent, i,&j);
            if (Sibling != NULL){
                MoveElement(Sibling, T, Parent, j, 1);
            }else{
                if (i == 0)
                    Sibling = Parent->Children[1];
                else
                    Sibling = Parent->Children[i - 1];
                
                Parent = MergeNode(Parent, T, Sibling, i);
                T = Parent->Children[i];
            }
        }
        
    }

    
    return T;
}

/* 删除 */
extern BPlusTree Remove(BPlusTree T,KeyType Key)
{
    return RecursiveRemove(T, Key, 0, NULL);
}

/* 销毁 */
extern BPlusTree Destroy(BPlusTree T)
{
    int i,j;
    if (T != NULL) {
        i = 0;
        while (i < T->KeyNum + 1) {
            Destroy(T->Children[i]);
            i++;
        }

        printf("Destroy:(");
        j = 0;
        while (j < T->KeyNum) {
            /*  T->Key[i] != Unavailable*/
            printf("%d:",T->Key[j++]);
        }

        printf(") ");
        pthread_rwlock_destroy(&(T->rwlock));

        free(T);
        T = NULL;
    }
    
    return T;
}

static void RecursiveTravel(BPlusTree T,int Level)
{
    int i;
    if (T != NULL) {
        printf("  ");
        printf("[Level:%d]-->",Level);
        printf("(");
        i = 0;
        while (i < T->KeyNum) {
            /*  T->Key[i] != Unavailable*/
            printf("%d:",T->Key[i++]);
        }

        printf(")");

        Level++;

        i = 0;
        while (i <= T->KeyNum) {
            RecursiveTravel(T->Children[i], Level);
            i++;
        }
        
        
    }
}

ValueType SearchKey(BPlusTree T, KeyType key)
{
    Position Tmp;
    int i;
    Tmp = T;

    while (Tmp->Children[0] != NULL) {
        for(i = Tmp->KeyNum - 1; i >= 0; i--) {
            if(key >= Tmp->Key[i]) {
                Tmp = Tmp->Children[i];
                break;
            }
        }
    }

    if(Tmp->Children[0] == NULL) {
        int j = 0;
        for( ; j < Tmp->KeyNum; j++) {
            if(key == Tmp->Key[j])
            {
                printf("%d\n",Tmp->Value[j]);
                return Tmp->Value[j];
            }
        }
        printf("NO such key\n");
        return -1;
    }

    return -1;
}

/* fill it */
void FillTreeID_recur(BPlusTree T)
{
    if(T == NULL) {
        return ;
    }

    T->id = __initIDval++;
    for(int i = 0; i < M + 1; i++) {
        FillTreeID(T->Children[i]);
    }
}

/* fill it! by queue */
void FillTreeID(BPlusTree T)
{
    myque_t *que = myque_init();

    myque_append(que, T);
    while(!myque_isempty(que)) {
        BPlusTree tmp = myque_top(que);
        myque_pop(que);

        tmp->id = __initIDval++;
        for(int i = 0; i < M + 1; i++) {
            if(tmp->Children[i] == NULL) {
                continue;
            }

            if(myque_append(que, tmp->Children[i]) == -1) {
                printf("queue is not long enough.\n");
                exit(-1);
            }
        }
    }

    myque_destory(que);
}




/* 遍历 */
extern void Travel(BPlusTree T){
    RecursiveTravel(T, 0);
    printf("\n");
}

/* 遍历树叶节点的数据 */
extern void TravelData(BPlusTree T){
    Position Tmp;
    int i;
    if (T == NULL)
        return ;
    printf("All Data:");
    Tmp = T;
    while (Tmp->Children[0] != NULL)
        Tmp = Tmp->Children[0];
    /* 第一片树叶 */
    while (Tmp != NULL){
        i = 0;
        while (i < Tmp->KeyNum)
        {
            printf(" %d\n",Tmp->Key[i++]);

        }
        Tmp = Tmp->Next;
    }
}
