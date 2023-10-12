#pragma once

class VertexArray
{
private:
	unsigned int m_VAO;	// Vertex Array Object
	unsigned int m_EBO;	// Element Buffer Object
	unsigned int m_VBO;	// Vertex Buffer Object
	int m_vertexCount;	// 顶点数目 索引的数目
	std::vector<int> m_attribLayout;	// 每个属性的维度数目
public:
	VertexArray(int count);
	~VertexArray();
	/// <summary>
	/// 添加顶点
	/// </summary>
	/// <param name="count">顶点个数</param>
	/// <param name="nDimen">每个顶点的维度</param>
	/// <param name="data">数据指针</param>
	void AddBuffer(int count, int nDimen, const float* data);
	void AddElementBuffer(int count, const unsigned int* data);

/// <summary>
/// 添加属性
/// </summary>
/// <param name="index">属性索引</param>
/// <param name="nDimen">属性维度</param>
/// <param name="stride">步幅</param>
/// <param name="offset">偏置</param>
	void AddVertexAttrib(unsigned int index, int nDimen, int stride, int offset);
	void DrawElement();
	void Bind();
	void Unbind();

	void PushAttrib(int nDimen);
	void ClearAttrib();

	// 应用当前属性布局
	void ApplyLayout();
};