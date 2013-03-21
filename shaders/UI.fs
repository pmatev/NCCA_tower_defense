#version 330
uniform sampler2D tex;
uniform vec4 colourSelect;
in vec2 vertUV;
out vec4 fragColour[2];

void main()
{
    fragColour[0]= texture(tex,vertUV.st);

    fragColour[1] = colourSelect;
}
