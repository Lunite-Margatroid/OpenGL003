#version 330 core
in vec2 textureCoord;
out vec4 FragColor;
uniform vec4 theColor;
uniform sampler2D texture0;
uniform sampler2D texture1;
void main()
{
	FragColor = mix(texture(texture0, textureCoord), texture(texture1, textureCoord), 0.2);
}