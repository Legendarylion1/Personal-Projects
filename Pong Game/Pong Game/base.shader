#Vertex Shader
#version 410 core

layout(location = 0) in vec4 position;

uniform mat4 u_PositionMatrix;

void main()
{
   gl_Position = u_PositionMatrix * position;
};

#Fragment Shader
#version 410 core

layout(location = 0) out vec4 color;

uniform vec4 u_Color;

void main()
{
   color = u_Color;
};