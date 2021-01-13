#version 330 core // archivo ExplotaVS.glsl
in vec4 vertex;                     // atributos de los vertices a procesar
in vec3 normal;
in vec2 uv0;

out vec2 vUv0;                 // out del vertex shader
out vec3 viewVertex;
out vec3 viewNormal;



uniform mat4 modelViewProjMat;      // matriz de transformacion
uniform mat4 normalMat;             // matriz inversa (normales)
uniform mat4 modelViewMat;


void main() {
   
    vUv0 = uv0;
    viewVertex = vec3(modelViewMat * vertex);
	viewNormal=normalize(vec3(normalMat* vec4(normal,0)));
    gl_Position = vertex; // El GS tiene que transformar las
//coordenadas de gl_Position al espacio de corte
}