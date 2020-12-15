#version 330 core


in vec2 vUv0; // out del vertex shader

in vec3 Normal;


uniform sampler2D textura1; // tipo sampler2D para texturas 2D
uniform sampler2D textura2; // tipo sampler2D para texturas 2D

uniform vec4 OutColor;   // color del que se pintara la parte de fuera
uniform vec4 InColor;    // color del que se pintara la parte de dentro


uniform vec4 lightPos;      // direccion de la luz (considerada como vector)
uniform vec4 intLuz;        // intensidad de luz
uniform vec4 lightAmbient;   
uniform vec4 lightDiffuse; 


out vec4 vFrontColor;
out vec4 vBackColor;

uniform vec4 materialDiffuse;

in mat4 modelViewMat; 
in mat4 normalMat; 

out vec4 fFragColor; // out del fragment shader

float diff(vec3 cVertex, vec3 cNormal)
{
    vec3 lightDir = lightPos.xyz; // directional light ?
    if (lightPos.w == 1) // positional light ?
    lightDir = lightPos.xyz ‐ cVertex;
    return max(dot(cNormal, normalize(lightDir)), 0.0);
    // dot: coseno ángulo
}


void main() {
	vec3 color = vec3(texture(textura1, vUv0));
	vec3 color2 = vec3(texture(textura2, vUv0));

	 if(color.x > 0.55) discard;         // si el texel cumple esta caracteristica, salimos y no se pinta (como un return)
 
    vec3 norm ;
    vec4 col;
    vec3 colTex;
    if(gl_FrontFacing){ 
        norm = -normalize(Normal);
        col=OutColor;
        colTex=color2;
    } 
    else
    {
        norm = normalize(Normal);
        col=InColor;
        colTex=color;
    }
 
    vec3 ambient = lightAmbient * materialDiffuse;
    // diffuse en view space
    vec3 viewVertex = vec3(modelViewMat * vertex);
    vec3 viewNormal = normalize(vec3(normalMat * vec4(normal,0)));
    vec3 diffuse = diff(viewVertex, viewNormal) * lightDiffuse * materialDiffuse;
    vFrontColor = ambient + diffuse; // + specular
    diffuse = diff(viewVertex, ‐viewNormal) * lightDiffuse * materialDiffuse;
    vBackColor = ambient + diffuse; // + specular   
    fFragColor = vec4(vec3(col) *colTex*diffuse  , 1.0);       
}

