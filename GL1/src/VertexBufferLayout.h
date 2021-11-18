#pragma once
#include<iostream>
#include<vector>
#include<GL/glew.h>
#include"Renderer.h"


struct VertexBufferElement
{
	VertexBufferElement(unsigned int t, unsigned int c, bool n)
	{
		type = t;
		count = c;
		normalized = n;
	}

	unsigned int type;
	unsigned int count;
	bool normalized;

	static unsigned int GetSizeOfType(unsigned int type)
	{
		switch (type)
		{
		case GL_FLOAT: 
			return sizeof(GLfloat);
		case GL_UNSIGNED_INT: 
			return sizeof(GLuint);
		case GL_UNSIGNED_BYTE: 
			return sizeof(GLubyte);
		}
		ASSERT(false);
		return 0;
	}
};

class VertexBufferLayout
{
private:
	std::vector<VertexBufferElement> m_Elements;
	unsigned int m_Stride;

public:
	VertexBufferLayout();
	~VertexBufferLayout();

	template<typename T>
	void Push(unsigned int count)
	{
		static_assert(false);
	}

	template<>
	void Push<float>(unsigned int count)
	{
		m_Elements.push_back({ GL_FLOAT,count,GL_FALSE });
		m_Stride += (VertexBufferElement::GetSizeOfType(GL_FLOAT) * count);
	}

	template<>
	void Push<unsigned int>(unsigned int count)
	{
		m_Elements.push_back({ GL_UNSIGNED_INT,count,GL_FALSE });
		m_Stride += (VertexBufferElement::GetSizeOfType(GL_UNSIGNED_INT) * count);
	}

	template<>
	void Push<unsigned char>(unsigned int count)
	{
		m_Elements.push_back({ GL_UNSIGNED_BYTE,count,GL_TRUE });
		m_Stride += (VertexBufferElement::GetSizeOfType(GL_UNSIGNED_BYTE) * count);
	}

	inline const std::vector<VertexBufferElement> GetElements() const { return m_Elements; }

	inline unsigned int GetStride() const { return m_Stride; }

};

