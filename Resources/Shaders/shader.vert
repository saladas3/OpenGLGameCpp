#version 330 core

// This represents the verices we are working with (the vertex aka point data aka coordinates)
layout (location = 0) in vec3 aPos;

void main() {
    // gl_Position is the value that will be passed to the next step of the graphics pipeline.
    gl_Position = vec4(aPos, 1.0);
}
