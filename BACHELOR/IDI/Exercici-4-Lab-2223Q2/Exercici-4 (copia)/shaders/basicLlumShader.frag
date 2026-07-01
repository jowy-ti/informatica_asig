#version 330 core

in vec3  fmatamb;
in vec3  fmatdiff;
in vec3  fmatspec;
in float fmatshin;
in vec3  fvertex;
in vec3  fnormal;

const vec3 llumAmbient = vec3(0.1, 0.1, 0.1);

vec3 PosFB = vec3(5.,10.,5.);

uniform vec4 PosF0;
uniform vec4 PosF1;
uniform vec4 PosF2;
uniform vec4 PosF3;

uniform int IDB;
uniform int ID0;
uniform int ID1;
uniform int ID2;
uniform int ID3;

vec3 colorFB = vec3(0.4, 0.4, 0.4);
vec3 colorF0 = vec3(0.4, 0., 0.);
vec3 colorF1 = vec3(0., 0.4, 0.);
vec3 colorF2 = vec3(0., 0., 0.4);
vec3 colorF3 = vec3(0.4, 0.4, 0.);

uniform mat4 TG;
uniform mat4 Proj;
uniform mat4 View;

out vec4 FragColor;


vec3 Ambient() {
  return llumAmbient*fmatamb;
}

vec3 Difus (vec3 NormSCO, vec3 L, vec3 colFocus)
{
  // Fixeu-vos que SOLS es retorna el terme de Lambert!
  // S'assumeix que els vectors que es reben com a paràmetres estan normalitzats
  vec3 colRes = vec3(0);
  if (dot (L, NormSCO) > 0)
    colRes = colFocus * fmatdiff * dot (L, NormSCO);
  return (colRes);
}

vec3 Especular (vec3 NormSCO, vec3 L, vec3 vertSCO, vec3 colFocus)
{
  // Fixeu-vos que SOLS es retorna el terme especular!
  // Assumim que els vectors estan normalitzats
  vec3 colRes = vec3 (0);
  // Si la llum ve de darrera o el material és mate no fem res
  if ((dot(NormSCO,L) < 0) || (fmatshin == 0))
    return colRes;  // no hi ha component especular

  vec3 R = reflect(-L, NormSCO); // equival a: 2.0*dot(NormSCO,L)*NormSCO - L;
  vec3 V = normalize(-vertSCO); // perquè la càmera està a (0,0,0) en SCO

  if (dot(R, V) < 0)
    return colRes;  // no hi ha component especular

  float shine = pow(max(0.0, dot(R, V)), fmatshin);
  return (colRes + fmatspec * colFocus * shine);
}

void main() {

    vec4 focusSCO = View * vec4(PosFB,1.0);
    vec3 LB = normalize(focusSCO.xyz - fvertex);
    
    focusSCO = View * PosF0;
    vec3 L0 = normalize(focusSCO.xyz - fvertex);
    
    focusSCO = View * PosF1;
    vec3 L1 = normalize(focusSCO.xyz - fvertex);
    
    focusSCO = View * PosF2;
    vec3 L2 = normalize(focusSCO.xyz - fvertex);
    
    focusSCO = View * PosF3;
    vec3 L3 = normalize(focusSCO.xyz - fvertex);

    vec3 NN = normalize(fnormal);
    vec3 Lambert = Ambient();
    if (IDB == 1) Lambert += Difus(NN, LB, colorFB)+Especular(NN, LB, fvertex, colorFB);
    if (ID0 == 1) Lambert += Difus(NN, L0, colorF0)+Especular(NN, L0, fvertex, colorF0);
    if (ID1 == 1) Lambert += Difus(NN, L1, colorF1)+Especular(NN, L1, fvertex, colorF1);
    if (ID2 == 1) Lambert += Difus(NN, L2, colorF2)+Especular(NN, L2, fvertex, colorF2);
    if (ID3 == 1) Lambert += Difus(NN, L3, colorF3)+Especular(NN, L3, fvertex, colorF3);
    
    FragColor = vec4(Lambert, 1);
}
