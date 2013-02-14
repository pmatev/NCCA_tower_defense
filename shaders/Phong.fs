#version 150


in vec3 normal;
out vec4 outColour;
void main ()
{
 // set the fragment colour to the current texture
 outColour = vec4(normal,0);
}
