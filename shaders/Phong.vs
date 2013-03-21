#version 330

struct PointLight
{
    vec4 pos;
    vec4 ambCol;
    vec4 diffCol;
    vec4 specCol;
};

#define numLights 4
uniform PointLight lights[numLights];
uniform mat3 normalMatrix;
uniform mat4 V;
uniform mat4 MV;
uniform mat4 MVP;

layout (location=0) in vec3 inVert;
layout (location=1) in vec2 inUV;
layout (location=2) in vec3 inNormal;

out vec3 vert;
out vec3 normal;
out vec2 uv;

out vec3 lightDir[numLights];
out vec3 halfVector[numLights];



void main()
{
 // calculate the vertex position
 normal = normalMatrix * inNormal;

 vec4 vPosition4 = MV*vec4(inVert,1);
 vec3 vPosition3 = vPosition4.xyz / vPosition4.w;

for(int i=0; i<numLights; ++i)
 {
    vec4 lightPos4 = V*lights[i].pos;
    vec3 lightPos3 = lightPos4.xyz / lightPos4.w;
    lightDir[i] = normalize(lightPos3 - vPosition3);
 }



 uv = inUV;
 gl_Position = MVP*vec4(inVert, 1.0);
}











