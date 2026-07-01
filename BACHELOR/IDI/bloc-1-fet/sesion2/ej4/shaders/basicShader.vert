#version 330 core

in vec3 vertex;
in vec3 colors;
out vec3 fragcol;

void main()  {
    gl_Position = vec4(vertex, 2.0);
    fragcol = colors;
}
