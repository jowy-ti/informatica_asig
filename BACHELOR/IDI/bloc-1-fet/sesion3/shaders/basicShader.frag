#version 330 core

in vec3 fragcol;
out vec4 FragColor;

void main() {
    FragColor = vec4(fragcol, 1);
}

