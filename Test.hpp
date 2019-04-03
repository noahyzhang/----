#if 0
#pragma once
#ifndef __BINTREE_H__
#define __BINTREE_H__

#include <stdio.h>
#include <assert.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>

#define MAXSIZE 10
typedef char DataType;

typedef struct BTreeNode
{
	DataType data;
	struct BTreeNode* left;
	struct BTreeNode* right;
}BTreeNode;

typedef BTreeNode* BDataType;

typedef struct Queue
{
	BDataType array[MAXSIZE];
	int front;
	int back;
	int count;
}Queue;

typedef BTreeNode* SDataType;

typedef struct Stack
{
	SDataType array[MAXSIZE];
	int top;
}Stack;

//二叉树面试题中栈和对列辅助操作
void InitQueue(Queue* q);
void PushQueue(Queue* q, BDataType data);
void PopQueue(Queue* q);
BDataType FrontQueue(Queue* q);
int IsEmptyQueue(Queue* q);
int GetCount(Queue* q);
/////////////////////////////////////////////////////////
void InitStack(Stack* ps);
void PushStack(Stack* ps, SDataType data);
void PopStack(Stack* ps);
int IsEmptyStack(Stack* ps);//返回1表示为空
SDataType TopStack(Stack* ps);

//创建一个二叉树  前序遍历思想
void CreateBinTree(BTreeNode** BTnode, char* str, int size,
	int* index, DataType invalid);
BTreeNode* BuyBTNode(DataType data);//创建一个新的节点
void PreOrder(BTreeNode* BTnode);//前序遍历 根 左 右
void InOrder(BTreeNode* BTnode);//中序遍历  左 根 右
void PostOrder(BTreeNode* BTnode);//后序遍历 左 右 根
BTreeNode* CopyBinTree(BTreeNode* BTnode);//二叉树的复制
void DestroyBinTree(BTreeNode** BTnode);//销毁二叉树 后序遍历的思想
int GetSizeBinTreeCount(BTreeNode* BTnode);//返回二叉树所有节点数
int GetLeafBinTreeCount(BTreeNode* BTnode);//返回二叉树叶子节点数
int GetKSizeBinTreeCount(BTreeNode* BTnode, int K);//返回二叉树第k层的节点数
int HeightBinTree(BTreeNode* BTnode);//得到二叉树的高度
BTreeNode* LeftBinTree(BTreeNode* BTnode);//得到二叉树的左孩子节点
BTreeNode* RightBinTree(BTreeNode* BTnode);//得到二叉树的右孩子节点
int IsExistInBinTree(BTreeNode* BTnode, BTreeNode* pNode);//判断节点是否在二叉树内
BTreeNode* ParentBinTree(BTreeNode* BTnode, BTreeNode* pNode);//返回节点的双亲节点
void LevelOrder(BTreeNode* BTnode);//层序遍历二叉树
void MirrorBinTree(BTreeNode* BTnode);//镜像二叉树递归
void MirrorBinTreeNor(BTreeNode* BTnode);//镜像二叉树非递归
void Swap(BTreeNode** left, BTreeNode** right);//交换函数，左孩子和右孩子交换
int IsCompleteBinTree(BTreeNode* BTnode);//判断二叉树是否为完全二叉树

/////////////////用非递归实现三种遍历方式//////////////////////
void PreOrderNor(BTreeNode* BTnode);//前序遍历 根 左 右 非递归
void InOrderNor(BTreeNode* BTnode);//中序遍历  左 根 右 非递归
void PostOrderNor(BTreeNode* BTnode);//后序遍历  左 右 根 非递归

/////////////////旷视科技笔试题之一/////////////////////////
void PrintRight(BTreeNode* BTnode);//打印一棵树的最右侧节点


#endif //__BINTREE_H__
#endif