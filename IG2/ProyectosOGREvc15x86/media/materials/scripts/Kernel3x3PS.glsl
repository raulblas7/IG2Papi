#version 330 core // archivo Kernel3x3PS.glsl

uniform sampler2D RTT0; // textura con la escena
out vec4 fFragColor;
in vec2 vUv0;           //coordenadas de textura


uniform float kernel[9];
    
void main()
{
    ivec2 texSize = textureSize(RTT0, 0);
    float incS = 1. / float(texSize.s);
    float incT = 1. / float(texSize.t);
   vec2 incUV[9] = vec2[]
    ( // incrementos para acceder a
    vec2(-incS, incT), // top‐left
    vec2(-incS, 0) , // top‐center
    vec2(-incS, -incT) , // top‐right
    vec2(0, incT) , // center‐left
    vec2(0, 0) , // center‐center
    vec2(0, -incT) , // center‐right
    vec2( incS, incT) , // bottom‐left
    vec2( incS, 0) , // bottom‐center
    vec2( incS, -incT) // bottom‐right 
    );
    

    vec3 color = vec3(0.0);

   for(int i = 0; i < 9; i++) {
      //  color += kernel[i] + incUV[i]; 
      color +=  vec3(   kernel[i] * texture(RTT0,vUv0+incUV[i])); 
       
        
    }
    fFragColor = vec4(color, 1.0);
}