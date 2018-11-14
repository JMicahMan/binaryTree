#include "binaryApp.h"




aie:Font * g_systemFont = nullptr;

bool binaryApp::startup()
{
	m_2dRenderer = new aie::Renderer2D();
	g_systemFont = new aie::Font("./font/consolas.ttf", 32);
	return true;
}

void binaryApp::update(float deltaTime)
{
	aie::Input* input = aie::Input::getInstance();

	static int value = 0;
	ImGui::Input("Value, &value");

	if (ImGui::Button("Insert", ImVec2(50, 0)))
	{
		m_binaryTree.insert(value);
		m_selectedNode = m_binaryTree.find(value);
	}

	if (ImGui::Button("Remove", ImVec2(50, 0)))	{		m_binaryTree.remove(value);	}
	if (ImGui::Button("Find", ImVec2(50, 0)))
	{
		m_selectedNode = m_binaryTree.find(value);
	}

	// exit the application
	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();
}

void binaryApp::draw()
{
	clearScreen();

	m_2dRenderer->begin();

	m_binaryTree.draw(m_2dRenderer, m_selectedNode);

	m_2dRenderer->drawText(g_systemFont, "press Esc to quit", 0, 0);

	m_2dRenderer->end();

}