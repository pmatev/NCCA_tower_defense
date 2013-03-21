#version 330
struct PointLight
{
    vec4 pos;
    vec4 ambCol;
    vec4 diffCol;
    vec4 specCol;
};
#define numLights 4

out vec4 outColour[2];

uniform vec4 colour;
uniform vec4 colourSelect;
uniform PointLight lights[numLights];

in vec2 uv;
in vec3 normal;
in vec3 lightDir[numLights];
in vec3 halfVector[numLights];

void calcPointLight(    in int i,
                        inout vec4 _amb,
                        inout vec4 _diff,
                        inout vec4 _spec
                     )
{
    vec3 N = normalize(normal);
    vec3 L = normalize(lightDir[i]);
    vec3 R = reflect(-L, N);
    float lambertTerm = max(dot(N, L),0.0);

    _amb += colour * lights[i].ambCol;
    _diff += colour * lights[i].diffCol * lambertTerm;

    _spec += lights[i].specCol * pow(max(0.0,dot(N,R)),20);


}
void main()
{
    outColour[0] = vec4(0,0,0,1);
    outColour[1] = vec4(0,0,0,1);

    vec4 ambient = vec4(0,0,0,1);
    vec4 diffuse = vec4(0,0,0,1);
    vec4 specular = vec4(0,0,0,1);

    for(int i=0; i<numLights; i++)
    {
        calcPointLight(i, ambient, diffuse, specular);
    }

    outColour[0] = ambient+diffuse+specular;

    //draw the colour selection buffer
    outColour[1] = colourSelect;
}
