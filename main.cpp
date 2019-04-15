#include "tree.h"

int main()
{
	binaryTreeNode<int> *root = NULL;
	binaryTree<int> tr(root);
	tr.Create();
	tr.preOrder();
	tr.inOrder();
	tr.postOrder();
	tr.getHight();
	tr.getSize();
	tr.breadthFirstSearch();
	return 0;
}