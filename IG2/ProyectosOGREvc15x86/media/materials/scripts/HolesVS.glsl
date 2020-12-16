#version 330 core

in vec4 vertex;                     // atributos de los vertices a procesar
in vec3 normal;
in vec2 uv0;

uniform mat4 modelViewProjMat;      // matriz de transformacion
uniform mat4 normalMat;             // matriz inversa (normales)
uniform mat4 modelViewMat;

out vec2 vUv0;                 // out del vertex shader
out vec3 viewVertex;
out vec3 viewNormal;

void main() {
	viewVertex = vec3(modelViewMat * vertex);
	viewNormal=normalize(vec3(normalMat* vec4(normal,0)));
    vUv0 = uv0;

	gl_Position = modelViewProjMat * vertex; // obligatorio
}