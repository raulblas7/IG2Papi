#version 330 core

uniform sampler2D textura1; //textura1 de la boya
uniform sampler2D textura2; //textura2

uniform vec4 OutColor;
uniform vec4 InColor;

uniform vec4 lightPos;
uniform vec3 lightAmbient;
uniform vec3 lightDiffuse;
uniform vec3 materialDiffuse;
uniform float Flipping;

in vec2 vUv0;
in vec3 viewNormal;
in vec3 viewVertex;

out vec4 fFragColor;

float diff(vec3 cVertex, vec3 cNormal) {
	vec3 lightDir = lightPos.xyz;

	if (lightPos.w == 1) {
		lightDir = lightPos.xyz - cVertex;
	}

	return max(dot(cNormal, normalize(lightDir)), 0.0);
}

void main() {
	vec3 color = vec3(texture(textura1, vUv0));
	vec3 color2 = vec3(texture(textura2, vUv0));

	

	if (color.x > 0.6) { discard; }

	vec3 ambient = lightAmbient * materialDiffuse;

	vec3 diffuse = diff(viewVertex, viewNormal) * lightDiffuse * materialDiffuse;
	vec3 vFrontColor = ambient + diffuse;

	diffuse = diff(viewVertex, -viewNormal) * lightDiffuse * materialDiffuse;
	vec3 vBackColor = ambient + diffuse;

	bool frontFacing = (Flipping > -1) ? gl_FrontFacing : !gl_FrontFacing;

	vec3 col;

	if (frontFacing) { col = vFrontColor * color2 * vec3(OutColor); }
	else { col = vBackColor * color * vec3(InColor); }
    

	fFragColor = vec4(col, 1.0);
}