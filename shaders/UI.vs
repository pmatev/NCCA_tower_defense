#version 150
in vec2 inVert;
in vec2 inUV;
out vec2 vertUV;
uniform float xpos;
uniform float ypos;
uniform float scaleX;
uniform float scaleY;

void main()
{
    vertUV = inUV;
    gl_Position= vec4( ((xpos+inVert.x)*scaleX)-1,((ypos+inVert.y)*scaleY)-1,0.0,1.0);

}
