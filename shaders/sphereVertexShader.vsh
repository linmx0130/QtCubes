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
