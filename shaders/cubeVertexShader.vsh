/*
 * cubeVertexShader.vsh
 * Vertex shader of the cube model.
 * 
 * Copyright (c) Mengxiao Lin <linmx0130@gmail.com>
 * All rights reserved.
 *
 * This source code is licensed under the BSD license found in the
 * LICENSE file in the root directory of this source tree.
 */
 
#version 330
layout(location = 0) in vec3 posVertex;
layout(location = 1) in vec3 normalVertex;
layout(location = 2) in vec2 coordVertex;
uniform mat4 projectMat;
uniform mat4 viewMat;
uniform mat4 modelMat;
out vec2 texCoord;
out vec3 normalVec;
out vec3 fragPosition;
void main() {
   gl_Position = projectMat * viewMat * modelMat * vec4(posVertex, 1);
   fragPosition = vec3(viewMat * modelMat * vec4(posVertex, 1));
   texCoord = coordVertex;
   normalVec = vec3(modelMat * vec4(normalVertex, 1));
}
