/* 
 * sphereFragmentShader.fsh
 * This is the fragment shader for the sphere model.
 *
 * Copyright (c) Mengxiao Lin <linmx0130@gmail.com>
 * All rights reserved.
 *
 * This source code is licensed under the BSD license found in the
 * LICENSE file in the root directory of this source tree.
 */
uniform vec3 lightPos;
varying vec3 normalVec;
varying vec3 fragPosition;

void main(void)
{
    vec3 lightColor = vec3(1.0f, 1.0f, 1.0f);
    vec3 norm = normalize(normalVec);
    vec3 lightDir = normalize(lightPos - fragPosition);
    float diff = max(dot(norm, lightPos), 0.0f);
    float ambientStrength = 0.4f;
    vec3 result = (ambientStrength + diff * 0.6f) * lightColor;
    gl_FragColor = vec4(result, 1.0f);
}
