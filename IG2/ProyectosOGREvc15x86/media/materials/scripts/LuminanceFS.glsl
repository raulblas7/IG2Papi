#version 330 core // archivo LuminancePS.glsl

in vec2 vUv0;           //coordenadas de textura
uniform sampler2D RTT0; // textura con la escena
out vec4 fFragColor;
// weight vector for luminance (de suma 1)
const vec3 WsRGB = vec3(0.2125, 0.7154, 0.0721);

void main() {
    vec4 sceneColor = texture(RTT0, vUv0);
    float lum = dot(vec3(sceneColor), WsRGB);
    fFragColor = vec4(lum, lum, lum, sceneColor.a);
}