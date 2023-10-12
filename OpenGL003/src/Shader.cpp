#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "render.h"
#include "Shader.h"

Shader::Shader(const std::string& vertexShader, const std::string& fragmentShader)
	:m_ShaderID(0)
{
	// 创建shader对象
	GLCall(unsigned int m_VertexShaderID = glCreateShader(GL_VERTEX_SHADER));
	GLCall(unsigned int m_FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER));

	std::string str_vertexShaderSource;
	std::string str_FragmentShaderSource;
	GetShaderSource(vertexShader, str_vertexShaderSource);
	GetShaderSource(fragmentShader, str_FragmentShaderSource);

	const char* vertexShaderSource = str_vertexShaderSource.c_str();
	const char* fragmentShaderSource = str_FragmentShaderSource.c_str();

	// shader代码关联到shader对象
	glShaderSource(m_VertexShaderID, 1, &vertexShaderSource, NULL);
	glShaderSource(m_FragmentShaderID, 1, &fragmentShaderSource, NULL);

	//-----------Compile--------------
	int success;
	char infoLog[512];

	GLCall(glCompileShader(m_VertexShaderID));
	glGetShaderiv(m_VertexShaderID, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(m_VertexShaderID, 512, NULL, infoLog);
		std::cout << "Vertex"<< " compile error!\n" << infoLog << std::endl;
	}

	GLCall(glCompileShader(m_FragmentShaderID));
	glGetShaderiv(m_FragmentShaderID, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(m_VertexShaderID, 512, NULL, infoLog);
		std::cout << "Fragment" << " compile error!\n" << infoLog << std::endl;
	}

	m_ShaderID = glCreateProgram();
	glAttachShader(m_ShaderID, m_VertexShaderID);
	glAttachShader(m_ShaderID, m_FragmentShaderID);
	glLinkProgram(m_ShaderID);

	// 删除着色器对象
	glDeleteShader(m_VertexShaderID);
	glDeleteShader(m_FragmentShaderID);

	// 查错
	glGetProgramiv(m_ShaderID, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(m_ShaderID, 512, NULL, infoLog);
		std::cout << "ShaderProgram Error!\n" << infoLog << std::endl;
	}
}

Shader::~Shader()
{
	GLCall(glDeleteProgram(m_ShaderID));
}

void Shader::Bind() const
{
	GLCall(glUseProgram(m_ShaderID));
}

void Shader::Unbind() const
{
	GLCall(glUseProgram(0));
}

void Shader::SetUniform4f(const std::string& valueName, float v1, float v2, float v3, float v4)
{
	GLCall(glUniform4f(GetUniformLocation(valueName), v1, v2, v3, v4));
}

void Shader::SetUniform1i(const std::string& valueName, int v1)
{
	GLCall(glUniform1i(GetUniformLocation(valueName), v1));
}

void Shader::SetUniformMatrix4f(const std::string& valueName, bool transpose, const GLfloat* value)
{
	GLCall(glUniformMatrix4fv(GetUniformLocation(valueName), 1 ,transpose, value));
}

int Shader::GetUniformLocation(const std::string& valueName)
{
	if (m_UniformMapLocation.find(valueName) != m_UniformMapLocation.end())
		return m_UniformMapLocation[valueName];

	GLCall(int location = glGetUniformLocation(m_ShaderID, valueName.c_str()));
	if (location == -1)
	{
		std::cout << "Can't find uniform value '" << valueName << "' !" << std::endl;
	}
	m_UniformMapLocation[valueName] = location;
	return location;
}

void Shader::GetShaderSource(const std::string& path, std::string& shaderSource)
{
	std::ifstream infile;
	std::stringstream sstr;
	infile.open(path, std::ios::in);
	if (infile)
	{
		while (!infile.eof())
		{
			std::string str_t;
			getline(infile, str_t);
			sstr << str_t << '\n';
		}
	}
	else
	{
		std::cout << "Can't open file" << std::endl;
		infile.close();
		return;
	}

	shaderSource = sstr.str();
	infile.close();
	return;
}
