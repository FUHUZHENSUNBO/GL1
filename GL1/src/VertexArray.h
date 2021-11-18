#pragma once
#include"VertexBuffer.h"
class VertexBufferLayout;



class VertexArray
{
private:
	unsigned int m_RendererID;

public:
	/// <summary>
	/// 
	/// </summary>
	VertexArray();

	
	~VertexArray();

	/// <summary>
	/// 
	/// </summary>
	void Bind()const;

	/// <summary>
	/// 
	/// </summary>
	void UnBind()const;

	void AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);
};