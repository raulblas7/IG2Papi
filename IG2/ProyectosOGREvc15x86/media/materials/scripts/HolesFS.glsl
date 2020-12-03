#version 330 core


in vec2 vUv0; // out del vertex shader
in vec3 Normal;


uniform sampler2D textura1; // tipo sampler2D para texturas 2D

uniform vec3 color_front;   // color del que se pintara la parte de fuera
uniform vec3 color_back;    // color del que se pintara la parte de dentro


uniform vec4 lightPos;      // direccion de la luz (considerada como vector)
uniform vec4 intLuz;        // intensidad de luz

out vec4 fFragColor; // out del fragment shader

void main() {
	vec3 color = vec3(texture(textura1, vUv0));
	 if(color.x > 0.5) discard;         // si el texel cumple esta caracteristica, salimos y no se pinta (como un return)
 
 
 if(gl_FrontFacing){ 
	vec3 norm = -normalize(Normal);
	 vec3 lightDir = normalize(vec3(lightPos));
        float diff = max(dot(norm, lightDir), 0.0);
        vec3 diffuse = vec3(intLuz) * diff;
    fFragColor = vec4(color_front*color *diffuse , 1.0);
 }
 else
  {
	vec3  norm = normalize(Normal);
	  vec3 lightDir = normalize(vec3(lightPos));
        float diff = max(dot(norm, lightDir), 0.0);
        vec3 diffuse = vec3(intLuz) * diff;
      // fFragColor = vec4(color_front*color , 1.0);
	    fFragColor = vec4(color_back*color , 1.0);

  }

       


}