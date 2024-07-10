#version 330 core

in vec3 vertex;
in vec3 colors;
out vec3 fragcol;
uniform mat4 TG;

void main()  {
    gl_Position = TG*vec4(vertex, 1.0);
    fragcol = colors;
}
