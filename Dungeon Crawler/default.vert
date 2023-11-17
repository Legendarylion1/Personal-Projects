#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTex;
layout (location = 3) in vec2 aScaler;

out vec3 color;
out vec2 texCoord;

uniform mat4 mvp;
uniform float healthBar;
uniform float uTexAtlasX;
uniform float uTexAtlasY;

void main()
{
	gl_Position = mvp * vec4(aPos.x + (aScaler.x * healthBar), aPos.y, aPos.z, 1.0);
	color = aColor;
	texCoord = vec2(aTex.x + uTexAtlasX,aTex.y + uTexAtlasY);
}