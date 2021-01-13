#version 330 core // archivo NormalesVS.glsl
in vec4 vertex;
in vec3 normal; // atributos de los vértices a procesar
out vec3 gNormal; // out del VS (gNormal) al GS (gNormal[])

void main() {
    gNormal = normalize(normal); // !!
    gl_Position = vertex; // (*)
} // out del VS (gl_Position) al GS (gl_in[].gl_Position)