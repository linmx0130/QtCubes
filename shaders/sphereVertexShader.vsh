/* 
 * sphereVertexShader.vsh
 * This is the vertex shader for the sphere model.
 *
 * Copyright (c) Mengxiao Lin <linmx0130@gmail.com>
 * All rights reserved.
 *
 * This source code is licensed under the BSD license found in the
 * LICENSE file in the root directory of this source tree.
 */
attribute vec3 posVertex;
uniform mat4 projectMat;
uniform mat4 viewMat;
uniform mat4 modelMat;

varying vec3 normalVec;
varying vec3 fragPosition;

void main(void)
{
    gl_Position = projectMat * viewMat * modelMat * vec4(posVertex, 1);
    fragPosition = vec3(viewMat * modelMat * vec4(posVertex, 1));
    normalVec = vec3(modelMat * vec4(posVertex, 1));
}
