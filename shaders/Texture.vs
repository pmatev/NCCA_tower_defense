#version 150
in vec2 inVert;
in vec2 inUV;

out vec2 vertUV;

void main()
{
    vertUV = inUV;
    gl_Position = vec4(inVert,0.0,1.0);

}
