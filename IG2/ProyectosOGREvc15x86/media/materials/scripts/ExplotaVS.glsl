#version 330 core // archivo ExplotaVS.glsl
in vec4 vertex;
void main() {
gl_Position = vertex; // El GS tiene que transformar las
coordenadas de gl_Position al espacio de corte
}