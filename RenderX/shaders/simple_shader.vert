// 450 corresponds to glsl version 4.5
#version 450

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 color;
layout(location = 2) in vec3 normal;
layout(location = 3) in vec2 uv;

layout(location = 0) out vec3 fragColor;
layout(location = 1) out vec3 fragPosWorld; // need this to calculate the direction to the light source for each fragment
layout(location = 2) out vec3 fragNormalWorld; // will also be interpolated for the fragment shader

layout(set = 0, binding = 0) uniform GlobalUbo {
	mat4 projectionViewMatrix;
	vec4 ambientLightColor; // w is light intensity
	vec3 lightPosition;
	vec4 lightColor;
} ubo;

layout(push_constant) uniform Push {
	mat4 modelMatrix;
	mat4 normalMatrix;
} push; // order here must match the order specified in the SimplePushConstantData struct

void main() {
	vec4 positionWorld = push.modelMatrix * vec4(position, 1.0);
	gl_Position = ubo.projectionViewMatrix * push.modelMatrix * vec4(position, 1.0);

	fragNormalWorld = normalize(mat3(push.normalMatrix) * normal);
	fragPosWorld = positionWorld.xyz;
	fragColor = color;
}