#pragma once
#include<iostream>
using namespace std;

enum Color { RED, BLACK };

template<class V>
struct RBTreeNode {
	RBTreeNode(const V& data = V(), const Color color = RED)
		: _pLeft(nullptr)
		, _pRight(nullptr)
		, _pParent(nullptr)
		, _data(data)
		, _color(color)
	{}

	RBTreeNode<V>* _pLeft;
	RBTreeNode<V>* _pRight;
	RBTreeNode<V>* _pParent;
	V _data;
	Color _color;
};

template<class V>
class RBTree
{
	typedef RBTreeNode<V> Node;
	typedef Node* PNode;
public:
	RBTree()
	{
		_pHead = new Node;
		_pHead->_pLeft = _pHead;
		_pHead->_pRight = _pHead;
		_pHead->_pParent = nullptr;
	}
	~RBTree()
	{
		_Destroy(GetRoot());
	}
	bool Insert(const V& data)
	{
		PNode pCur = nullptr;
		PNode pParent = SearchNode(data, pCur);
		return CheckCondition(pParent, pCur);
	}

	void PrintOrder()
	{
		PNode pRoot = GetRoot();
		_InOrder(pRoot);
	}

private:
	PNode SearchNode(const V& data, PNode& pCur)
	{
		PNode pRoot = GetRoot();
		if (pRoot == nullptr)
		{
			pRoot = new Node(data, BLACK);
			_pHead->_pParent = pRoot;
		}
		else
		{
			pCur = pRoot;
			PNode pParent = nullptr;
			while (pCur)
			{
				pParent = pCur;
				if (data < pCur->_data)
					pCur = pCur->_pLeft;
				else if (data > pCur->_data)
					pCur = pCur->_pRight;
				else
					return nullptr;
			}
			pCur = new Node(data, RED);
			if (data < pParent->_data)
				pParent->_pLeft = pCur;
			else
				pParent->_pRight = pCur;

			pCur->_pParent = pParent;
			return pParent;
		}
	}
	bool CheckCondition( PNode& pParent, PNode& pCur)
	{
		if (pParent == nullptr)
			return false;
		while (pParent == nullptr && pParent != _pHead && pParent->_color == RED)
		{
			PNode GrandFather = pParent->_pParent;
			if (pParent == GrandFather->_pLeft)  //父节点是祖父节点的左孩子
			{
				PNode uncle = GrandFather->_pRight;
				if (uncle && uncle->_color == RED) //uncle的颜色为红色
				{
					pParent->_color = BLACK;
					uncle->_color = BLACK;
					GrandFather->_color = RED;

					pParent = GrandFather->_pParent;
				}
				else if (uncle == nullptr || uncle->_color == BLACK)
				{
					if (pCur == pParent->_pLeft)
					{
						pParent->_color = BLACK;
						GrandFather->_color = RED;
						RotateR(GrandFather);
					}
					else if (pCur == pParent->_pRight)
					{
						RotateL(pParent);
						pCur->_color = BLACK;
						GrandFather->_color = RED;
						RotateR(GrandFather);
					}
					break;
				}
			}
			else if (pParent == GrandFather->_pRight) //父节点是祖父节点的右孩子
			{
				PNode uncle = GrandFather->_pLeft;
				if (uncle && uncle->_color == RED)
				{
					pParent->_color = BLACK;
					uncle->_color = BLACK;
					GrandFather->_color = RED;
					pParent = GrandFather->_pParent;
				}
				else if (uncle == nullptr || uncle->_color == BLACK )
				{ 
					if (pCur == pParent->_pRight)
					{
						GrandFather->_color = BLACK;
						pParent->_color = BLACK;
						RotateL(GrandFather);
					}
					else if (pCur == pParent->_pLeft)
					{
						RotateR(pParent);
						GrandFather->_color = RED;
						pCur->_color = RED;
						RotateL(GrandFather);
					}
					break;
				}
			}
		}
		_pHead->_pParent->_color = BLACK;
		_pHead->_pLeft = LeftMost();
		_pHead->_pRight = RightMost();
		return true;
	}

private:
	void _InOrder(PNode pRoot)
	{
		if (pRoot != nullptr)
		{
			_InOrder(pRoot->_pLeft);
			cout << pRoot->_data << " ";
			_InOrder(pRoot->_pRight);
		}
	}
	PNode& GetRoot()
	{
		return _pHead->_pParent;
	}
	void RotateL(PNode& pParent)
	{
		PNode pSubR = pParent->_pRight;
		PNode pSubRL = pSubR->_pLeft;
		pParent->_pRight = pSubRL;
		if (pSubRL)
			pSubR->_pParent = pParent;
		pSubR->_pLeft = pParent;
		PNode pPParent = pParent->_pParent;
		pParent->_pParent = pSubR;
		pSubR->_pParent = pPParent;

		PNode& pRoot = GetRoot();
		if (pRoot == pParent)
		{
			pRoot = pSubR;
		}
		else
		{
			if (pParent == pPParent->_pLeft)
				pPParent->_pLeft = pSubR;
			else
				pPParent->_pRight = pSubR;
		}
	}
	void RotateR(PNode& pParent)
	{
		PNode pSubL = pParent->_pLeft;
		PNode pSubLR = pSubL->_pRight;

		pParent->_pLeft = pSubLR;
		if (pSubLR)
			pSubLR->_pParent = pParent;

		pSubL->_pRight = pParent;
		PNode pPParent = pParent->_pParent;
		pParent->_pParent = pSubL;
		pSubL->_pParent = pPParent;

		PNode& pRoot = GetRoot();
		if (pParent == pRoot)
			pRoot = pSubL;
		else
		{
			if (pParent == pPParent->_pLeft)
				pPParent->_pLeft = pSubL;
			else
				pPParent->_pRight = pSubL;
		}
	}
	PNode LeftMost()
	{
		PNode pRoot = GetRoot();
		if (nullptr == pRoot)
			return _pHead;

		PNode pCur = pRoot;
		while (pCur->_pLeft)
			pCur = pCur->_pLeft;
		return pCur;
	}

	PNode RightMost()
	{
		PNode pRoot = GetRoot();
		if (nullptr == pRoot)
			return _pHead;

		PNode pCur = pRoot;
		while (pCur->_pRight)
			pCur = pCur->_pRight;
		return pCur;
	}

	void _Destroy(PNode& pRoot)
	{
		if (pRoot)
		{
			_Destroy(pRoot->_pLeft);
			_Destroy(pRoot->_pRight);
			delete pRoot;
			pRoot = nullptr;
		}
	}
	
private:
	PNode _pHead;
};

void TestSet()
{
	RBTree<int> at;
	//int array[] = { 16, 3, 7, 11, 9, 26, 18, 14, 15 };
	//int array[] = { 4, 2, 6, 1, 3, 5, 15, 7, 16, 14 };
	int array[] = { 1,6,8,11,13,15,17,25,22,27 };
	for (int i = 0; i < sizeof(array) / sizeof(array[0]); i++)
		at.Insert(array[i]);
	at.PrintOrder();
}