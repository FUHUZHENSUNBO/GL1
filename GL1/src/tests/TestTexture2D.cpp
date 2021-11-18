#include "TestTexture2D.h"

namespace test
{

	TestTexture2D::TestTexture2D():m_TranslationA(200, 200, 0), m_TranslationB(400, 200, 0),
	m_proj(glm::ortho(0.0f, 1280.0f, 0.0f, 860.0f, -1.0f, 10.0f)),
	m_view(glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0)))
	{
		/*输出对应的GLVERSION*/
		std::cout << glGetString(GL_VERSION) << std::endl; 

		GLfloat positions[] = {
			-50.f,  -50.f, 0.0f, 0.0f, //0
			50.f,  -50.f, 1.0f, 0.0f, //1
			50.f,  50.f, 1.0f, 1.0f, //2
			-50.f,  50.f, 0.0f, 1.0f  //3
		};

		unsigned int indices[] = {
			0,1,2,
			2,3,0,
		};



		m_VAO = std::make_unique<VertexArray>();
		m_VAO->Bind();

		m_VBO = std::make_unique<VertexBuffer>(positions,sizeof(positions));
		m_VBO->Bind();

		m_IndexBuffer = std::make_unique<IndexBuffer>(indices, sizeof(indices) / sizeof(unsigned int));
		m_IndexBuffer->Bind();

		VertexBufferLayout layout;
		layout.Push<float>(2);
		layout.Push<float>(2);

		m_VAO->AddBuffer(*m_VBO, layout);

		m_Shaser = std::make_unique<Shader>("res/shaders/ashader.txt");
		m_Shaser->Bind();

		m_Texture = std::make_unique<Texture>("C:/Users/AORUS/Desktop/uept.png");

		m_Shaser->SetUniform1i("u_Texture", 0);
	}

	TestTexture2D::~TestTexture2D()
	{

	}

	void TestTexture2D::OnUpdata(float deltaTime)
	{

	}

	void TestTexture2D::OnRender()
	{
		GLCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
		GLCall(glClear(GL_COLOR_BUFFER_BIT));

		Renderer render;
		render.Clear();
		m_Texture->Bind();
		m_Shaser->Bind();
		{
			glm::mat4 model = glm::translate(glm::mat4(1.0f), m_TranslationA);
			glm::mat4 mvp = m_proj * m_view * model;
			m_Shaser->SetUniformMat4("u_MVP", mvp);
			render.Draw(*m_VAO, *m_IndexBuffer, *m_Shaser);
		}

		{
			glm::mat4 model = glm::translate(glm::mat4(1.0f), m_TranslationB);
			glm::mat4 mvp = m_proj * m_view * model;
			m_Shaser->SetUniformMat4("u_MVP", mvp);
			render.Draw(*m_VAO, *m_IndexBuffer, *m_Shaser);
		}
		m_Shaser->UnBind();
		m_Texture->UnBind();
	}

	void TestTexture2D::OnImGuiRender()
	{
		ImGui::SliderFloat3("TranslationA", &m_TranslationA.x, 0.0f, 960.0f);
		ImGui::SliderFloat3("TranslationB", &m_TranslationB.x, 0.0f, 960.0f);
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	}
}
