//
// Created by ibrah on 5/10/2022.
//

#ifndef IBR_BST_H
#define IBR_BST_H


#include "EmployeeAux.h"

    template<class Key>
class BST {
public:
    struct node {
        Key key;
        EmployeeAux* info;
        node *right_son;
        node *left_son;
        node *father;
        long long int Height;
        long long int gradesSumOfGreater;
        long long int rank;


    };
    bool istoDelete;
    node *root;
    node *iterator;
    long long int Size;

    void DeleteNode(node *&ToDelete);

private:
    long long int height(node *Node);

    long long int max(long long int x, long long int y);

    node *&InsertNode(Key key, EmployeeAux* info, node *&NodeToAdd);

    node *RemoveNode(Key key, node *Tree);

    node *RotateRight(node *&Node);

    node *RotateLeft(node *&Node);

    node *FindSmallestNode(node *Tree);

    node *FindBiggestNode(node *Tree);


    EmployeeAux &FindNode(Key key, node *Tree);

    EmployeeAux* FindNode2(Key key, node *Tree);

    void fill2(EmployeeAux** arr, long long int *index, node *node);

    void fillComp2(EmployeeAux** arr, long long int *index, node *node, long long int *count);

    void nodesArr2(node **arr, long long int *index, node *node);
    void nodesArr4(node **arr, long long int *index, node *node,long long int size);

    void updateHeightAfterMerge2(node* node);
    void getNum2(Key min, Key max,long long int* all,node* node);
    void fillLast2(EmployeeAux** arr,long long int* index,Key min, Key max,node* node,long long int size);


//    node* makeAvl2(node** arr,long long int begin,long long int end,long long int* cnt);


public:
//    void getNum3(long long int min, long long int max, long long int *all, long long int *match, long long int minGrade, long long int minSal,node* node);

    void fillLast(EmployeeAux** arr,long long int* index,Key min, Key max,long long int size);
    void getNum(Key min, Key max,long long int* all);
    void updateHeightAfterMerge();
    node* makeAvl(node** arr,long long int begin,long long int end,long long int* cnt);
    node* findMostLeftBySalary(long long int salary,node* Tree) ;
    node* findMostRightBySalary(long long int salary,node* Tree) ;
    long long int calcRank(Key key,node* Tree);

    long long int calcBetween(long long int lowSal,long long int highSal, long long int * num);

    void nodesArr(node **arr, long long int *index);
    void nodesArr3(node **arr, long long int *index,long long int size);


    void fill(EmployeeAux** arr, long long int *index);

    void fillComp(EmployeeAux** arr, long long int *index, long long int *count);

    explicit BST(bool toDelete=false);

    ~BST();

    node *insert(Key key, EmployeeAux* info);

    void remove(Key key);
    long long int getBalance(node *N);
    long long int GetSize();
    long long int& ModSize();

    void ResetIterator();

    EmployeeAux &NextIteration(Key **key);

    long long int GetHeight();

    EmployeeAux &Find(Key key);

    EmployeeAux* Find2(Key k);
    long long int Postorder(node* node);
    long long int Postorder2(node* node);
    long long int inorder(node* node);
        long long int inorder11(node* node);

    long long int findByRank(long long int rank1, node* temp,long long int sumRank);
    long long int calcSumGrades(Key key,node* Tree);
    void clear();

    EmployeeAux* highest();

    class FailureException {
    };

    class KeyNotFound : public FailureException {
    };

//    void getNum2(long long int min, long long int max, long long int *all, long long int *match, long long int minGrade, long long int minSal, node *node);
//
//    void getNum3(long long int min, long long int max, long long int *all, long long int *match, long long int minGrade, long long int minSal, node *node);
};

template<class Key>
BST<Key>::BST(bool toDelete):istoDelete(toDelete), root(nullptr),iterator(nullptr),Size(0){}

template<class Key>
BST<Key>::~BST<Key>() {
    DeleteNode(root);
}

template<class Key>
typename BST<Key>::node* BST<Key>::insert(Key key, EmployeeAux* info){
    return InsertNode(key,info,root);
}

template<class Key>
void BST<Key>::remove(Key key) {
    root = RemoveNode(key,root);
}

template<class Key>
typename BST<Key>::node*& BST<Key>::InsertNode(Key key,EmployeeAux* info1, node*& NodeToAdd) {

    if(NodeToAdd == nullptr)
    {
        NodeToAdd = new node;
        NodeToAdd->key = key;
        NodeToAdd->info = info1;

        NodeToAdd->rank=1;
        NodeToAdd->gradesSumOfGreater=info1->employee.employeeGrade;

        NodeToAdd->Height = 1;
        NodeToAdd->left_son =nullptr;
        NodeToAdd->right_son =nullptr;
        NodeToAdd->father = nullptr;
        Size++;
    }
    else if(key == NodeToAdd->key)

        throw FailureException{};

    else if(key < NodeToAdd->key) {

        NodeToAdd->rank++;
        NodeToAdd-> gradesSumOfGreater+=info1->employee.employeeGrade;


        NodeToAdd->left_son = InsertNode(key,info1,NodeToAdd->left_son);
        NodeToAdd->left_son->father = NodeToAdd;
        if (height(NodeToAdd->left_son) - height(NodeToAdd->right_son) == 2) {
            if (key < NodeToAdd->left_son->key)
                NodeToAdd = RotateRight(NodeToAdd);//LL
            else {
                NodeToAdd->left_son = RotateLeft(NodeToAdd->left_son);//LR
                NodeToAdd = RotateRight(NodeToAdd);
            }
        }
    }
    else if(key > NodeToAdd->key)
    {
        NodeToAdd->rank++;
        NodeToAdd-> gradesSumOfGreater+=info1->employee.employeeGrade;


        NodeToAdd->right_son = InsertNode(key,info1,NodeToAdd->right_son);
        NodeToAdd->right_son->father = NodeToAdd;
        if(height(NodeToAdd->left_son) - height(NodeToAdd->right_son) == -2)
        {
            if(key > NodeToAdd->right_son->key)
                NodeToAdd = RotateLeft(NodeToAdd);//RR
            else{
                NodeToAdd->right_son = RotateRight(NodeToAdd->right_son);//RL
                NodeToAdd = RotateLeft(NodeToAdd);
            }
        }
    }

    NodeToAdd->Height = max(height(NodeToAdd->left_son), height(NodeToAdd->right_son))+1;
    return NodeToAdd;
}






template<class Key>
typename BST<Key>::node* BST<Key>::RotateRight(node *&Node) {

    node* TempNode = Node->left_son;
    Node->left_son = TempNode->right_son;
    Node->rank=1;
    Node->gradesSumOfGreater=Node->info->employee.employeeGrade;
    if(Node->left_son) {
        Node->left_son->father = Node;
        Node->gradesSumOfGreater=Node->info->employee.employeeGrade+Node->left_son->gradesSumOfGreater;
        Node->rank=1+Node->left_son->rank;
    }
    if(Node->right_son){
        Node->gradesSumOfGreater+=Node->right_son->gradesSumOfGreater;
        Node->rank+=Node->right_son->rank;
    }
    TempNode->right_son = Node;
    TempNode->father = Node->father;
    Node->father = TempNode;
    Node->Height = max(height(Node->left_son), height(Node->right_son))+1;
    TempNode->Height = max(height(TempNode->left_son), Node->Height)+1;

    TempNode->rank=1;
    TempNode->gradesSumOfGreater=TempNode->info->employee.employeeGrade;
    if(TempNode->right_son){
        TempNode->rank+=TempNode->right_son->rank;
        TempNode->gradesSumOfGreater+=TempNode->right_son->gradesSumOfGreater;

    }
    if(TempNode->left_son){
        TempNode->rank+=TempNode->left_son->rank;
        TempNode->gradesSumOfGreater+=TempNode->left_son->gradesSumOfGreater;

    }

    return TempNode;

}

template<class Key>
typename BST<Key>::node* BST<Key>::RotateLeft(node *&Node){

    node* TempNode = Node->right_son;
    Node->right_son = TempNode->left_son;
    Node->rank=1;
    Node->gradesSumOfGreater=Node->info->employee.employeeGrade;

    if(Node->right_son) {
        Node->right_son->father = Node;
        Node->gradesSumOfGreater=Node->info->employee.employeeGrade+Node->right_son->gradesSumOfGreater;

        Node->rank=1+Node->right_son->rank;

    }
    if(Node->left_son){
        Node->gradesSumOfGreater+=Node->left_son->gradesSumOfGreater;

        Node->rank+=Node->left_son->rank;
    }

    TempNode->left_son = Node;
    TempNode->father = Node->father;
    Node->father = TempNode;
    Node->Height = max(height(Node->left_son), height(Node->right_son))+1;
    TempNode->Height = max(height(TempNode->right_son), Node->Height)+1 ;
    TempNode->rank=1;
    TempNode->gradesSumOfGreater=TempNode->info->employee.employeeGrade;
    if(TempNode->right_son){
        TempNode->rank+=TempNode->right_son->rank;
        TempNode->gradesSumOfGreater+=TempNode->right_son->gradesSumOfGreater;

    }
    if(TempNode->left_son){
        TempNode->rank+=TempNode->left_son->rank;
        TempNode->gradesSumOfGreater+=TempNode->left_son->gradesSumOfGreater;

    }
    return TempNode;
}

template<class Key>
long long int BST<Key>::height(node *Node) {
    long long int Right = 0;
    long long int Left = 0;
    if(Node == nullptr)
        return 0;
    if(Node->right_son)
        Right = Node->right_son->Height;
    if(Node->left_son)
        Left = Node->left_son->Height;
    return max(Right,Left)+1;
}

template<class Key>
long long int BST<Key>::max(long long int x, long long int y) {
    return (x > y ? x : y);
}

template<class Key>
typename BST<Key>::node* BST<Key>::FindSmallestNode(node* Tree) {
    if(Tree == nullptr)
        return Tree;
    else if(Tree->left_son == nullptr)
        return Tree;
    return FindSmallestNode(Tree->left_son);
}

template<class Key>
typename BST<Key>::node* BST<Key>::FindBiggestNode(node* Tree) {
    if (Tree == nullptr)
        return Tree;
    else if (Tree->right_son == nullptr)
        return Tree;
    return FindBiggestNode(Tree->right_son);
}

template<class Key>
long long int BST<Key>::getBalance(node *N)
{
    if (N == nullptr)
        return 0;
    return height(N->left_son) -
           height(N->right_son);
}



template<class Key>
typename BST<Key>::node* BST<Key>::RemoveNode(Key key, node* tempRoot) {


    // STEP 1: PERFORM STANDARD BST DELETE
    if (tempRoot == nullptr)
        return tempRoot;

    // If the key to be deleted is smaller
    // than the tempRoot's key, then it lies
    // in left_son subtree
    if (key < tempRoot->key) {

        tempRoot->rank--;
        tempRoot-> gradesSumOfGreater-=key.employeeGrade;

        tempRoot->left_son = RemoveNode(key, tempRoot->left_son);
    }
        // If the key to be deleted is greater
        // than the tempRoot's key, then it lies
        // in right_son subtree
    else if (key > tempRoot->key) {

        tempRoot->rank--;
        tempRoot-> gradesSumOfGreater-=key.employeeGrade;

        tempRoot->right_son = RemoveNode(key, tempRoot->right_son);
    }
        // if key is same as tempRoot's key, then
        // This is the node to be deleted
    else
    {
        tempRoot->rank--;
        tempRoot-> gradesSumOfGreater-=key.employeeGrade;
        // node with only one child or no child
        if( (tempRoot->left_son == nullptr) ||
            (tempRoot->right_son == nullptr) )
        {
            node *temp = tempRoot->left_son ?
                         tempRoot->left_son :
                         tempRoot->right_son;

            // No child case
            if (temp == nullptr)
            {

                temp = tempRoot;
                tempRoot = nullptr;
            }
            else // One child case
            {
                tempRoot->key =temp->key; // Copy the contents of
                tempRoot->info=temp->info;
                tempRoot->right_son= temp->right_son;
                tempRoot->left_son= temp->left_son;
               // tempRoot->father=temp->father;

            }

            delete temp;
            Size--;
        }
        else
        {

            // node with two children: Get the inorder
            // successor (smallest in the right_son subtree)
            node* temp = FindSmallestNode(tempRoot->right_son);

            // Copy the inorder successor's
            // data to this node
            tempRoot->key =temp->key; // Copy the contents of
            tempRoot->info=temp->info;
            // Delete the inorder successor
            tempRoot->right_son = RemoveNode(temp->key,tempRoot->right_son);
        }
    }

    // If the tree had only one node
    // then return
    if (tempRoot == nullptr)
        return tempRoot;

    // STEP 2: UPDATE HEIGHT OF THE CURRENT NODE
    tempRoot->Height = 1 + max(height(tempRoot->left_son),
                               height(tempRoot->right_son));

    // STEP 3: GET THE BALANCE FACTOR OF
    // THIS NODE (to check whether this
    // node became unbalanced)
    long long int balance = getBalance(tempRoot);

    // If this node becomes unbalanced,
    // then there are 4 cases

    // left_son left_son Case
    if (balance > 1 &&
        getBalance(tempRoot->left_son) >= 0)
        return RotateRight(tempRoot);

    // left_son right_son Case
    if (balance > 1 &&
        getBalance(tempRoot->left_son) < 0)
    {
        tempRoot->left_son = RotateLeft(tempRoot->left_son);
        return RotateRight(tempRoot);
    }

    // right_son right_son Case
    if (balance < -1 &&
        getBalance(tempRoot->right_son) <= 0)
        return RotateLeft(tempRoot);

    // right_son left_son Case
    if (balance < -1 &&
        getBalance(tempRoot->right_son) > 0)
    {
        tempRoot->right_son = RotateRight(tempRoot->right_son);
        return RotateLeft(tempRoot);
    }

    return tempRoot;

/////////////////////////////////////////////////////////////////////////////////
}

template<class Key>
EmployeeAux& BST<Key>::FindNode(Key key,node* Tree){
    if(!Tree)
        throw KeyNotFound();
    if(key > Tree->key)
        return FindNode(key,Tree->right_son);
    else if(key < Tree->key)
        return FindNode(key,Tree->left_son);
    return Tree->info;
}

template<class Key>
EmployeeAux* BST<Key>::FindNode2(Key key,node* Tree){
    if(!Tree)
        return nullptr;
    if(key > Tree->key)
        return FindNode2(key,Tree->right_son);
    else if(key < Tree->key)
        return FindNode2(key,Tree->left_son);
    return (Tree->info);
}

template<class Key>
void BST<Key>::DeleteNode(node*& ToDelete) {
    if(!ToDelete || Size == 0)
        return;
    DeleteNode(ToDelete->right_son);
    DeleteNode(ToDelete->left_son);
    Size--;
    if(istoDelete)
    delete ToDelete->info;
    ToDelete->info= nullptr;
    delete ToDelete;
}

template<class Key>
long long int BST<Key>::GetSize(){
    return Size;
}
template<class Key>
long long int& BST<Key>::ModSize(){
    return Size;
}
template<class Key>
long long int BST<Key>::GetHeight(){
    return height(root);
}

template<class Key>
EmployeeAux& BST<Key>::Find(Key key) {
    return FindNode(key,root);
}
template<class Key>
EmployeeAux* BST<Key>::Find2(Key key) {
    return FindNode2(key,root);
}

template<class Key>
void BST<Key>::clear() {
    DeleteNode(root);
}

template<class Key>
void BST<Key>::ResetIterator(){
    iterator = root;
    iterator = FindSmallestNode(iterator);
}

template<class Key>
EmployeeAux& BST<Key>::NextIteration(Key **key) {
    if(iterator == nullptr)
        throw FailureException{};
    **key = iterator->key;
    EmployeeAux& Temp = iterator->info;
    if (iterator->right_son) {
        iterator = iterator->right_son;
        while (iterator->left_son) {
            iterator = iterator->left_son;
        }
    } else {
        while (iterator->father && iterator == iterator->father->right_son) {
            iterator = iterator->father;
        }
        iterator = iterator->father;
    }
    return Temp;
}

template<class Key>
EmployeeAux* BST<Key>::highest() {
    if(root== nullptr) return nullptr;
    auto temp=this->root;
    while (temp->right_son){
        temp=temp->right_son;
    }
    return temp->info;
}

template<class Key>
void BST<Key>::fill2(EmployeeAux** arr, long long int *index, BST::node *node) {
    if(this->root== nullptr) return;
    if(node->right_son){
        fill2(arr,index,node->right_son);
    }
    arr[(*index)]=node->info;
    (*index)++;
    if(node->left_son){
        fill2(arr,index,node->left_son);
    }
}

template<class Key>
void BST<Key>::fill(EmployeeAux** arr, long long int *index) {
    return fill2(arr,index,this->root);
}

template<class Key>
void BST<Key>::fillComp(EmployeeAux** arr, long long int *index,long long int* count) {
    return fillComp2(arr,index,this->root,count);
}

template<class Key>
void BST<Key>::fillComp2(EmployeeAux** arr, long long int *index, BST::node *node,long long int* count) {
    if(this->root== nullptr || (*count)==(*index)) return;
    if(node->left_son){
        fillComp2(arr,index,node->left_son,count);
    }
    arr[(*index)]=node->info;
    (*index)++;
    if(node->right_son){
        fillComp2(arr,index,node->right_son,count);
    }
}

template<class Key>
void BST<Key>::nodesArr(node **arr, long long int *index){
    nodesArr2(arr,index,this->root);
}

template<class Key>
void BST<Key>::nodesArr2(BST::node **arr, long long int *index, BST::node *node) {
    if (node == nullptr) return;
    if (node->left_son){
        nodesArr2(arr,index,node->left_son);
    }
    arr[(*index)]=node;
    (*index)++;
    if(node->right_son){
        nodesArr2(arr,index,node->right_son);
    }
}


template<class Key>
void BST<Key>::nodesArr3(node **arr, long long int *index,long long int size){
    nodesArr4(arr,index,this->root,size);
}

template<class Key>
void BST<Key>::nodesArr4(node **arr, long long int *index, node *node,long long int size) {
    if (node == nullptr || (*index)==size) return;
    if (node->left_son){
        nodesArr4(arr,index,node->left_son,size);
    }
    arr[(*index)]=node;
    (*index)++;
    if (node == nullptr || (*index)==size) return;

    if(node->right_son){
        nodesArr4(arr,index,node->right_son,size);
    }
}



template<class Key>
typename BST<Key>::node* BST<Key>::makeAvl(node** arr,long long int begin,long long int end,long long int* cnt){
    if(begin > end){
        return nullptr;
    }
    long long int mid=(begin+end)/2;
    auto nodeNew=arr[mid];
    *cnt=*cnt+1;
    if(*cnt==1){
        root=nodeNew;
    }
    nodeNew->left_son= makeAvl(arr,begin,mid-1,cnt);
    if(nodeNew->left_son != nullptr){
        nodeNew->left_son->father=nodeNew;
    }
    nodeNew->right_son= makeAvl(arr,mid+1,end,cnt);
    if(nodeNew->right_son != nullptr){
        nodeNew->right_son->father=nodeNew;
    }
    return nodeNew;
}




template<class Key>
void BST<Key>::updateHeightAfterMerge2(BST::node *node) {
    if(node== nullptr) return;
    updateHeightAfterMerge2(node->left_son);
    updateHeightAfterMerge2(node->right_son);
    if(node->left_son == nullptr && node->right_son == nullptr){
        node->Height=0;
        return;
    }
    if(node->right_son== nullptr && node->left_son!= nullptr){
        node->Height=node->left_son->Height+1;
        return;
    }
    if(node->right_son != nullptr && node->left_son== nullptr){
        node->Height=node->right_son->Height+1;
        return;
    }
    if(node->right_son->Height > node->left_son->Height){
        node->Height=node->right_son->Height+1;
        return;
    }
    node->Height=node->left_son->Height+1;

}

template<class Key>
void BST<Key>::updateHeightAfterMerge() {
    updateHeightAfterMerge2(this->root);
}

template<class Key>
void BST<Key>::getNum(Key min, Key max, long long int *all) {
    return getNum2(min,max,all, this->root);
}

template<class Key>
void BST<Key>::getNum2(Key min, Key max, long long int *all, BST::node *node) {
    if(node== nullptr) return;
    if(node->key>=min && node->key<=max){
        (*all)++;
        getNum2(min,max,all,node->right_son);
        getNum2(min,max,all,node->left_son);



    }
    else if(node->key<min){
        getNum2(min,max,all,node->right_son);
    }
    else{
        getNum2(min,max,all,node->left_son);
    }
}


template<class Key>
void BST<Key>::fillLast(EmployeeAux** arr, long long int *index, Key min, Key max,long long int size){
    return fillLast2(arr,index,min,max,root,size);

}


template<class Key>
void BST<Key>::fillLast2(EmployeeAux** arr, long long int *index, Key min, Key max, BST::node *node,long long int size) {
    if (node == nullptr) return;
    if((*index)==size) return;
    if(node->key <= max && node->key >= min){
        arr[(*index)]=node->info;
        (*index)++;
        fillLast2(arr,index,min,max,node->left_son,size);
        fillLast2(arr,index,min,max,node->right_son,size);
    }
    else if(node->key < min){
        fillLast2(arr,index,min,max,node->right_son,size);
    }
    else{
        fillLast2(arr,index,min,max,node->left_son,size);
    }
}

template<class Key>
long long int BST<Key>::findByRank(long long int rank1,node* temp,long long int sumRank) {


    long long int ss=0;
    if(temp->left_son) {
        ss=temp->left_son->rank;
    }
        if (rank1 < 1 + ss+sumRank) {
            return findByRank(rank1, temp->left_son,sumRank);
        } else if (rank1 > 1 + ss+sumRank){
            return findByRank(rank1, temp->right_son,1 + ss+sumRank);

        }
        else {
            long long int temp1=calcSumGrades(FindBiggestNode(root)->info->employee,root);
            long long int temp2=calcSumGrades(temp->info->employee,root);
            return temp1-temp2 +temp->info->employee.employeeGrade;
        }

}



template<class Key>

long long int BST<Key>::calcSumGrades(Key  key,node* Tree){

    if(!Tree)
        throw KeyNotFound();
    if(key > Tree->key)
        if(Tree->left_son)
            return calcSumGrades(key,Tree->right_son)+Tree->left_son->gradesSumOfGreater+Tree->info->employee.employeeGrade;
        else
            return calcSumGrades(key,Tree->right_son)+Tree->info->employee.employeeGrade;
    else if(key < Tree->key)
        return calcSumGrades(key,Tree->left_son);
    if(Tree->left_son)
        return Tree->info->employee.employeeGrade+Tree->left_son->gradesSumOfGreater;
    else
        return Tree->info->employee.employeeGrade;


}


template<class Key>
typename BST<Key>::node* BST<Key>::findMostLeftBySalary(long long int salary,node* Tree) {

    if(!Tree) return nullptr;


    if(salary > Tree->info->employee.employeeSalary){
        return findMostLeftBySalary(salary,Tree->right_son);

    }

    else if(salary <= Tree->info->employee.employeeSalary){
        node* temp=  findMostLeftBySalary(salary,Tree->left_son);
        if(!temp) return Tree;
        return temp;
    }
}

template<class Key>
typename BST<Key>::node* BST<Key>::findMostRightBySalary(long long int salary,node* Tree) {

    if(!Tree) return nullptr;
    if(salary >= Tree->info->employee.employeeSalary){
        node* temp=  findMostRightBySalary(salary,Tree->right_son);
        if(!temp) return Tree;
        return temp;
    }

    else if(salary < Tree->info->employee.employeeSalary){
        return findMostRightBySalary(salary,Tree->left_son);

    }
}

template<class Key>

long long int BST<Key>::calcBetween(long long int lowSal,long long int highSal, long long int * num){

    node* lowNode= findMostLeftBySalary(lowSal,root);
    node* highNode=findMostRightBySalary(highSal,root);
    if(!lowNode || !highNode) return -1;
    int tt1=calcRank(highNode->info->employee,root);
    int tt2=calcRank(lowNode->info->employee,root);
    *num=tt1-tt2+1;
    long long int xx1=calcSumGrades(highNode->info->employee,root);
    long long int xx2=calcSumGrades(lowNode->info->employee,root);

    return xx1-xx2+lowNode->info->employee.employeeGrade;

}
template<class Key>
long long int BST<Key>::calcRank(Key key,node* Tree){


    if(!Tree)
        throw KeyNotFound();
    if(key > Tree->key)
        if(Tree->left_son)
            return calcRank(key,Tree->right_son)+Tree->left_son->rank+1;
        else
            return calcRank(key,Tree->right_son)+1;
    else if(key < Tree->key)
        return calcRank(key,Tree->left_son);

    if(Tree->left_son)
        return 1+Tree->left_son->rank;
    else
        return 1;


}

template<class Key>
long long int BST<Key>::Postorder(BST::node *node) {

    if (node == nullptr)
        return 0;

   int temp1=Postorder(node->left_son);
   int temp2=Postorder(node->right_son);
   node->rank=1+temp2+temp1;
   return node->rank;

}
template<class Key>

long long int BST<Key>::Postorder2(BST::node *node) {

    if (node == nullptr)
        return 0;

    int temp1=Postorder2(node->left_son);
    int temp2=Postorder2(node->right_son);
    node->gradesSumOfGreater=node->info->employee.employeeGrade+Postorder2(node->left_son)+Postorder2(node->right_son);
    return node->gradesSumOfGreater;

}

template<class Key>
long long int BST<Key>::inorder(BST::node *node) {
    if (node == nullptr)
        return 0;

    return inorder(node->left_son)+inorder(node->right_son)+node->info->employee.employeeGrade;
    return 0;
}
template<class Key>
long long int BST<Key>::inorder11(BST::node *node) {
    if (node == nullptr)
        return 0;

    return inorder11(node->left_son)+inorder11(node->right_son)+node->info->employee.employeeGrade;
    return 0;
}




#endif //IBR_BST_H
