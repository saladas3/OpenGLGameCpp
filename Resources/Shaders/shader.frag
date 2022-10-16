#version 330 core

// What we expect to output on the screen (information from the CPU or w/e)
out vec4 FragColor;
// The name needs to be the same as in vertex shader
in vec3 color;
in vec2 texCoord;

uniform sampler2D tex0;

void main() {
    FragColor = texture(tex0, texCoord);
}
