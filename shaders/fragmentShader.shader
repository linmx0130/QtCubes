#version 330
in vec2 texCoord;
in vec3 normalVec;
in vec3 fragPosition;
out vec4 fragColor;

uniform sampler2D ourTexture;
uniform vec3 lightPos;

void main() {
   vec3 norm = normalize(normalVec);
   vec3 lightDir = normalize(lightPos - fragPosition);
   vec3 lightColor = vec3(1.0f, 1.0f, 1.0f);
   float diff = max(dot(norm, lightPos), 0.0f);
   float ambientStrength = 0.4f;
   vec3 result = (ambientStrength + diff * 0.6f) * lightColor;
   fragColor = texture(ourTexture, texCoord) * vec4(result, 1.0f);
}
