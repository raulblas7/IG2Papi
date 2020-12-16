#version 330 core


uniform sampler2D textura1; // tipo sampler2D para texturas 2D
uniform sampler2D textura2; // tipo sampler2D para texturas 2D

uniform vec4 OutColor;   // color del que se pintara la parte de fuera
uniform vec4 InColor;    // color del que se pintara la parte de dentro


uniform vec4 lightPos;      // direccion de la luz (considerada como vector)
uniform vec3 lightAmbient;   
uniform vec3 lightDiffuse; 
uniform vec3 materialDiffuse;
uniform float Flipping; 

in vec2 vUv0; // out del vertex shader
in vec3 viewNormal;
in vec3 viewVertex;

out vec4 fFragColor; // out del fragment shader

float diff(vec3 cVertex, vec3 cNormal)
{
    vec3 lightDir = lightPos.xyz; // directional light

    //si es posicional las coordenadas son una posicion
    if (lightPos.w == 1)
    { // positional light 
        lightDir = lightPos.xyz - cVertex;
    }
    return max(dot(cNormal, normalize(lightDir)), 0.0);
    // dot: coseno ángulo
}


void main()
{
	vec3 color = vec3(texture(textura1, vUv0));
	vec3 color2 = vec3(texture(textura2, vUv0));

    vec3 ambient = lightAmbient * materialDiffuse;

    vec3 diffuse =diff(viewVertex, viewNormal)   * lightDiffuse * materialDiffuse;
    vec3 vFrontColor = ambient + diffuse; // + specular

    diffuse = diff(viewVertex, -viewNormal) * lightDiffuse * materialDiffuse;
    vec3 vBackColor = ambient + diffuse; // + specular   
    

	 if(color.x > 0.55) discard;         // si el texel cumple esta caracteristica, salimos y no se pinta (como un return)
     
    bool frontFacing = (Flipping > -1)? gl_FrontFacing : ! gl_FrontFacing;

    vec3 col;

    if(frontFacing) { col = vFrontColor * texture1 * vec3(OutColor);}
    else{ col = vBackColor * texture2 * vec3(InColor);}
     
    fFragColor = vec4(col, 1.0);
}

