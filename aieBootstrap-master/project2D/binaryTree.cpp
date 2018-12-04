
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
	
	TreeNode * current;
	current = m_pRoot;
	TreeNode * parent;
	parent = m_pRoot;
	TreeNode ** ppOutNode;
	ppOutNode = &current;
	TreeNode ** ppOutParent;
	ppOutParent = &parent;

	

	if (findNode(a_nValue, ppOutNode, ppOutParent) == true)
	{
		TreeNode *minimum = *ppOutNode;
		TreeNode *minimumParent = *ppOutParent;
		
		if (current->hasRight())
		{
			if (minimum->hasRight())
			{
				minimumParent = minimum;
				minimum = minimum->getRight();
			}
			while (minimum->hasLeft())
			{
				minimumParent = minimum;
				minimum = minimum->getLeft();

			}
			current->setData(minimum->getData());
			if (minimumParent->getLeft() == minimum)
			{
					minimumParent->setLeft(minimum->getRight());
			}
			else if (minimumParent->getRight() == minimum)
			{
				{
					minimumParent->setRight(minimum->getRight());
				}
			}
			delete minimum;
		}

		else
		{
			if (parent->getLeft() == current)
			{
					parent->setLeft(current->getLeft());
			}

			else if (parent->getRight() == current)
			{
				
				{
					parent->setRight(current->getLeft());
				}
			}

			else if (m_pRoot == current)
			{
				
					m_pRoot = (current->getLeft());
			}
			delete current;
			current = nullptr;
		}

	
	}



}

TreeNode * BinaryTree::find(int a_nValue)
{
	TreeNode *current = m_pRoot;
	while (current != nullptr)
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


	while (*ppOutNode != nullptr)
	{
		 
		if (a_nSearchValue == (*ppOutNode)->getData()) //checks to see if the node is the node we are looking for
		{
			return true;
		}

		else if (a_nSearchValue < (*ppOutNode)->getData()) // checks to see if tge node is greater than what we're looking for and sends us down the left branch if true
		{
			if ((*ppOutNode)->hasLeft())
			{
				*ppOutParent = (*ppOutNode);
				*ppOutNode = (*ppOutNode)->getLeft();
			}
		}

		else if (a_nSearchValue >(*ppOutNode)->getData()) // checks to see if tge node is less than what we're looking for and sends us down the right branch if true
		{
			if ((*ppOutNode)->hasRight())
			{
				*ppOutParent = (*ppOutNode);
				*ppOutNode = (*ppOutNode)->getRight();
			}

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
