#pragma once
#include <iostream>
#include <stack>
#include <queue>
template <typename T>
class binaryTreeNode
{
public:
	T element;
	binaryTreeNode<T>* leftChild;
	binaryTreeNode<T>* rightChild;
	binaryTreeNode() { leftChild = NULL; rightChild = NULL; }
	binaryTreeNode(const T& val):element(val){ leftChild = NULL; rightChild = NULL; }
};

template <typename T>
class binaryTree 
{
private:
	
	binaryTreeNode<T> *mRoot;//树根

	int getSize(binaryTreeNode<T>*);
	int getHeight(binaryTreeNode<T>*);

	void preOrder(binaryTreeNode<T>*);
	void inOrder(binaryTreeNode<T>*);
	void postOrder(binaryTreeNode<T>*);
	void depthFirstSearch(binaryTreeNode<T>*);
	void breadthFirstSearch(binaryTreeNode<T>*);
	void destroy(binaryTreeNode<T>*&);
	binaryTreeNode<T>* Create(binaryTreeNode<T>*);//递归创建二叉树
	binaryTreeNode<T>* AddNode(const T& key, int direction, binaryTreeNode<T>*& root);

public:

	
	binaryTree(binaryTreeNode<T>*);
	~binaryTree() { destroy(); }

	void Create();
	void AddNode(const T& key, int direction);

	int getSize();
	int getHight();

	void preOrder();//前序遍历
	void inOrder();//中序遍历
	void postOrder();//后序遍历
	void depthFirstSearch();//深度优先遍历
	void breadthFirstSearch();//广度优先遍历

	void destroy();//删除二叉树
	
};

template <typename T>
binaryTree<T>::binaryTree(binaryTreeNode<T> *root):mRoot(root){}

/********************************************************************/
template <typename T>
binaryTreeNode<T>* binaryTree<T>::AddNode(const T& key, int direction, binaryTreeNode<T>*& root)
{
	if (direction == 0)//左孩子
	{
		if (root->leftChild == NULL)
		{
			root->leftChild = new binaryTreeNode<T>(key);
		}
		else
		{
			root->leftChild = AddNode(key, direction, root->leftChild);
		}
	}
	else
	{
		if (root->rightChild == NULL)
			root->rightChild = new binaryTreeNode<T>(key);
		else
			root->rightChild = AddNode(key, direction, root->rightChild);
	}
	return root;
}

template <typename T>
void binaryTree<T>::AddNode(const T& key, int direction)
{
	AddNode(key, direction, mRoot);
}
/********************************************************************/


/********************************************************************/
template <typename T>
void binaryTree<T>::Create()
{
	mRoot = Create(mRoot);
}

template <typename T>
binaryTreeNode<T>* binaryTree<T>::Create(binaryTreeNode<T>* root)
{
	binaryTreeNode<T>* temp = NULL;
	T val;

	std::cin >> val;

	if (val == -1)//标识当前子树为空，转向下一节点
		return NULL;
	else//递归创建左右子树
	{
		temp = new binaryTreeNode<T>;
		temp->element = val;
		temp->leftChild = Create(temp);
		temp->rightChild = Create(temp);
		return temp;
	}
}
/********************************************************************/

/********************************************************************/
/*
	二叉树的销毁操作：后序遍历删除

	1）不能使用该声明：void distroy(binaryTreeNode<T>* pNode);该声明会创建一个局部的临时对象来保存传递的指针
	虽然实参指针和局部指针都执行同一块堆空间，delete局部指针也会删除二叉树结构所占用的堆内存
	但是实参指针将出现无所指的状态，出现不可预料的错误
	因此传递的是指针的引用，这样才能将实参指针置空。

	2）使用递归方法释放节点
  */
template <typename T>
void binaryTree<T>::destroy(binaryTreeNode<T>* &pNode)
{
	if (pNode)
	{
		destroy(pNode->leftChild);
		destroy(pNode->rightChild);
		delete pNode;
		pNode = NULL;
	}
}

template <typename T>
void binaryTree<T>::destroy()
{
	destroy(mRoot);
}
/********************************************************************/

/********************************************************************/
/*
	获取当前节点的深度
	递归的方法首先要设置截止条件，在进行递归操作。
	0.约束条件：节点为空
	1.递归左子树,每次递归加1
	2.递归右子树，每次递归加1
	3.比较左右子树深度，更深的子树+1即为当前节点深度。
 */
template <typename T>
int binaryTree<T>::getHight()
{
	return getHeight(mRoot);
}

template <typename T>
int binaryTree<T>::getHeight(binaryTreeNode<T>* node)
{
	if (node == NULL)
		return 0;
	else
	{
		int deL = getHeight(node->leftChild);
		int deR = getHeight(node->rightChild);
		return deL > deR ? deL+1 : deR+1;
	}
}
/********************************************************************/

/********************************************************************/
/*
	前序遍历：
	1.由于是递归实现，所以要设置截止条件：当前节点为空
	2.先访问父节点，再访问左节点，最后访问右孩子
	根左右
*/

template <typename T>
void binaryTree<T>::preOrder()
{
	std::cout << "前序遍历: ";
	preOrder(mRoot);
	std::cout << std::endl;
}

template <typename T>
void binaryTree<T>::preOrder(binaryTreeNode<T>* node)
{
	if (node == NULL)
		return;
	else
	{
		std::cout << node->element << ' ';
		preOrder(node->leftChild);
		preOrder(node->rightChild);
	}
}

/********************************************************************/
/*
中序遍历
左根右
*/

template <typename T>
void binaryTree<T>::inOrder()
{
	std::cout << "中序遍历: ";
	inOrder(mRoot);
	std::cout << std::endl;
}

template <typename T>
void binaryTree<T>::inOrder(binaryTreeNode<T>* node)
{
	if (node == NULL)
		return;
	else
	{
		inOrder(node->leftChild);
		std::cout << node->element << ' ';
		inOrder(node->rightChild);
	}
}
/********************************************************************/

/********************************************************************/
/*
	后序遍历
	左右根
*/
template <typename T>
void binaryTree<T>::postOrder()
{
	std::cout << "后序遍历: ";
	postOrder(mRoot);
	std::cout << std::endl;
}

template <typename T>
void binaryTree<T>::postOrder(binaryTreeNode<T>* node)
{
	if (node == NULL)
		return;
	else
	{
		postOrder(node->leftChild);
		postOrder(node->rightChild);
		std::cout << node->element << ' ';
	}
}
/********************************************************************/

/********************************************************************/
/*深度优先遍历*/
template <typename T>
void binaryTree<T>::depthFirstSearch(binaryTreeNode<T>* node)
{
	std::stack<binaryTreeNode<T>*> nodeStack;
	nodeStack.push(node);
	binaryTreeNode<T> *temp;
	std::cout << "深度优先遍历：";
	while (!nodeStack.empty())
	{
		temp = nodeStack.top();
		std::cout << temp->element << ' ';
		nodeStack.pop();
		if (temp->rightChild)//先将右子树压栈，保证栈顶是左子树
			nodeStack.push(temp->rightChild);
		if (temp->leftChild)
			nodeStack.push(temp->leftChild);
	}
	std::cout << std::endl;
}

template <typename T>
void binaryTree<T>::depthFirstSearch()
{
	depthFirstSearch(mRoot);
}
/********************************************************************/
template <typename T>
void binaryTree<T>::breadthFirstSearch(binaryTreeNode<T>* node)
{
	std::queue<binaryTreeNode<T>*> nodeQueue;
	nodeQueue.push(node);
	binaryTreeNode<T>* temp;
	std::cout << "广度优先遍历：";
	while (!nodeQueue.empty())
	{
		temp = nodeQueue.front();
		nodeQueue.pop();
		std::cout << temp->element << ' ';
		//左孩子先入队，右孩子后入队，在整体上保持从左向右入队
		if (temp->leftChild)
			nodeQueue.push(temp->leftChild);
		if (temp->rightChild)
			nodeQueue.push(temp->rightChild);
	}
	std::cout << std::endl;
}

template <typename T>
void binaryTree<T>::breadthFirstSearch()
{
	breadthFirstSearch(mRoot);
}

/********************************************************************/
/*
	获得总的节点数
*/
template <typename T> 
int binaryTree<T>::getSize()
{
	return getSize(mRoot);
}

template <typename T>
int binaryTree<T>::getSize(binaryTreeNode<T>* node)
{
	if (node == NULL)
		return 0;
	
	int i = 0;
	i = 1 + getSize(node->leftChild) + getSize(node->rightChild);
	return i;
}

