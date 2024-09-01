#version 330
layout (location = 0) in vec3 vertPos;
layout (location = 1) in vec3 vertNormal;
layout (location = 2) in vec2 vertTexCoord;


uniform mat4 Projection;
uniform mat4 View;
uniform mat4 Model;

out vec2 TexCoord;

void main()
{
    gl_Position = Projection * View * Model * vec4(vertPos, 1.0f);
    TexCoord = vertTexCoord;
}