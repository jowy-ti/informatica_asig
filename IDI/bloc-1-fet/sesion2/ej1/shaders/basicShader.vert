#version 330 core

in vec3 vertex;

uniform mat4 TG;
uniform mat4 Proj;

void main()  {
    gl_Position = Proj * TG * vec4 (vertex, 1.0);
}
