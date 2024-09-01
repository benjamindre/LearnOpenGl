#version 330
layout (location = 0) in vec3 vertPosition;
layout (location = 1) in vec3 vertNormal;
layout (location = 2) in vec2 vertTexture;

uniform mat4 BoxProjection;
uniform mat4 BoxView;
uniform mat4 BoxModel;

out vec2 BoxTexCoord;
out vec3 BoxNormal;
out vec3 FragPos;

void main()
{
    gl_Position = BoxProjection * BoxView * BoxModel * vec4(vertPosition, 1.0);

    BoxTexCoord = vertTexture;
    BoxNormal = vertNormal;
    FragPos = vec3(BoxView * BoxModel * vec4(vertPosition, 1.0f));
}
