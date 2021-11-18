#include "Test.h"
#include <imgui/imgui.h>

namespace test
{

	TestMenu::TestMenu(Test*& currentTestPointer):m_CurrentTest(currentTestPointer)
	{

	}

	TestMenu::~TestMenu()
	{

	}

	void TestMenu::OnImGuiRender()
	{
		for (auto& it_test : m_Tests)
		{
			if (ImGui::Button(it_test.first.c_str()))
			{
				m_CurrentTest = it_test.second();
			}
		}
	}

}