#version 150

/// @brief projection matrix passed in from camera class in main app
uniform mat4 MVP;

in vec3 inVert;
in vec3 inNormal;

out vec3 normal;

void main()
{
 // calculate the vertex position
 gl_Position = MVP*vec4(inVert, 1.0);
 normal=inNormal;
}











