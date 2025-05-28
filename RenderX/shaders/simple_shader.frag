#version 450
 
layout (location = 0) in vec3 fragColor;
layout (location = 0) out vec4 outColor;

layout(push_constant) uniform Push {
	mat4 transform;
	vec3 color;
} push; // order here must match the order specified in the SimplePushConstantData struct 

void main() {
	outColor = vec4(fragColor, 1.0);
	// the last parameter corresponds to opecity, the first one (three) parameter(s) is (are) rgb
}