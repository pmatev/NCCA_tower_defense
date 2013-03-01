#version 150
uniform vec4 colour;
uniform vec4 colourSelect;

in vec2 uv;
in vec3 normal;
out vec4 outColour[2];

void main()
{
// set the fragment colour to the current texture
 outColour[0] = colour;

//draw the colour selection buffer
 outColour[1] = colourSelect;
}
