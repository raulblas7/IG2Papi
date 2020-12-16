#version 330 core

uniform sampler2D textura1; // tipo sampler2D para texturas 2D

uniform sampler2D textura2; // ‐> unidades de textura (int)

in vec2 vUv0; // out del vertex shader

out vec4 fFragColor; // out del fragment shader

void main() {

    vec3 color1 = vec3(texture(textura1, vUv0)); 
	vec3 color2 = vec3(texture(textura2, vUv0));
	vec3 color = color1*color2;         


	fFragColor = vec4(color, 1.0); // out
}