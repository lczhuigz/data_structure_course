#include <iostream>


using namespace std;


// 创建结构体节点
struct Node{
    int data;
    Node *next;
};
// 创建栈
struct Stack{
    Node * top;
    Node * bottom;
};
// 初始化栈func
void init_stack(Stack &s){
    s.top = nullptr;
    s.bottom = nullptr;
}
// 入栈func
bool push(Stack &s, int e){
    Node *p = new Node;
    p -> data = e;
    p -> next = nullptr;

    if(s.bottom == nullptr){
        s.bottom = p;
        s.top = p;
    }else{
        s.top -> next = p;
        s.top = p;
    }

    return true;
}
// 出栈func
bool pop(Stack &s, int &e){
    if(s.bottom == nullptr){
        return false;
    }

    Node *p = s.top;
    e = p -> data;

    if(s.bottom == s.top){
        s.bottom = nullptr;
        s.top = nullptr;
    }else{
        Node *q = s.bottom;
        while(q -> next != s.top){
            q = q-> next;
        }
        q -> next = nullptr;
        s.top = q;
    }

    delete p;

    return true;
}
// 计算栈长func
int length(const Stack &s){
    int n = 0;
    Node *p = s.bottom;
    while(p != nullptr){
        n ++;
        p = p -> next;
    }

    return n;
}
// 打印栈func
void printStack(const Stack &s){
    Node *p = s.bottom;
    if(p == nullptr){
        cout << "empty stack !" << endl;
        return ;
    }

    cout << "stack(bottom->top):";
    while(p != nullptr){
        cout << p -> data << " ";
        p = p -> next;
    }

    cout << endl;
}
// 释放栈func
void destroyStack(Stack &s){
    Node *p = s.bottom;
    while(p != nullptr){
        Node *q = p -> next;
        delete p;
        p = q;
    }
    s.bottom = nullptr;
    s.top = nullptr;
}


int main(int argc, char ** argv){

    Stack s1;
    int a[] = {67, 3, 88, 6, 1, 7, 0};
    int n = sizeof(a) / sizeof(a[0]);
    int e;

    init_stack(s1);

    for(int i = 0; i < n; i ++){
        push(s1, a[i]);
    }

    cout << "after creating s1:" << endl;
    printStack(s1);

    push(s1, -9);
    cout << "after pushing -9:" << endl;
    printStack(s1);

    cout << "pop 3 elements continuously:" << endl;
    for (int i = 0; i < 3; i++) {
        if (pop(s1, e)) {
            cout << "popped element " << i + 1 << ": " << e << endl;
        }
    }

    cout << "after deleting 3 top elements:" << endl;
    printStack(s1);

    cout << "current number of elements in stack: " << length(s1) << endl;

    destroyStack(s1);


    return 0;
}