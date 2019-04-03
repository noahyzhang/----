#if 0
#pragma once

template<class T>
struct AVLTreeNode
{
	AVLTreeNode(const T& data)
		: _pLeft(nullptr)
		, _pRight(nullptr)
		,_pParent(nullptr)
		, _data(data)
		, _bf(0)
	{}
	AVLTreeNode<T>* _pLeft;
	AVLTreeNode<T>* _pRight;
	AVLTreeNode<T>* _pParent;
	T _data;
	int _bf;
};

template<class T>
class AVLTree {
	typedef AVLTreeNode<T> Node;
	typedef Node* PNode;
public:
	AVLTree()
		: _pRoot(nullptr)
	{ }

	bool Insert(const T& data)
	{
		if (nullptr == _pRoot)
		{
			_pRoot = new Node(data);
			return true;
		}
		PNode pCur = _pRoot;
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

		pCur = new Node(data);
		if (data < pParent->_data)
			pParent->_pLeft = pCur;
		else
			pParent->_pRight = pCur;

		pCur->_pParent = pParent;

		//更新平衡因子
		while (pParent)
		{
			if (pCur == pParent->_pLeft)
				pParent->_bf--;
			else
				pParent->_bf++;

			if (0 == pParent->_bf)
				break;
			else if (-1 == pParent->_bf || 1 == pParent->_bf)
			{
				pCur = pParent;
				pParent = pCur->_pParent;
			}
			else //此时说明平衡因子 >1 了，需要左右旋了
			{
				if (pParent->_bf == 2)
				{
					if (pParent->_pRight->_bf == 1)
						_RotateL(pParent);
					else if (pParent->_pRight->_bf == -1)
						_RotateRL(pParent);
				}
				else if (pParent->_bf == -2)
				{
					if (pParent->_pLeft->_bf == -1)
						_RotateR(pParent);
					else if (pParent->_pLeft->_bf == 1)
						_RotateLR(pParent);
				}
				break;
			}
		}
		return true;
	}
	bool IsBalanceTree()
	{
		return _IsBalanceTree(this->_pRoot);
	}

private:
	bool _IsBalanceTree(PNode pRoot)
	{
		if (pRoot == nullptr)
			return true;
		int LeftHeight = _Height(pRoot->_pLeft);
		int RightHeight = _Height(pRoot->_pRight);
		int diff = RightHeight - LeftHeight;

		if ((diff != pRoot->_bf) || (diff > 1) || (diff < -1))
			return false;
		return _IsBalanceTree(pRoot->_pLeft) && _IsBalanceTree(pRoot->_pRight);
	}

	int _Height(PNode pRoot)
	{
		if (pRoot == nullptr)
			return 0;
		int HeightL = _Height(pRoot->_pLeft);
		int HeightR = _Height(pRoot->_pRight);

		return (HeightL > HeightR) ? (HeightL + 1) : (HeightR + 1);
	}

	void _RotateR(PNode pParent)
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

		if (pPParent == nullptr)
		{
			_pRoot = pSubL;
			pSubL->_pParent = nullptr;
		}
		else
		{
			if (pPParent->_pLeft == pParent)
				pPParent->_pLeft = pSubL;
			else
				pPParent->_pRight = pSubL;
		}

		pParent->_bf = pSubL->_bf = 0;
	}

	void _RotateL(PNode pParent)
	{
		PNode pSubR = pParent->_pRight;
		PNode pSubRL = pSubR->_pLeft;

		pParent->_pRight = pSubRL;
		if (pSubRL)
			pSubRL->_pParent = pParent;

		pSubR->_pLeft = pParent;

		PNode pPParent = pParent->_pParent;

		pParent->_pParent = pSubR;
		pSubR->_pParent = pPParent;

		if (pPParent == nullptr)
		{
			_pRoot = pSubR;
			pSubR->_pParent = nullptr;
		}
		else
		{
			if (pPParent->_pLeft == pParent)
				pPParent->_pLeft = pSubR;
			else
				pPParent->_pRight = pSubR;
		}
		
		pSubR->_bf = pParent->_bf = 0;
	}
	void _RotateLR(PNode pParent)
	{
		PNode pSubL = pParent->_pLeft;
		PNode pSubLR = pSubL->_pRight;

		int bf = pSubLR->_bf;
		_RotateL(pParent->_pLeft);
		_RotateR(pParent);

		if (bf == 1)
			pSubL->_bf = -1;
		else if (bf == -1)
			pParent->_bf = 1;
	}
	void _RotateRL(PNode pParent)
	{
		PNode pSubR = pParent->_pRight;
		PNode pSubRL = pSubR->_pLeft;

		int bf = pSubRL->_bf;
		_RotateR(pParent->_pRight);
		_RotateL(pParent);
		if (bf == 1)
			pParent->_bf = -1;
		else if (bf == -1)
			pSubR->_bf = 1;
	}

private:
	PNode _pRoot;
};

void TestAVLTree()
{
	AVLTree<int> at;
	//int array[] = { 16, 3, 7, 11, 9, 26, 18, 14, 15 };
	int array[] = { 4, 2, 6, 1, 3, 5, 15, 7, 16, 14 };
	for (int i = 0; i < sizeof(array) / sizeof(array[0]); i++)
		at.Insert(array[i]);
	bool check = at.IsBalanceTree();
}
#endif