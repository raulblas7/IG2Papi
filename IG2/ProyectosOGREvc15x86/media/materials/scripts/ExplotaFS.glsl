#version 330 core // archivo ExplotaFS.glsl
uniform sampler2D textura1; //textura1 de la boya
uniform sampler2D textura2; //textura2
out vec4 fFragColor;


uniform vec4 lightPos;
uniform vec3 lightAmbient;
uniform vec3 lightDiffuse;
uniform vec3 materialDiffuse;

in vec2 vUv0Out;                 // out del geometry shader
in vec3 viewVertexOut;
in vec3 viewNormalOut;

uniform float Flipping;

float diff(vec3 cVertex, vec3 cNormal) {
	vec3 lightDir = lightPos.xyz;

	if (lightPos.w == 1) {
		lightDir = lightPos.xyz - cVertex;
	}

	return max(dot(cNormal, normalize(lightDir)), 0.0);
}
void main() {
  vec3 color = vec3(texture(textura1, vUv0Out));
vec3 color2 = vec3(texture(textura2, vUv0Out));

	vec3 ambient = lightAmbient * materialDiffuse;

	vec3 diffuse = diff(viewVertexOut, viewNormalOut) * lightDiffuse * materialDiffuse;
	vec3 vFrontColor = ambient + diffuse;

	diffuse = diff(viewVertexOut, -viewNormalOut) * lightDiffuse * materialDiffuse;
	vec3 vBackColor = ambient + diffuse;

	bool frontFacing = (Flipping > -1) ? gl_FrontFacing : !gl_FrontFacing;

	

	vec3 col;

	if (frontFacing) { col =vFrontColor*   color2; }
	else { col = vBackColor* color  ;}
    

	fFragColor = vec4(col, 1.0);
}