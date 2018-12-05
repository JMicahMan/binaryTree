#pragma once

#include "Application.h"
#include "binaryTree.h"
#include "Font.h"






class binaryApp : public aie::Application {



public:

	

	bool startup() override;
	void shutdown() override;

	void update(float deltaTime) override;
	void draw() override;



protected:
	BinaryTree m_binaryTree;
    TreeNode* m_selectedNode;
	aie::Renderer2D*	m_2dRenderer;
	aie::Font*			g_systemFont;
	
};