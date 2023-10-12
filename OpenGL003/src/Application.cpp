#define STB_IMAGE_IMPLEMENTATION

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb/stb_image.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "render.h"
#include "Shader.h"
#include "Camera.h"
#include "VertexArray.h"




bool LibInit();
void mouse_callback(GLFWwindow* window, double xpos, double ypos);

// 全局变量
float currentTime =0.0f;
float deltaTime = 0.0f;
float lastTime = 0.0f;

Camera camera;

int main()
{
	if (!LibInit())
		return -1;

	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "OpenGL003", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Fail to create a window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	// 垂直同步
	glfwSwapInterval(1);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Fail to initialize glad" << std::endl;
		return false;
	}

	GLCall(glViewport(0, 0, WIDTH, HEIGHT));

	// 声明回调函数
	void framebuffer_size_callback(GLFWwindow * window, int width, int height);
	void scroll_callback(GLFWwindow* window, double offsetx, double offsery);

	// 注册回调函数
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);

	// 声明交互函数
	void ProcessInput(GLFWwindow * window);
	// 捕捉cursor
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	glm::mat4 modelTrans(1.f);
	glm::mat4 viewTrans(1.f);
	glm::mat4 projectionTrans;



	float vertice[] =
	{
		// 位置坐标			纹理坐标
		 0.5f, 0.5f,0.5f,		1.0f, 1.0f,
		-0.5f, 0.5f,0.5f,		0.0f, 1.0f,
		-0.5f,-0.5f,0.5f,		0.0f, 0.0f,
		 0.5f,-0.5f,0.5f,		1.0f, 0.0f,

		 0.5f, 0.5f,-0.5f,		1.0f, 1.0f,
		-0.5f, 0.5f,-0.5f,		0.0f, 1.0f,
		-0.5f,-0.5f,-0.5f,		0.0f, 0.0f,
		 0.5f,-0.5f,-0.5f,		1.0f, 0.0f,

		0.5f, 0.5f, 0.5f,		1.0f, 1.0f,
		0.5f,-0.5f, 0.5f,		0.0f, 1.0f,
		0.5f,-0.5f,-0.5f,		0.0f, 0.0f,
		0.5f, 0.5f,-0.5f,		1.0f, 0.0f,

		-0.5f, 0.5f, 0.5f,		1.0f, 1.0f,
		-0.5f,-0.5f, 0.5f,		0.0f, 1.0f,
		-0.5f,-0.5f,-0.5f,		0.0f, 0.0f,
		-0.5f, 0.5f,-0.5f,		1.0f, 0.0f,

		 0.5f,0.5f ,0.5f,		1.0f, 1.0f,
		-0.5f,0.5f ,0.5f,		0.0f, 1.0f,
		-0.5f,0.5f ,- 0.5f,		0.0f, 0.0f,
		 0.5f,0.5f ,-0.5f,		1.0f, 0.0f,

		 0.5f,-0.5f, 0.5f,		1.0f, 1.0f,
		-0.5f,-0.5f, 0.5f,		0.0f, 1.0f,
		-0.5f,-0.5f,-0.5f,		0.0f, 0.0f,
		 0.5f,-0.5f,-0.5f,		1.0f, 0.0f,
	};


	unsigned int indice[36] =
	{
		0,1,2,
		2,3,0
	};
	for (int i = 6; i < 36; i++)
	{
		indice[i] = indice[i - 6] + 4;
	}
	
	std::vector<glm::vec3> positions;
	for (int i = 0; i < 10; i++)
	{
		float x, y, z;
		x = float(rand() % 200) / 10.0f;
		y = float(rand() % 200) / 10.0f;
		z = float(rand() % 200) / 10.0f;
		positions.push_back(glm::vec3( x, y, z));
	}
	positions.push_back(glm::vec3(0.0f, 0.0f, -5.0f));
	positions.push_back(glm::vec3(2.0f, 2.0f, -3.0f));

	// 纹理
	unsigned int texture;
	unsigned int texture1;
	stbi_set_flip_vertically_on_load(true);			// 反转Y轴
	std::string img_path(".\\res\\container.jpg");
	LoadTexture(&texture, img_path, 0, GL_RGB, GL_RGB);
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));		// 设置环绕方式

	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));	// 设置插值方式
	img_path = ".\\res\\awesomeface.png";
	LoadTexture(&texture1, img_path, 1, GL_RGBA, GL_RGBA);
	
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));		// 设置环绕方式

	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));	// 设置插值方式
	
	// 变换
	

	modelTrans = glm::rotate(modelTrans, -PI/3.5f, glm::vec3(1.0f, 0.0f, 0.0f));
	viewTrans = glm::translate(viewTrans, glm::vec3(0.0f, 0.0f, -3.0f));
	projectionTrans = glm::perspective(PI / 4.0f, (float)WIDTH/(float)HEIGHT, 0.1f, 100.0f);

	{
		VertexArray va1(36);
		va1.AddBuffer(24, 5, vertice);
		va1.AddElementBuffer(36, indice);
		va1.PushAttrib(3);
		va1.PushAttrib(2);
		va1.ApplyLayout();

		std::string vertexShaderPath(".\\res\\VertexShader.shader");
		std::string fragmentShaderPath(".\\res\\FragmentShader.shader");
		Shader shader(vertexShaderPath, fragmentShaderPath);
		shader.Bind();
		// 设置uniform
		//shader.SetUniform4f("theColor", 1.0f, 0.3f, 0.3f, 1.f);
		//shader.SetUniform1i("texture0", 0);
		
		
		shader.SetUniform1i("texture1", 1);
		GLCall(glClearColor(0.223f, 0.773f, 0.733f, 1.f));
		GLCall(glEnable(GL_DEPTH_TEST));	// 深度检测


		lastTime = currentTime = glfwGetTime();
		while (!glfwWindowShouldClose(window))
		{
			glm::mat4 temp(1.f);
			int i;
			
			currentTime = glfwGetTime();
			deltaTime = currentTime - lastTime;
			lastTime = currentTime;
			
			viewTrans = camera.GetViewTrans();
			projectionTrans = camera.GetProjectionTrans();

			

			for (i =0;i<positions.size();i++)
			{
				temp = glm::mat4(1.0f);
				temp = glm::translate(temp, positions[i]);
				if(i%3==0)
					temp = glm::rotate(temp, (float)currentTime, glm::vec3(1.0f, 0.4f, 0.2f));
				shader.SetUniformMatrix4f("modelTrans", false, glm::value_ptr(temp));
				va1.DrawElement();
			}
			shader.SetUniformMatrix4f("viewTrans", false, glm::value_ptr(viewTrans));
			shader.SetUniformMatrix4f("projectionTrans", false, glm::value_ptr(projectionTrans));

			// 处理键盘交互
			ProcessInput(window);
			// 交换缓冲
			glfwSwapBuffers(window);

			GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));	// 清除颜色和深度检测缓冲

			// 检查触发事件
			glfwPollEvents();
		}
	}
	glfwTerminate();
	return 0;
}

inline bool LibInit()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	
	return true;
}

// 回调函数 改变窗口大小和位置时 重新设置视口
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	GLCall(glViewport(0, 0, WIDTH, HEIGHT));
}

// 处理交互
void ProcessInput(GLFWwindow* window)
{
	// 检测esc按下，则关闭窗口
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		camera.ProcessKeyInput(FRONT, deltaTime);
	}

	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		camera.ProcessKeyInput(BACK, deltaTime);
	}

	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		camera.ProcessKeyInput(LEFT, deltaTime);
	}

	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		camera.ProcessKeyInput(RIGHT, deltaTime);
	}

	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		camera.ProcessKeyInput(UP, deltaTime);
	}

	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
	{
		camera.ProcessKeyInput(DOWN, deltaTime);
	}
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	static bool firstMouse = true;
	static float lastX = WIDTH / 2;
	static float lastY = HEIGHT / 2;

	if (firstMouse)
	{
		firstMouse = false;
		lastX = xpos;
		lastY = ypos;
	}

	float offsetX = xpos - lastX;
	float offsetY = lastY - ypos;

	camera.ProcessMouse(offsetX, offsetY);

	lastX = xpos;
	lastY = ypos;
}

void scroll_callback(GLFWwindow * window, double offsetx, double offsety)
{
	camera.ProcessScroll(offsety);
}