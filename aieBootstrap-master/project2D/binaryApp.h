#pragma once
#pragma once

#include "Application.h"
#include "Renderer2D.h"
#include "binaryTree.h"
#include "treeNode.h"






class binaryApp : public aie::Application {



	BinaryTree m_binaryTree;
	TreeNode* m_selectedNode;

	binaryApp();
	virtual ~binaryApp();

	virtual bool startup();
	virtual void shutdown();

	virtual void update(float deltaTime);
	virtual void draw();




	aie::Renderer2D*	m_2dRenderer;
	aie::Texture*		m_texture;
	aie::Texture*		m_shipTexture;
	//aie::Font*			m_font;

	float m_cameraX, m_cameraY;
	float m_timer;
};