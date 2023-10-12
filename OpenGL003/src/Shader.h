#pragma once



class Shader
{
private:
	unsigned int m_ShaderID;
	std::unordered_map<std::string, int> m_UniformMapLocation;
public:
	Shader(const std::string& vertexShader, const std::string& fragmentShader);
	~Shader();

	void Bind() const;
	void Unbind() const;

	void SetUniform4f(const std::string &valueName, float v1, float v2, float v3, float v4);
	void SetUniform1i(const std::string &valueName, int v1);
	/// <summary>
	/// 设置 4x4 float 矩阵
	/// </summary>
	/// <param name="valueName">变量名</param>
	/// <param name="transpose">是否转置</param>
	/// <param name="value">数据指针</param>
	void SetUniformMatrix4f(const std::string &valueName, bool transpose, const GLfloat* value);
private:
	int GetUniformLocation(const std::string& valueName);
	static void GetShaderSource(const std::string& path, std::string& shaderCode);
};