#version 410 core
layout (location = 0) in vec2 pos;
layout (location = 1) in vec3 colorIn;

out vec4 color;

void main ()
{
	color = vec4(colorIn,1);
	gl_Position = vec4(pos,0,1);
}