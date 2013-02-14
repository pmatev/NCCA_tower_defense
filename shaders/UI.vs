#version 150
in vec2 inVert;

uniform vec3 colour;
uniform float scaleX;
uniform float scaleY;
uniform float xpos;
uniform float ypos;

void main()
{
    gl_Position=vec4( ((xpos+inVert.x)*scaleX)-1.0,((ypos+inVert.y)*scaleY)+1.0,0.0,1.0);

}
