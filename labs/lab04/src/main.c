#include <stdio.h>
#include <stdlib.h>

//  二叉树节点结构体
typedef struct _bitnode{
    char data;
    struct _bitnode *lchild, *rchild;
}bitnode, *bitree;

//  创建二叉树指针函数
bitree create(){
    char ch;
    scanf(" %c", &ch);
    if(ch == '#'){
        return NULL;
    }
    bitree T = (bitree)malloc(sizeof(bitnode));
    if(T == NULL){
        puts("内存分配失败！\n");
        exit(1);
    }
    T -> data = ch;
    T -> lchild = create();
    T -> rchild = create();

    return T;
}
//  前序遍历函数
void pre_order(bitree T){
    if(T != NULL){
        printf("%c ", T -> data);
        pre_order(T -> lchild);
        pre_order(T -> rchild);
    }
}
//  中序遍历函数
void in_order(bitree T){
    if(T != NULL){
        in_order(T -> lchild);
        printf("%c ", T -> data);
        in_order(T -> rchild);
    }
}
//  后序遍历函数
void post_order(bitree T){
    if(T != NULL){
        post_order(T -> lchild);
        post_order(T -> rchild);
        printf("%c ", T -> data);
    }
}
//  计算节点数量函数
int node_count(bitree T){
    if(T == NULL){
        return 0;
    }

    return 1 + node_count(T -> lchild) + node_count(T -> rchild);
}
//  销毁二叉树函数
void destroy_tree(bitree T){
    if(T != NULL){
        destroy_tree(T -> lchild);
        destroy_tree(T -> rchild);
        free(T);
    }
}


int main(int argc, char ** argv){
    bitree T;
    puts("请输入先序序列（#表示空结点）：\n");
    T = create();

    puts("先序遍历结果：");
    pre_order(T);
    putchar('\n');

    puts("中序遍历结果：");
    in_order(T);
    putchar('\n');

    puts("后序遍历结果：");
    post_order(T);
    putchar('\n');

    printf("二叉树结点个数：%d\n", node_count(T));

    destroy_tree(T);


    return 0;
}