#version 460 core

layout(location = 0) in vec3 pos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

out vec3 WorldPos;

void main()
{
    vec4 world = model * vec4(pos,1.0);
    WorldPos = world.xyz;

    gl_Position = proj * view * world;
}
