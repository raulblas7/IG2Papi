#version 330 core

in vec4 vertex;                     // atributos de los vertices a procesar
in vec3 normal;
in vec2 uv0;

uniform mat4 modelViewProjMat;      // matriz de transformacion
out mat4 normalMat;             // matriz inversa (normales)
out mat4 modelViewMat;

out vec2 vUv0;                 // out del vertex shader


out vec3 Normal;

void main() {
	Normal = mat3(normalMat)*normal;
    vUv0 = uv0;

	gl_Position = modelViewProjMat * vertex; // obligatorio
}