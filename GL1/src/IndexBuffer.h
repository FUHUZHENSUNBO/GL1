#pragma once
#include<GL/glew.h>



class IndexBuffer
{
private:
	unsigned int m_RendererID = 0;
	unsigned int m_count = 0;

public:
	IndexBuffer(const void* data,unsigned int size);
	~IndexBuffer();

	/// <summary>
	/// 
	/// </summary>
	void Bind()const;

	/// <summary>
	/// 
	/// </summary>
	void UnBind()const;

	/// <summary>
	/// 
	/// </summary>
	/// <returns></returns>
	inline unsigned int GetCount()const{ 
		return m_count;
	};






};

