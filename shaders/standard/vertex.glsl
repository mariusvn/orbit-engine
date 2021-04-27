#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 texCoord;
layout (location = 3) in vec3 tangent;
layout (location = 4) in vec3 bitangent;

out vec2 TexCoord;
uniform mat4 transform;

void main() {
    gl_Position = transform * vec4(position, 1.0);
    TexCoord = texCoord;
}
