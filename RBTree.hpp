#if 0
#pragma once
#include<iostream>
using namespace std;

enum Color{ RED,BLACK };

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
#if 0
	bool Insert(const V& data)
	{
		PNode& pRoot = GetRoot();
		if (nullptr == pRoot)
		{
			pRoot = new Node(data, BLACK);
			pRoot->_pParent = _pHead;
		}
		else
		{
			//按照二叉搜索树性质插入新节点
			PNode pCur = pRoot;
			PNode pParent = nullptr;
			while (pCur)
			{
				pParent = pCur;
				if (data < pCur->_data)
					pCur = pCur->_pLeft;
				else if (data > pCur->_data)
					pCur = pCur->_pRight;
				else
					return false;
			}

			//插入新节点
			pCur = new Node(data);
			if (data < pParent->_data)
				pParent->_pLeft = pCur;
			else
				pParent->_pRight = pCur;
			pCur->_pParent = pParent;

			//更新节点颜色
			while (pParent != _pHead && RED == pParent->_color)
			{
				PNode grandFather = pParent->_pParent;
				if (pParent == grandFather->_pLeft)
				{
					PNode uncle = grandFather->_pRight;
					if (uncle && RED == uncle->_color) //叔叔节点存在且为红
					{
						pParent->_color = BLACK;
						uncle->_color = BLACK;
						grandFather->_color = RED;
						pCur = grandFather;
						pParent = pCur->_pParent;
					}
					else
					{
						//情况3
						if (pCur == pParent->_pRight)
						{
							RotateL(pParent);
							swap(pCur, pParent);
						}
						//情况2
						pParent->_color = BLACK;
						grandFather->_color = RED;
						RotateR(grandFather);
					}
				}
				else
				{
					PNode uncle = grandFather->_pLeft;
					if (uncle && uncle->_color == RED)
					{
						pParent->_color = BLACK;
						uncle->_color = BLACK;
						grandFather->_color = RED;
						pCur = grandFather;
						pParent = pCur->_pParent;
					}
					else
					{
						if (pCur == pParent->_pRight)
						{
							RotateR(pParent);
							swap(pCur, pParent);
						}
						pParent->_color = BLACK;
						grandFather->_color = RED;
						RotateL(grandFather);
					}
				}
			}
		}
		pRoot->_color = BLACK;
		_pHead->_pLeft = LeftMost();
		_pHead->_pRight = RightMost();
		return true;
	}
#endif
	bool Insert(const V& data)
	{
		PNode& pRoot = GetRoot();
		if (nullptr == pRoot)
		{
			pRoot = new Node(data, BLACK);
			pRoot->_pParent = _pHead;
		}
		else
		{
			//按照二叉搜索树性质插入新节点
			PNode pCur = pRoot;
			PNode pParent = nullptr;
			while (pCur)
			{
				pParent = pCur;
				if (data < pCur->_data)
					pCur = pCur->_pLeft;
				else if (data > pCur->_data)
					pCur = pCur->_pRight;
				else
					return false;
			}

			//插入新节点
			pCur = new Node(data);
			if (data < pParent->_data)
				pParent->_pLeft = pCur;
			else
				pParent->_pRight = pCur;
			pCur->_pParent = pParent;

			while (pParent && pParent->_color == RED)
			{
				PNode grandfather = pParent->_pParent;
				if (pParent == grandfather->_pLeft)
				{
					PNode uncle = grandfather->_pRight;
					if (uncle && uncle->_color == RED)
					{   //第一种情况  变色
						grandfather->_color = RED;
						pParent->_color = BLACK;
						uncle->_color = BLACK;

						pCur = grandfather;
						pParent = grandfather->_pParent;
					}
					else if ((uncle && uncle->_color == BLACK) || uncle == NULL)
					{
						if (pCur == pParent->_pLeft)
						{//第二种情况 右单旋        cur必然有黑色孩子
							pParent->_color = BLACK;
							grandfather->_color = RED;
							RotateR(grandfather);
						}
						else
						{//第三种情况 左右双旋
							RotateL(pParent);
							pParent->_color = BLACK;
							grandfather->_color = RED;
							RotateR(grandfather);
						}
						break;
					}
				}
				else if (pParent == grandfather->_pRight)
				{
					PNode uncle = grandfather->_pLeft;
					if (uncle&&uncle->_color == RED)
					{//第一种情况 变色
						grandfather->_color = RED;
						pParent->_color = BLACK;
						uncle->_color = BLACK;

						pCur = grandfather;
						pParent = pCur->_pParent;
					}
					else if ((uncle && uncle->_color == BLACK) || uncle == NULL)
					{//第二种情况 左单旋 cur必然有黑孩子
						if (pCur == pParent->_pRight)
						{
							pParent->_color = BLACK;
							grandfather->_color = RED;
							RotateL(grandfather);
						}
						else if (pCur == pParent->_pLeft)
						{//第三种情况 右左双旋
							RotateR(pParent);
							pParent->_color = BLACK;
							grandfather->_color = RED;
							RotateL(grandfather);
						}
						break;
					}
				}
			}
		}
		pRoot->_color = BLACK;
		_pHead->_pLeft = LeftMost();
		_pHead->_pRight = RightMost();
		return true;
	}


	void InOrder()
	{
		_InOrder(_pHead->_pParent);
		cout << endl;
	}

	bool IsRBTree()
	{
		PNode pRoot = GetRoot();
		if (nullptr == pRoot)
			return true;
		if (RED == pRoot->_color)
		{
			cout << "违反性质2：根节点的颜色为红色" << endl;
			return false;
		}

		size_t blackCount = 0;
		PNode pCur = pRoot;
		while (pCur)
		{
			if (BLACK == pCur->_color)
				blackCount++;
			pCur = pCur->_pLeft;
		}
		size_t pathBlack = 0;
		return _IsRBTree(pRoot, blackCount, pathBlack);
	}

private:
	PNode& GetRoot()
	{
		return _pHead->_pParent;
	}
	void _InOrder(PNode pRoot)
	{
		if (pRoot == nullptr)
			return;
		_InOrder(pRoot->_pLeft);
		cout << pRoot->_data << " ";
		_InOrder(pRoot->_pRight);
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

	bool _IsRBTree(PNode pRoot, size_t blackCount, size_t pathBlack)
	{
		if (nullptr == pRoot)
			return true;
		if (BLACK == pRoot->_color)
			pathBlack++;

		PNode pParent = pRoot->_pParent;
		if (pParent && pRoot->_color == RED && RED == pParent->_color)
		{
			cout << "违反性质3：有连在一起的红色节点" << endl;
			return false;
		}
		if (pRoot->_pLeft == nullptr && nullptr == pRoot->_pRight)
		{
			if (blackCount != pathBlack)
			{
				cout << "违反性质4：路径中黑色节点的个数不相同" << endl;
				return false;
			}
		}
		return _IsRBTree(pRoot->_pLeft, blackCount, pathBlack) && _IsRBTree(pRoot->_pRight, blackCount, pathBlack);
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

	void RotateL(PNode pParent)
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

	void RotateR(PNode pParent)
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

private:
	PNode _pHead;

};

void TestRBTree()
{
		RBTree<int> at;
		//int array[] = { 16, 3, 7, 11, 9, 26, 18, 14, 15 };
		//int array[] = { 4, 2, 6, 1, 3, 5, 15, 7, 16, 14 };
		int array[] = { 1,6,8,11,13,15,17,25,22,27 };
		for (int i = 0; i < sizeof(array) / sizeof(array[0]); i++)
			at.Insert(array[i]);
		at.InOrder();
		at.IsRBTree();
}
#endif

//template<class K, class V>
//bool RBTree<K, V>::Insert(const K& key, const V& value)
//{
//	if (_root == NULL)
//	{
//		_root = new RBTreeNode<K, V>(key, value);
//		_root->_color = BLACK;
//		return true;
//	}
//	//  找位置
//	RBTreeNode<K, V>* cur = _root;
//	RBTreeNode<K, V>* parent = NULL;
//	while (cur)
//	{
//		if (cur->_key > key)
//		{
//			parent = cur;
//			cur = cur->_left;
//		}
//		else if (cur->_key < key)
//		{
//			parent = cur;
//			cur = cur->_right;
//		}
//		else
//		{
//			return false;
//		}
//	}
//	//插入
//	cur = new RBTreeNode<K, V>(key, value);
//	cur->_parent = parent;
//	if (parent->_key > key)
//		parent->_left = cur;
//	else if (parent->_key < key)
//		parent->_right = cur;
//
//	//检查颜色分配是否满足要求
//	while (parent&&parent->_color == RED)
//	{
//		RBTreeNode<K, V>* grandfather = parent->_parent;
//		if (parent == grandfather->_left)
//		{
//			RBTreeNode<K, V>* uncle = grandfather->_right;
//			if (uncle&&uncle->_color == RED)
//			{   //第一种情况  变色
//				grandfather->_color = RED;
//				parent->_color = BLACK;
//				uncle->_color = BLACK;
//
//				cur = grandfather;
//				parent = grandfather->_parent;
//			}
//			else if ((uncle&&uncle->_color == BLACK) || uncle == NULL)
//			{
//				if (cur == parent->_left)
//				{//第二种情况 右单旋        cur必然有黑色孩子
//					parent->_color = BLACK;
//					grandfather->_color = RED;
//					RotateR(grandfather);
//				}
//				else
//				{//第三种情况 左右双旋
//					RotateL(parent);
//					parent->_color = BLACK;
//					grandfather->_color = RED;
//					RotateR(grandfather);
//				}
//				break;
//			}
//		}
//		else if (parent == grandfather->_right)
//		{
//			RBTreeNode<K, V>* uncle = grandfather->_left;
//			if (uncle&&uncle->_color == RED)
//			{//第一种情况 变色
//				grandfather->_color = RED;
//				parent->_color = BLACK;
//				uncle->_color = BLACK;
//
//				cur = grandfather;
//				parent = cur->_parent;
//			}
//			else if ((uncle&&uncle->_color == BLACK) || uncle == NULL)
//			{//第二种情况 左单旋 cur必然有黑孩子
//				if (cur == parent->_right)
//				{
//					parent->_color = BLACK;
//					grandfather->_color = RED;
//					RotateL(grandfather);
//				}
//				else if (cur == parent->_left)
//				{//第三种情况 右左双旋
//					RotateR(parent);
//					parent->_color = BLACK;
//					grandfather->_color = RED;
//					RotateL(grandfather);
//				}
//				break;
//			}
//		}
//	}
//	_root->_color = BLACK;
//	return true;
//}