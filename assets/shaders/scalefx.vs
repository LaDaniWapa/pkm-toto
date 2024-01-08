#version 330 core

in vec3 vertex;
in vec2 texcoord;

out vec2 fragTexcoord;

void main()
{
    gl_Position = vec4(vertex, 1.0);
    fragTexcoord = texcoord;
}
