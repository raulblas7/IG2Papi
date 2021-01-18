#version 330 core // archivo ExplotaGS.glsl
layout (triangles) in; // procesa un triángulo: recibe 1 triángulo y
layout (triangle_strip, max_vertices = 3) out; // emite 1 triángulo
// al no declarar ninguna variable in, estamos suponiendo que el VS no tiene out,
// los vértices no traen asociados atributos, solo las coordenadas
uniform mat4 modelViewProjMat; // para pasar a Clip-Space
const float VD = 50; // longitud del desplazamiento

uniform float time;

in vec2 vUv0[];                 // in del geometry shader
in vec3 viewVertex[];
in vec3 viewNormal[];

out vec2 vUv0Out;                 // out del geometry shader
out vec3 viewVertexOut;
out vec3 viewNormalOut;


vec3 normalVec(vec3 v[3])
 { 
    vec3 normal= normalize(cross ((v[2]-v[1]),(v[0]-v[1])));
    return normal;
  } // vector normal al triángulo

vec3 baricentro(vec3 v[3]){
   vec3 baric = normalize((v[0] + v[1] + v[2]) / 3);
   return baric;
}

void main() 
{
vec3 vertices[3] = vec3[]
(gl_in[0].gl_Position.xyz,
 gl_in[1].gl_Position.xyz,
 gl_in[2].gl_Position.xyz );

//vec3 dir = normalVec (vertices); // para los 3 vértices sacando la normal del triangulo
vec3 dir = baricentro(vertices); // para los 3 vértices sacando el baricentro del triangulo
for (int i=0; i<3; ++i)
    { // para emitir 3 vértices

         vUv0Out=vUv0[i];               
         viewVertexOut=viewVertex[i];
         viewNormalOut=viewNormal[i];
         
        vec3 posDes = vertices[i] + dir * (VD* (time* 0.8 + 0.75));

        vec3 giro;
        giro.x = posDes.x * (cos(time)) + posDes.z * (-sin(time));
        giro.y = posDes.y;
        giro.z = posDes.x * (sin(time)) + posDes.z * (cos(time));
        
        // vértice desplazado (los 3 en la misma dirección)
        gl_Position = modelViewProjMat * vec4(giro,1.0);
        // paso a Clip-Space
        EmitVertex(); // al no declarar ninguna variable out, los vertices del
        // triángulo emitido no llevan asociados atributos, solo las coordenadas
    }
   EndPrimitive();
}