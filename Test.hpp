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

//��������������ջ�Ͷ��и�������
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
int IsEmptyStack(Stack* ps);//����1��ʾΪ��
SDataType TopStack(Stack* ps);

//����һ��������  ǰ�����˼��
void CreateBinTree(BTreeNode** BTnode, char* str, int size,
	int* index, DataType invalid);
BTreeNode* BuyBTNode(DataType data);//����һ���µĽڵ�
void PreOrder(BTreeNode* BTnode);//ǰ����� �� �� ��
void InOrder(BTreeNode* BTnode);//�������  �� �� ��
void PostOrder(BTreeNode* BTnode);//������� �� �� ��
BTreeNode* CopyBinTree(BTreeNode* BTnode);//�������ĸ���
void DestroyBinTree(BTreeNode** BTnode);//���ٶ����� ���������˼��
int GetSizeBinTreeCount(BTreeNode* BTnode);//���ض��������нڵ���
int GetLeafBinTreeCount(BTreeNode* BTnode);//���ض�����Ҷ�ӽڵ���
int GetKSizeBinTreeCount(BTreeNode* BTnode, int K);//���ض�������k��Ľڵ���
int HeightBinTree(BTreeNode* BTnode);//�õ��������ĸ߶�
BTreeNode* LeftBinTree(BTreeNode* BTnode);//�õ������������ӽڵ�
BTreeNode* RightBinTree(BTreeNode* BTnode);//�õ����������Һ��ӽڵ�
int IsExistInBinTree(BTreeNode* BTnode, BTreeNode* pNode);//�жϽڵ��Ƿ��ڶ�������
BTreeNode* ParentBinTree(BTreeNode* BTnode, BTreeNode* pNode);//���ؽڵ��˫�׽ڵ�
void LevelOrder(BTreeNode* BTnode);//�������������
void MirrorBinTree(BTreeNode* BTnode);//����������ݹ�
void MirrorBinTreeNor(BTreeNode* BTnode);//����������ǵݹ�
void Swap(BTreeNode** left, BTreeNode** right);//�������������Ӻ��Һ��ӽ���
int IsCompleteBinTree(BTreeNode* BTnode);//�ж϶������Ƿ�Ϊ��ȫ������

/////////////////�÷ǵݹ�ʵ�����ֱ�����ʽ//////////////////////
void PreOrderNor(BTreeNode* BTnode);//ǰ����� �� �� �� �ǵݹ�
void InOrderNor(BTreeNode* BTnode);//�������  �� �� �� �ǵݹ�
void PostOrderNor(BTreeNode* BTnode);//�������  �� �� �� �ǵݹ�

/////////////////���ӿƼ�������֮һ/////////////////////////
void PrintRight(BTreeNode* BTnode);//��ӡһ���������Ҳ�ڵ�


#endif //__BINTREE_H__
#endif