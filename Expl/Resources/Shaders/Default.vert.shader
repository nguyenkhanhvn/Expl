#version 330 core

layout (location = 0) in vec3 a_Position;
out vec3 v_position;

void main()
{
	v_position = a_Position + 0.5;
	gl_Position = vec4(a_Position, 1.0);
}
