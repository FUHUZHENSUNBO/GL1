#pragma once
#include<iostream>
#include<cstring>
#include<unordered_map>
#include<vector>
#include<GL/glew.h>
#include <glm/gtc/matrix_transform.hpp>
struct ShaderProgaramSource
{
	std::string VertexSource;
	std::string FragmentSource;
};


class Shader
{
private:
	std::string m_FilePath;
	unsigned int m_RendererID;
	std::unordered_map<std::string, int> m_UniformLocationCache;

public:
	Shader(const std::string& filepath);
	~Shader();

	void Bind()const;
	void UnBind()const;


	//Set Uniform
	void SetUniform1i(const std::string& name, int value);

	void SetUniform1f(const std::string& name, float value);

	void SetUniform2f(const std::string& name, float v0, float v1);
	void SetUniform2f(const std::string& name, const glm::vec2& value);

	void SetUniform3f(const std::string& name, float v0, float v1, float v2);
	void SetUniform3f(const std::string& name, const glm::vec3& value);

	void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3);
	void SetUniform4f(const std::string& name, const glm::vec4& value);

	void SetUniformMat3(const std::string& name, const glm::mat3& proMat);

	void SetUniformMat4(const std::string& name, const glm::mat4& proMat);

private:
	/// <summary>
	/// 
	/// </summary>
	/// <param name="filepath"></param>
	/// <returns></returns>
	ShaderProgaramSource ParseShader(const std::string& filepath);

	/// <summary>
	/// 
	/// </summary>
	/// <param name="src"></param>
	/// <param name="type"></param>
	/// <returns></returns>
	unsigned int CompileShader(const std::string& src, unsigned int type);

	/// <summary>
	/// 
	/// </summary>
	unsigned int CreateShader(const std::string& SourceOfVertexShader, const std::string& SourceOfFragmentShader);

	/// <summary>
	/// 
	/// </summary>
	int GetUniformLocation(const std::string& name);
};
