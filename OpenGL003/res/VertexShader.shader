#version 330 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec2 texturePos;

uniform mat4 modelTrans;
uniform mat4 viewTrans;
uniform mat4 projectionTrans;

out vec2 textureCoord;
void main()
{
	gl_Position = projectionTrans * viewTrans * modelTrans * vec4(aPos, 1.0);
	textureCoord = texturePos;
}