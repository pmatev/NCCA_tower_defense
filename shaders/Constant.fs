#version 330
uniform sampler2D tex;
uniform vec4 colour;
uniform vec4 colourSelect;
uniform bool textured;
uniform vec4 highlightColour;


in vec2 uv;
in vec3 normal;
out vec4 outColour[2];

void main()
{

 if(textured)
 {
    outColour[0] = colour * texture(tex, uv) * highlightColour;
 }
 else
 {
     outColour[0] = colour * highlightColour;
 }

//draw the colour selection buffer
 outColour[1] = colourSelect;
}
