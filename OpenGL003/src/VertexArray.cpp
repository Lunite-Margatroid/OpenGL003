#include <glad/glad.h>
#include "render.h"
#include "VertexArray.h"

VertexArray::VertexArray(int count):m_vertexCount(count)
{
	GLCall(glGenBuffers(1, &m_VBO));
	GLCall(glGenBuffers(1, &m_EBO));
	GLCall(glGenVertexArrays(1, &m_VAO));

	GLCall(glBindVertexArray(m_VAO));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_VBO));
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO));
}

VertexArray::~VertexArray()
{
	GLCall(glDeleteVertexArrays(1, &m_VAO));
	GLCall(glDeleteBuffers(1, &m_VBO));
	GLCall(glDeleteBuffers(1, &m_EBO));
}

void VertexArray::AddBuffer(int count, int nDimen ,const float* data)
{
	ASSERT(sizeof(float) == sizeof(GL_FLOAT));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_VBO));
	GLCall(glBufferData(GL_ARRAY_BUFFER, nDimen*count * sizeof(GL_FLOAT), data, GL_STATIC_DRAW));
}

void VertexArray::AddElementBuffer(int count, const unsigned int* data)
{
	ASSERT(sizeof(unsigned int) == sizeof(GL_UNSIGNED_INT));
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO));
	GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(GL_UNSIGNED_INT), data, GL_STATIC_DRAW));
	m_vertexCount = count;
}

/// <summary>
/// 添加属性
/// </summary>
/// <param name="index">属性索引</param>
/// <param name="nDimen">属性维度</param>
/// <param name="stride">步幅</param>
/// <param name="offset">偏置</param>
void VertexArray::AddVertexAttrib(unsigned int index, int nDimen, int stride, int offset)
{
	GLCall(glVertexAttribPointer(index, nDimen, GL_FLOAT, GL_FALSE, stride*sizeof(float), (void*)(offset*sizeof(float))));
	GLCall(glEnableVertexAttribArray(index));
}

void VertexArray::DrawElement()
{
	Bind();
	GLCall(glDrawElements(GL_TRIANGLES, m_vertexCount, GL_UNSIGNED_INT, 0));
}

void VertexArray::Bind()
{
	GLCall(glBindVertexArray(m_VAO));
}

void VertexArray::Unbind()
{
	GLCall(glBindVertexArray(0));
}

void VertexArray::PushAttrib(int nDimen)
{
	m_attribLayout.push_back(nDimen);
}

void VertexArray::ClearAttrib()
{
	m_attribLayout.clear();
}

void VertexArray::ApplyLayout()
{
	ASSERT(sizeof(GL_FLOAT) == sizeof(float));
	if (m_attribLayout.empty())
	{
		std::cout << "当前布局为空!" << std::endl;
		return;
	}

	int sum = 0;
	int offset = 0;
	for (int n : m_attribLayout)
	{
		sum += n;
	}
	for (int i = 0; i < m_attribLayout.size(); i++)
	{
		AddVertexAttrib(i, m_attribLayout[i], sum, offset);
		offset += m_attribLayout[i];
	}
}
