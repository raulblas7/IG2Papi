#version 330 core

uniform sampler2D textura1; // tipo sampler2D para texturas 2D

in vec2 vUv0; // out del vertex shader

uniform vec4 InColor;
uniform vec4 OutColor; 

uniform float Flipping;
out vec4 fFragColor; // out del fragment shader

uniform vec4 lightPos;      // direccion de la luz (considerada como vector)
uniform vec4 intLuz;        // intensidad de luz

void main() {
vec3 color = vec3(texture(texture1, vUv0));

    if(color.x > 0.55) discard;         // si el texel cumple esta caracteristica, salimos y no se pinta (como un return)

    vec3 norm;
	//bool frontFacing = (Flipping > -1)? gl_FrontFacing : ! gl_FrontFacing;
    if (gl_FrontFacing)
	{
		norm = normalize(Normal); 
		 color = InColor;
    }
	else
	{
		norm = -normalize(Normal);
		  color = OutColor;
	}

        vec3 lightDir = normalize(vec3(lightPos));
        float diff = max(dot(norm, lightDir), 0.0);
        vec3 diffuse = vec3(intLuz) * diff;
        fFragColor = vec4(color * diffuse, 1.0);
}