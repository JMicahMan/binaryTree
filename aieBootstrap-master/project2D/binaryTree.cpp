
#include "binaryApp.h"




BinaryTree::BinaryTree()
{
	m_pRoot = nullptr;
}

BinaryTree::~BinaryTree()
{
}

bool BinaryTree::isEmpty() const
{
	if (m_pRoot == nullptr)
	{
		return true;
	}
	return false;
}

void BinaryTree::insert(int a_nValue) //works
{
	TreeNode* temp;

	if (isEmpty() == true)
	{
		m_pRoot = new TreeNode(a_nValue);
	}
	else if (isEmpty() == false)
	{
		TreeNode* current;
		current = m_pRoot;
		TreeNode* parent;
		parent = current;
		while (current != nullptr)
		{
			if (current->getData() > a_nValue)
			{
				parent = current;
				current = current->getLeft();
				
			}
			else if (current->getData() < a_nValue)
			{
				parent = current;
				current = current->getRight();
			}
			else
			{
				return;
			}
		}
		if (parent->getData() > a_nValue)
		{
			temp = new TreeNode(a_nValue);
			parent->setLeft(temp);
		}
		else
		{
			temp = new TreeNode(a_nValue);
			parent->setRight(temp);
		}
	}
}

void BinaryTree::remove(int a_nValue)
{
	//find the value in the tree, obtaining a pointer to the node and its parent
	/*

			remove(int value)
		find the value in the tree, obtaining a pointer to the node and its parent
		If the current node has a right branch, then
			find the minimum value in the right branch by iterating down the left branch of the
				current node’s right child until there are no more left branch nodes
			copy the value from this minimum node to the current node
			find the minimum node’s parent node (the parent of the node you are deleting)
				if you are deleting the parent’s left node
					set this left child of the parent to the right child of the minimum
					node
				if you are deleting the parent’s right node
					set the right child of the parent to the minimum node’s right child

		If the current node has no right branch
			if we are deleting the parent’s left child, set the left child of the parent to the left
			child of the current node
			If we are deleting the parent’s right child, set the right child of the parent to the left
			child of the current node
			If we are deleting the root, the root becomes the left child of the current node

	*/
	TreeNode * current;
	current = m_pRoot;
	TreeNode * parent;
	parent = m_pRoot;
	TreeNode ** ppOutNode;
	ppOutNode = &current;
	TreeNode ** ppOutParent;
	ppOutParent = &parent;

	
	findNode( a_nValue, ppOutNode, ppOutParent); //Works needs to be broken

	if (findNode(a_nValue, ppOutNode, ppOutParent) == true)
	{
		TreeNode *minimum = *ppOutNode;
		TreeNode *minimumParent = *ppOutParent;
//		TreeNode *temp;
		
		if (current->hasRight())
		{
			minimumParent = minimum;
			minimum = minimum->getRight();
			if (minimum->hasLeft())
			{
				while (minimum->hasLeft())
				{
					minimumParent = minimum;
					minimum = minimum->getLeft();

					//left off here
				}
				current->setData(minimum->getData());
			}

			if (minimumParent->getLeft() == minimum)
			{
				if (minimum->hasRight())
				{
					minimumParent->setLeft(minimum->getRight());
					delete minimum;
					return;
				}
			}
			else if (minimumParent->getRight() == minimum)
			{
				if (minimum->hasRight())
				{
					minimumParent->setRight(minimum->getRight());
					delete minimum;
					return;
				}
			}
		}

		else
		{
			if (parent->getLeft() == current)
			{
				if (current->hasLeft())
				{
					parent->setLeft(current->getLeft());
					delete current;
					return;
				}
			}

			if (parent->getRight() == current)
			{
				if (current->hasLeft())
				{
					parent->setRight(current->getLeft());
					delete current;
					return;
				}
			}

			if (m_pRoot == current)
			{
				if (current->hasLeft())
				{
					m_pRoot = (current->getLeft());
					delete current;
					return;
				}
			}
		}

	
	}

	if (current->hasLeft() == false && current->hasRight() == false)
	{
		delete current;
		current = nullptr;
		return;
	}

	if (current->hasRight() == true)
	{
		current = current->getRight();
		while (current->hasLeft() == true)
		{
			current = current->getLeft();
		}
		TreeNode* curntptr = *ppOutNode;
		
		curntptr->setData(current->getData());
	}

	if (current->hasRight() == true)
	{
		parent->setRight(current->getRight());
		delete current; 
		return;
	}

	if (current->hasLeft() == true)
	{
		parent->setLeft(current->getLeft());
		delete current;
		return;
	}

}

TreeNode * BinaryTree::find(int a_nValue)
{
	TreeNode *current = m_pRoot;
	while (current->hasLeft() || current->hasRight())
	{

		if (current->getData() == a_nValue)
		{
			return current;
		}
		else if (current->getData() > a_nValue)
		{
			current = current->getLeft();
		}
		else if (current->getData() < a_nValue)
		{
			current = current->getRight();
		}
	}
}

void BinaryTree::draw(aie::Renderer2D* renderer, aie::Font* g_systemFont, TreeNode* selected)
{
	draw(renderer, m_pRoot, 640, 680, 640,g_systemFont, selected);
}












bool BinaryTree::findNode(int a_nSearchValue, TreeNode ** ppOutNode, TreeNode ** ppOutParent)
{
	//we are passing in a pointer to a pointer so that when we change it, the change persists after we exit the function
	
	// set the current node to the root
	//		while the current node is not null
	//				if the search value equals the current node's value
	//						return the current node and its parent
	//				otherwise
	//						if the search value is less than the current node
	//								set the current node to it's left child
	//						otherwise
	//								set the current node to it's right child
	//		end while

	// If the loop exits, then a match was NOT found, so return false

	while (*ppOutNode != nullptr)
	{
		 
		if (a_nSearchValue == (*ppOutNode)->getData())
		{
			return true;
		}

		else if (a_nSearchValue < (*ppOutNode)->getData())
		{
			*ppOutParent = (*ppOutNode);
			*ppOutNode = (*ppOutNode)->getLeft();

	
		}

		else if (a_nSearchValue >(*ppOutNode)->getData())
		{
			*ppOutParent = (*ppOutNode);
			*ppOutNode = (*ppOutNode)->getRight();

		}

	}
	return false;
}







void BinaryTree::draw(aie::Renderer2D* renderer, TreeNode* pNode, int x, int y,
	int horizontalSpacing, aie::Font* g_systemFont, TreeNode* selected)
{
	horizontalSpacing /= 2;

	if (pNode) {
		if (pNode->hasLeft())
		{
			renderer->setRenderColour(1, 0, 0);
			renderer->drawLine(x, y, x - horizontalSpacing, y - 80);
			draw(renderer, pNode->getLeft(), x - horizontalSpacing,
				y - 80, horizontalSpacing,g_systemFont, selected);
		}

		if (pNode->hasRight())
		{
			renderer->setRenderColour(1, 0, 0);
			renderer->drawLine(x, y, x + horizontalSpacing, y - 80);
			draw(renderer, pNode->getRight(), x + horizontalSpacing,
				y - 80, horizontalSpacing, g_systemFont, selected);
		}
		pNode->draw(renderer, x, y, (selected == pNode));
	}
}
