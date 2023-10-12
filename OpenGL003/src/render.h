#pragma once

#include <sstream>
#include <fstream>
#include <iostream>
#include <unordered_map>
#include <string>
#include <vector>

#define ASSERT(x) if(!(x)) __debugbreak();
#define GLCall(x) GLClearError();\
		x;\
		ASSERT(GLLogCall(#x, __FILE__, __LINE__))

#define WIDTH	800
#define HEIGHT	600

#ifndef PI
#define PI 3.14159f
#endif




void GLClearError();
bool GLLogCall(const char* function, const char* file, int line);
bool LoadTexture(unsigned int* texture, const std::string& path, unsigned char index, int texColorMode, int resColorMode, bool bGenerateMipmap = true);

