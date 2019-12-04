#version 330
layout(location = 0) in vec3 posVertex;
layout(location = 1) in vec3 colorVertex;
layout(location = 2) in vec2 coordVertex;
uniform mat4 MVP;
out vec3 col;
out vec2 texCoord;
void main() {
   col = colorVertex;
   gl_Position = MVP * vec4(posVertex, 1);
   texCoord = coordVertex;
}
