#version 330 core
layout(location = 0) in vec3 position;
uniform float x;
uniform float y;
uniform float s = 1.0f;
uniform float rotation;
void main()
{
    gl_Position = vec4(cos(rotation)*s*position.x+x-sin(rotation)*s*position.y, sin(rotation)*s*position.x+cos(rotation)*s*position.y+y, position.z, 1);
}
