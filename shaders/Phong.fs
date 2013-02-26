#version 150

uniform vec4 colour;

in vec3 normal;
out vec4 outColour[2];

void main()
{
// set the fragment colour to the current texture
 outColour[0] = vec4(normal,1);

//draw the colour selection buffer
 outColour[1] = colour;
}
