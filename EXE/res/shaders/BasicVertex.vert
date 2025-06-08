#version 330 core  

layout (location = 0) in vec3 position;
layout (location = 1) in vec4 inColor;
layout (location = 2) in vec3 inNormal;

out vec4 ourColor;
out vec3 Normal;
out vec3 FragPos;

uniform mat4 u_Model;
uniform mat4 u_View;
uniform mat4 u_Projection;

uniform vec4 u_Tint;

void main()
{
    FragPos = vec3(u_Model * vec4(position, 1.0));
    Normal = mat3(transpose(inverse(u_Model))) * inNormal;

    gl_Position = u_Projection * u_View * vec4(FragPos, 1.0);
    ourColor = u_Tint * inColor;
};