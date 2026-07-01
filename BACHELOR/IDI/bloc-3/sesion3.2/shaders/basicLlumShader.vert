#version 330 core

in vec3 vertex;
in vec3 normal;

out vec4 vertexSCO;
out vec3 normalSCO;

in vec3 matamb;
in vec3 matdiff;
in vec3 matspec;
in float matshin;

out vec3 matambF;
out vec3 matdiffF;
out vec3 matspecF;
out float matshinF;

out vec4 vertSCO;
out vec3 NormSCO;

uniform mat4 proj;
uniform mat4 view;
uniform mat4 TG;


// Valors per als components que necessitem del focus de llum

void main()
{	

    vertSCO = (view * TG * vec4 (vertex, 1.0));
    mat3 NormalMatrix = inverse (transpose (mat3 (view * TG)));
    NormSCO = NormalMatrix*normal;

    gl_Position = proj * vertSCO;
    matambF = matamb;
    matdiffF = matdiff;
    matspecF = matspec;
    matshinF = matshin;
}
