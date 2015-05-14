#version 330 core

layout(location = 0) in vec3 vertex;
layout(location = 1) in vec3 vertexColor;

uniform mat4 mvpMatrix;

out vec4 fragColor;

void main() {
	gl_Position = mvpMatrix * vec4(vertex, 1);
	//fragColor = vec4(clamp(vertex, 0.0, 1.0), 1.0);
	fragColor = vec4(vertexColor, 1.0);
}

