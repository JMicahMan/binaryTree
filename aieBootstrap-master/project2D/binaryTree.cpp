#include "binaryTree.h"


BinaryTree::BinaryTree()
{
	m_pRoot = nullptr;
}

bool BinaryTree::isEmpty() const
{
	if (m_pRoot == nullptr)
	{
		return true;
	}
	return false;
}

void BinaryTree::insert(int a_nValue)
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
				current = current->getRight();
				
			}
			else if (current->getData() < a_nValue)
			{
				parent = current;
				current = current->getLeft();
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
	TreeNode** ppCurrent;
	TreeNode** ppParent;
	findNode(a_nValue, ppCurrent, ppParent);

	TreeNode* current =  *ppCurrent;
	TreeNode* parent = *ppParent;

	if (current->hasLeft() == false && current->hasRight() == false)
	{
		delete current;
	}

	if (current->hasRight() == true)
	{
		current = current->getRight();
		while (current->hasLeft() == true)
		{
			current = current->getLeft();
		}
		TreeNode* curntptr = *ppCurrent;
		
		curntptr->setData(current->getData());
	}

	if (current->hasRight() == true)
	{
		parent->setRight(current->getRight);
		delete current;
	}

	if (current->hasLeft() == true)
	{
		parent->setLeft(current->getLeft);
		delete current;
	}
}

void BinaryTree::draw(aie::Renderer2D* renderer, TreeNode* selected)
{
	draw(renderer, m_pRoot, 640, 680, 640, selected);
}

bool BinaryTree::findNode(int a_nSearchValue, TreeNode ** ppOutNode, TreeNode ** ppOutParent)
{
	TreeNode* current = m_pRoot;
	TreeNode* parent = current;

	while (current != nullptr)
	{
		parent = current;
		if (a_nSearchValue == current->getData())
		{
			return true;
		}

		else if (a_nSearchValue < current->getData())
		{
			parent = current;
			current = current->getLeft();

			ppOutNode = &current;
			ppOutParent = &parent;
		}

		else if (a_nSearchValue > current->getData())
		{
			parent = current;
			current = current->getRight();

			ppOutNode = &current;
			ppOutParent = &parent;
		}

	}
	return false;
}

void BinaryTree::draw(aie::Renderer2D* renderer, TreeNode* pNode, int x, int y,
	int horizontalSpacing, TreeNode* selected)
{
	horizontalSpacing /= 2;

	if (pNode) {
		if (pNode->hasLeft()) {
			renderer->setRenderColour(1, 0, 0);
			renderer->drawLine(x, y, x + horizontalSpacing, y - 80);
			draw(renderer, pNode->getLeft(), x - horizontalSpacing,
				y - 80, horizontalSpacing, selected);
		}

		pNode->draw(renderer, x, y, (selected == pNode));
	}
}
