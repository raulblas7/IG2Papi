#version 330 core // archivo NormalesFS.glsl
in vec3 vColor; // interpolado, en este ejemplo, a partir
//de los dos colores asociados a los 2 vértices de la línea
//generada por el Geometry Shader
out vec4 fFragColor;
void main()
{
fFragColor = vec4(vColor, 1.0);
}