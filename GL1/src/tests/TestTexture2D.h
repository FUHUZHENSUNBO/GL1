#pragma once
#include "Test.h"
#include <iostream>
#include <glm/gtc/matrix_transform.hpp>
#include <GL/glew.h>
#include <imgui/imgui.h>
#include "Renderer.h"
#include "VertexBufferLayout.h"
#include "Texture.h"
#include "VertexBuffer.h"

namespace test
{


	class TestTexture2D :public Test
	{
	public:
		TestTexture2D();
		~TestTexture2D();

		void OnUpdata(float deltaTime);
		void OnRender();
		void OnImGuiRender();
	private:
		std::unique_ptr <VertexArray> m_VAO;
		std::unique_ptr <VertexBuffer> m_VBO;
		std::unique_ptr <IndexBuffer> m_IndexBuffer;
		std::unique_ptr <Shader> m_Shaser;
		std::unique_ptr <Texture> m_Texture;


		glm::vec3 m_TranslationA;
		glm::vec3 m_TranslationB;

		glm::mat4 m_proj;
		glm::mat4 m_view;

	};
}