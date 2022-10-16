#version 330 core

// This represents the verices we are working with (the vertex aka point data aka coordinates)
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTex;

out vec3 color;
out vec2 texCoord;
uniform float scale;

void main() {
    // gl_Position is the value that will be passed to the next step of the graphics pipeline. The name MUST be gl_Position
    gl_Position = vec4(aPos.x + aPos.x * scale, aPos.y + aPos.y * scale, aPos.z + aPos.z * scale, 1.0);
    color = aColor;
    texCoord = aTex;
}
