#pragma once
#include<GL/glew.h>
#include"IndexBuffer.h"
#include"Shader.h"
#include"VertexArray.h"


void  GLClearError();
bool  GLLogCall(const char* function, const char* file, int line);

#define ASSERT(x) if (!(x)) __debugbreak();

//�˺궨��涨��GLClearError x ASSERT ������ִ��˳��
#define GLCall(x) GLClearError();\
    x;\
    ASSERT(GLLogCall(#x,__FILE__,__LINE__));

class VertexArray;
class IndexBuffer;
class Shader;

class Renderer
{

public:
    void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader)const;
    void Clear()const;
};
