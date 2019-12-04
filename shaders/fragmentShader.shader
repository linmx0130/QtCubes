#version 330
in vec3 col;
in vec2 texCoord;
out vec4 fragColor;
uniform sampler2D ourTexture;
void main() {
   fragColor = texture(ourTexture, texCoord) * vec4(col, 1.0f);
}
