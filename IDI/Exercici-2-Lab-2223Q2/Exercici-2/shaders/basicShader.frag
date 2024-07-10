#version 330 core

in vec3 fcolor;

out vec4 FragColor;

uniform vec3 Verd;
uniform int VRick;

void main() {

	if (VRick == 0) FragColor = vec4(fcolor*Verd, 1);
	else FragColor = vec4(vec3(0.,0.7,0.), 1);
}

