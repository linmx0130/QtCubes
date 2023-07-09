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
