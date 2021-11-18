#include "Shader.h"
#include "Renderer.h"
#include<iostream>
#include<fstream>
#include<sstream>


Shader::Shader(const std::string& filepath):m_FilePath(filepath), m_RendererID(0)
{
    ShaderProgaramSource shaderSRC  = ParseShader(filepath);
    m_RendererID = CreateShader(shaderSRC.VertexSource, shaderSRC.FragmentSource);

}


Shader::~Shader()
{
    GLCall(glDeleteProgram(m_RendererID));
}



void Shader::Bind() const
{
    GLCall(glUseProgram(m_RendererID));
}



void Shader::UnBind() const
{
    GLCall(glUseProgram(0));
}


unsigned int Shader::CompileShader(const std::string& src, unsigned int type)
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



unsigned int Shader::CreateShader(const std::string& SourceOfVertexShader, const std::string& SourceOfFragmentShader)
{
    unsigned int program = glCreateProgram();
    unsigned int vs = CompileShader(SourceOfVertexShader, GL_VERTEX_SHADER);
    unsigned int fs = CompileShader(SourceOfFragmentShader, GL_FRAGMENT_SHADER);

    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
}



ShaderProgaramSource Shader::ParseShader(const std::string& filepath)
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






 void Shader::SetUniform1i(const std::string& name, int value)
 {
	 int location = GetUniformLocation(name);
     if (location != -1)
     {
         GLCall(glUniform1i(location, value));
     }
 }


 void Shader::SetUniform1f(const std::string& name, float value)
 {
	 int location = GetUniformLocation(name);
     if (location != -1)
     {
         GLCall(glUniform1f(location, value));
     }
 }



 void Shader::SetUniform2f(const std::string& name, const glm::vec2& value)
 {
	 int location = GetUniformLocation(name);
	 if (location != -1)
	 {
		 GLCall(glUniform2f(location, value.x,value.y));
	 }
 }

 void Shader::SetUniform2f(const std::string& name, float v0, float v1)
 {
	 int location = GetUniformLocation(name);
	 if (location != -1)
	 {
		 GLCall(glUniform2f(location, v0, v1));
	 }
 }


 void Shader::SetUniform3f(const std::string& name, const glm::vec3& value)
 {
	 int location = GetUniformLocation(name);
	 if (location != -1)
	 {
		 GLCall(glUniform3f(location, value.x,value.y,value.z));
	 }
 }

 void Shader::SetUniform3f(const std::string& name, float v0, float v1, float v2)
 {
	 int location = GetUniformLocation(name);
	 if (location != -1)
	 {
		 GLCall(glUniform3f(location, v0, v1, v2));
	 }
 }

 void Shader::SetUniform4f(const std::string& name, const glm::vec4& value)
 {
	 int location = GetUniformLocation(name);
	 if (location != -1)
	 {
		 GLCall(glUniform4f(location, value.x, value.y, value.z, value.w))
	 }
 }

void Shader::SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3)
{
	int location = GetUniformLocation(name);
    if (location != -1)
    {
        GLCall(glUniform4f(location, v0, v1, v2, v3));
    }
}



void Shader::SetUniformMat3(const std::string& name, const glm::mat3& proMat)
{
	int location = GetUniformLocation(name);
	if (location != -1)
	{
		GLCall(glUniformMatrix3fv(location, 1, GL_FALSE, &proMat[0][0]));
	}
}

void Shader::SetUniformMat4(const std::string& name, const glm::mat4& proMat)
{
    int location = GetUniformLocation(name);
    if (location != -1)
    {
        GLCall(glUniformMatrix4fv(location, 1, GL_FALSE, &proMat[0][0]));
    }
    
}





int Shader::GetUniformLocation(const std::string& name)
{
    //ур╣╫ак
    if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end())
    {
        return m_UniformLocationCache[name];
    }

	GLCall(int location = glGetUniformLocation(m_RendererID, name.c_str()));
    if (location == -1)
    {
        std::cerr << "Warning : uniform " << name << "doesn't exist!" << std::endl;
    }

    m_UniformLocationCache[name] = location;    

    return location;
}

