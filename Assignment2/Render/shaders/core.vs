#version 330 core
layout(location = 0) in vec3 position;
uniform float x;
uniform float y;
uniform float s;
void main()
{
    gl_Position = vec4(s*position.x+x, s*position.y+y, position.z, 1);
}
