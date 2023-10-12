#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb/stb_image.h>


#include "render.h"


void GLClearError()
{
	while (glGetError() != GL_NO_ERROR);
}

bool GLLogCall(const char* function, const char* file, int line)
{
	while (GLenum error = glGetError())
	{
		std::cout << "[OpenGL Error] (" << error << "): " <<
			function << " file: " << file << "  line: " << line << std::endl;
		return false;
	}
	return true;
}

/// <summary>
/// 加载纹理
/// </summary>
/// <param name="texture">纹理对象id</param>
/// <param name="path">纹理图片源文件</param>
/// <param name="index">纹理索引</param>
/// <param name= "texColorMode">纹理颜色模式</param>
/// <param name= "resColorMode">源图片颜色模式</param>
/// <param name="bGenerateMipmap">是否自动生成多级渐远纹理</param>
/// <returns></returns>
bool LoadTexture(unsigned int* texture, const std::string& path, unsigned char index, int texColorMode, int resColorMode, bool bGenerateMipmap)
{
	int width, height, nChannals;
	unsigned char* img_data;
	img_data = stbi_load(path.c_str(), &width, &height, &nChannals, 0);

	if (img_data == 0)
	{
		std::cout << "Fail to load img!" << std::endl;
		return false;
	}
	GLCall(glGenTextures(1, texture));
	GLCall(glActiveTexture(GL_TEXTURE0 + index));
	GLCall(glBindTexture(GL_TEXTURE_2D, *texture)); // 绑定纹理


	GLCall(glTexImage2D(GL_TEXTURE_2D, 0, texColorMode, width, height, 0, resColorMode, GL_UNSIGNED_BYTE, img_data));
	// param1 纹理Target
	// param2 多级渐远级别 0为基本级别
	// param3 纹理格式
	// param4&5 宽度和高度x&y
	// param6 历史遗留 恒为0
	// param7 源数据格式
	// param8 源数据类型
	// param9 源数据

	if (bGenerateMipmap)
		GLCall(glGenerateMipmap(GL_TEXTURE_2D));	// 自动生成多级渐远级别纹理
	stbi_image_free(img_data);	// 释放图像资源
	return true;
}


