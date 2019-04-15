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
	
	binaryTreeNode<T> *mRoot;//����

	int getSize(binaryTreeNode<T>*);
	int getHeight(binaryTreeNode<T>*);

	void preOrder(binaryTreeNode<T>*);
	void inOrder(binaryTreeNode<T>*);
	void postOrder(binaryTreeNode<T>*);
	void depthFirstSearch(binaryTreeNode<T>*);
	void breadthFirstSearch(binaryTreeNode<T>*);
	void destroy(binaryTreeNode<T>*&);
	binaryTreeNode<T>* Create(binaryTreeNode<T>*);//�ݹ鴴��������
	binaryTreeNode<T>* AddNode(const T& key, int direction, binaryTreeNode<T>*& root);

public:

	
	binaryTree(binaryTreeNode<T>*);
	~binaryTree() { destroy(); }

	void Create();
	void AddNode(const T& key, int direction);

	int getSize();
	int getHight();

	void preOrder();//ǰ�����
	void inOrder();//�������
	void postOrder();//�������
	void depthFirstSearch();//������ȱ���
	void breadthFirstSearch();//������ȱ���

	void destroy();//ɾ��������
	
};

template <typename T>
binaryTree<T>::binaryTree(binaryTreeNode<T> *root):mRoot(root){}

/********************************************************************/
template <typename T>
binaryTreeNode<T>* binaryTree<T>::AddNode(const T& key, int direction, binaryTreeNode<T>*& root)
{
	if (direction == 0)//����
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

	if (val == -1)//��ʶ��ǰ����Ϊ�գ�ת����һ�ڵ�
		return NULL;
	else//�ݹ鴴����������
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
	�����������ٲ������������ɾ��

	1������ʹ�ø�������void distroy(binaryTreeNode<T>* pNode);�������ᴴ��һ���ֲ�����ʱ���������洫�ݵ�ָ��
	��Ȼʵ��ָ��;ֲ�ָ�붼ִ��ͬһ��ѿռ䣬delete�ֲ�ָ��Ҳ��ɾ���������ṹ��ռ�õĶ��ڴ�
	����ʵ��ָ�뽫��������ָ��״̬�����ֲ���Ԥ�ϵĴ���
	��˴��ݵ���ָ������ã��������ܽ�ʵ��ָ���ÿա�

	2��ʹ�õݹ鷽���ͷŽڵ�
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
	��ȡ��ǰ�ڵ�����
	�ݹ�ķ�������Ҫ���ý�ֹ�������ڽ��еݹ������
	0.Լ���������ڵ�Ϊ��
	1.�ݹ�������,ÿ�εݹ��1
	2.�ݹ���������ÿ�εݹ��1
	3.�Ƚ�����������ȣ����������+1��Ϊ��ǰ�ڵ���ȡ�
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
	ǰ�������
	1.�����ǵݹ�ʵ�֣�����Ҫ���ý�ֹ��������ǰ�ڵ�Ϊ��
	2.�ȷ��ʸ��ڵ㣬�ٷ�����ڵ㣬�������Һ���
	������
*/

template <typename T>
void binaryTree<T>::preOrder()
{
	std::cout << "ǰ�����: ";
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
�������
�����
*/

template <typename T>
void binaryTree<T>::inOrder()
{
	std::cout << "�������: ";
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
	�������
	���Ҹ�
*/
template <typename T>
void binaryTree<T>::postOrder()
{
	std::cout << "�������: ";
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
/*������ȱ���*/
template <typename T>
void binaryTree<T>::depthFirstSearch(binaryTreeNode<T>* node)
{
	std::stack<binaryTreeNode<T>*> nodeStack;
	nodeStack.push(node);
	binaryTreeNode<T> *temp;
	std::cout << "������ȱ�����";
	while (!nodeStack.empty())
	{
		temp = nodeStack.top();
		std::cout << temp->element << ' ';
		nodeStack.pop();
		if (temp->rightChild)//�Ƚ�������ѹջ����֤ջ����������
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
	std::cout << "������ȱ�����";
	while (!nodeQueue.empty())
	{
		temp = nodeQueue.front();
		nodeQueue.pop();
		std::cout << temp->element << ' ';
		//��������ӣ��Һ��Ӻ���ӣ��������ϱ��ִ����������
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
	����ܵĽڵ���
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

