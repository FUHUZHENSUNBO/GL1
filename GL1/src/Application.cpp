#include<GL/glew.h> 
#include<GL/wglew.h>
#include <GLFW/glfw3.h>
#include<iostream>
#include<fileapi.h>
#include<fstream>
#include<string>
#include<sstream>
#include<ctime>
#include<cstdlib>
#include <glm/gtc/matrix_transform.hpp>
#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw_gl3.h>
#include"Renderer.h"
#include"VertexBuffer.h"
#include"IndexBuffer.h"
#include"VertexArray.h"
#include"Shader.h"
#include"VertexBufferLayout.h"
#include "Texture.h"
#include "tests/Test.h"
#include "tests/TestClearColor.h"
#include "tests/TestTexture2D.h"

int main(void)
{
	//初始化窗口
#if 1
	GLFWwindow* window;
	/* Initialize the library */
	if (!glfwInit())
		return -1;
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(1280, 860, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}
	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	glfwSwapInterval(1);
#endif

	if (glewInit() != GLEW_OK)
	{
		std::cout << "Error!" << std::endl;
	}

	/*输出对应的GLVERSION*/
	std::cout << glGetString(GL_VERSION) << std::endl;
	{
		GLCall(glEnable(GL_BLEND));
		GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_CONSTANT_ALPHA));
		Renderer renderer;
		ImGui::CreateContext();
		ImGui_ImplGlfwGL3_Init(window, true);
		ImGui::StyleColorsDark();
		test::Test* currentTest = nullptr;
		test::TestMenu* testMenu = new test::TestMenu(currentTest);
		currentTest = testMenu;
		testMenu->RegisterTest<test::TestClearColor>("clear color");
		testMenu->RegisterTest<test::TestTexture2D>("Texture 2D");


		/* Loop until the user closes the window */
		while (!glfwWindowShouldClose(window))
		{
			/* Render here */
			GLCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
			renderer.Clear();
			ImGui_ImplGlfwGL3_NewFrame();


			if (currentTest)
			{
				currentTest->OnUpdate(0.0f);
				currentTest->OnRender();
				ImGui::Begin("Test");
				if (currentTest != testMenu && ImGui::Button("<-"))
				{
					delete currentTest;
					currentTest = testMenu;
				}
				currentTest->OnImGuiRender();
				ImGui::End();
			}

			ImGui::Render();
			ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());



			/* Swap front and back buffers */
			glfwSwapBuffers(window);
			/* Poll for and process events */
			glfwPollEvents();
		}
		delete currentTest;
		if (currentTest != testMenu)
		{
			delete testMenu;
		}
	}

	ImGui_ImplGlfwGL3_Shutdown();
	ImGui::DestroyContext();
	glfwTerminate();
	return 0;
}













//texture
#if 0
#include<GL/glew.h> 
#include<GL/wglew.h>
#include <GLFW/glfw3.h>
#include<iostream>
#include<fileapi.h>
#include<fstream>
#include<string>
#include<sstream>
#include<ctime>
#include<cstdlib>
#include <glm/gtc/matrix_transform.hpp>
#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw_gl3.h>
#include"Renderer.h"
#include"VertexBuffer.h"
#include"IndexBuffer.h"
#include"VertexArray.h"
#include"Shader.h"
#include"VertexBufferLayout.h"
#include "Texture.h"



#if 0
unsigned int static aCompileShader(const std::string& src, unsigned int type);
unsigned int static aCreateShader(const std::string& SourceOfVertexShader, const std::string& SourceOfFragmentShader);

unsigned int static aCompileShader(const std::string& src, unsigned int type)
{
	unsigned int shader = glCreateShader(type);
	const char* sourceCode = src.c_str();
	glShaderSource(shader, 1, &sourceCode, nullptr);
	glCompileShader(shader);

	GLsizei result;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &result);

	if (!result)
	{
		GLsizei length;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);
		GLchar* message = (char*)alloca(sizeof(char) * length);
		glGetShaderInfoLog(shader, 1, &length, message);
		std::cout << message << std::endl;
		glDeleteShader(shader);
	}

	return shader;
}

unsigned int static aCreateShader(const std::string& SourceOfVertexShader, const std::string& SourceOfFragmentShader)
{
	unsigned int program = glCreateProgram();
	unsigned int vs = aCompileShader(SourceOfVertexShader, GL_VERTEX_SHADER);
	unsigned int fs = aCompileShader(SourceOfFragmentShader, GL_FRAGMENT_SHADER);

	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);
	glValidateProgram(program);

	glDeleteShader(vs);
	glDeleteShader(fs);

	return program;
}


static ShaderProgaramSource ParseShader(const std::string& filepath)
{
	std::ifstream stream;
	stream.open(filepath);
	enum class ShaderType
	{
		NONE = -1,
		VERTEX = 0,
		FRAGMENT = 1
	};

	std::string line;
	std::stringstream ss[2];
	int type = (int)ShaderType::NONE;

	if (stream.is_open())
	{
		while (stream.good())
		{
			std::getline(stream, line);
			if (line.find("#shader") != std::string::npos)
			{
				if (line.find("vertex") != std::string::npos)
				{
					type = (int)ShaderType::VERTEX;
				}
				else if (line.find("fragment") != std::string::npos)
				{
					type = (int)ShaderType::FRAGMENT;
				}

			}
			else
			{
				ss[type] << line << '\n';
			}
		}
	}



	return { ss[0].str(),ss[1].str() };
}
#endif

#if 0
static unsigned int CompileShader(const std::string& source, unsigned int type)
{
	unsigned int id = glCreateShader(type);
	const char* src = source.c_str();
	glShaderSource(id, 1, &src, nullptr);
	glCompileShader(id);

	int result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);

	if (!result)
	{
		GLsizei length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		char* message = (char*)alloca(length * sizeof(char));
		glGetShaderInfoLog(id, length, &length, message);
		std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << "shader!" << std::endl;
		std::cout << message << std::endl;
		glDeleteShader(id);
	}

	return id;

}

static int CreateShader(const std::string& vertexShaderSource, const std::string& fragmentShaderSource)
{
	unsigned int program = glCreateProgram();

	unsigned int vs = CompileShader(vertexShaderSource, GL_VERTEX_SHADER);
	unsigned int fs = CompileShader(fragmentShaderSource, GL_FRAGMENT_SHADER);

	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);
	glValidateProgram(program);

	glDeleteShader(vs);
	glDeleteShader(fs);

	return program;
}
#endif


int main(void)
{
	//初始化窗口
#if 1
	GLFWwindow* window;
	/* Initialize the library */
	if (!glfwInit())
		return -1;
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(1280, 860, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}
	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	glfwSwapInterval(1);
#endif


	if (glewInit() != GLEW_OK)
	{
		std::cout << "Error!" << std::endl;
	}

	/*输出对应的GLVERSION*/
	//std::cout << glGetString(GL_VERSION) << std::endl; 

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

	VertexArray va;
	va.Bind();
	VertexBuffer vb(positions, sizeof(positions));
	vb.Bind();
	IndexBuffer ib(indices, sizeof(indices) / sizeof(unsigned int));
	ib.Bind();
	VertexBufferLayout layout;
	layout.Push<float>(2);
	layout.Push<float>(2);
	va.AddBuffer(vb, layout);

	GLfloat z = 0.f;

	glm::mat4 proj = glm::ortho(0.0f, 1280.0f, 0.0f, 860.0f, -1.0f, 10.0f);
	glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));

	//GLCall(glEnableVertexAttribArray(0));
	//GLCall(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0));

	//struct ShaderProgaramSource sps = ParseShader("res/shaders/ashader.txt");
	//unsigned int shader = aCreateShader(sps.VertexSource, sps.FragmentSource);
	//glUseProgram(shader);
	//int location = glGetUniformLocation(shader, "u_color");
	//ASSERT(location != -1);
	//GLCall(glUniform4f(location, r, g, b, a)); 

	Shader shader("res/shaders/ashader.txt");
	shader.Bind();

	Texture texture("C:/Users/AORUS/Desktop/uept.png");
	texture.Bind();

	shader.SetUniform1i("u_Texture", 0);



	Renderer render;
#if 1
	ImGui::CreateContext();

	ImGui_ImplGlfwGL3_Init(window, true);
	ImGui::StyleColorsDark();
#endif
	//随机种子
	srand((unsigned)time(NULL));
	bool flag = false;


#if 0
	bool show_demo_window = true;
	bool show_another_window = false;
	ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
#endif


	glm::vec3 translationA(200, 200, 0);
	glm::vec3 translationB(400, 200, 0);


	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		render.Clear();
#if 1
		ImGui_ImplGlfwGL3_NewFrame();
#endif
		{
			float r = (float)(rand() % 10) / 10;
			float g = (float)(rand() % 10) / 10;
			float b = (float)(rand() % 10) / 10;
			float a = (float)(rand() % 10) / 10;
			shader.SetUniform4f("u_Color", r, g, b, a);
			render.Draw(va, ib, shader);
		}

		{
			glm::mat4 model = glm::translate(glm::mat4(1.0f), translationA);
			glm::mat4 mvp = proj * view * model;
			shader.SetUniformMat4f("u_MVP", mvp);
			render.Draw(va, ib, shader);
		}

		{
			glm::mat4 model = glm::translate(glm::mat4(1.0f), translationB);
			glm::mat4 mvp = proj * view * model;
			shader.SetUniformMat4f("u_MVP", mvp);
			render.Draw(va, ib, shader);
		}
		//shader.Bind();



#if 0
		r = (float)(rand() % 10) / 10;
		g = (float)(rand() % 10) / 10;
		b = (float)(rand() % 10) / 10;
		a = (float)(rand() % 10) / 10;
		shader1.SetUniform4f("u_Color", r, g, b, a);
#endif



#if 1
		{
#if 0
			static float f = 0.0f;
			static int counter = 0;
			ImGui::Text("Hello, world!");                           // Display some text (you can use a format string too)
#endif
			ImGui::SliderFloat3("TranslationA", &translationA.x, 0.0f, 960.0f);
			ImGui::SliderFloat3("TranslationB", &translationB.x, 0.0f, 960.0f);
#if 0
			ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

			ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our windows open/close state
			ImGui::Checkbox("Another Window", &show_another_window);

			if (ImGui::Button("Button"))                            // Buttons return true when clicked (NB: most widgets return true when edited/activated)
				counter++;
			ImGui::SameLine();
			ImGui::Text("counter = %d", counter);
#endif


			ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		}


		ImGui::Render();
		ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());

#endif
		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}
#if 1
	ImGui_ImplGlfwGL3_Shutdown();
	ImGui::DestroyContext();
#endif
	glfwTerminate();
	return 0;
}
#endif