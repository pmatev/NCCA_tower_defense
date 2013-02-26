#version 150
uniform sampler2D tex;
in vec2 vertUV;
out vec4 fragColour;

void main()
{
    vec4 texture = texture(tex,vertUV);
    fragColour = texture;
}
