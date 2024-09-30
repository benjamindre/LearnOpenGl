#version 330
struct Material
{
    sampler2D emission;
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
};

struct Light
{
    vec3 position;
    vec3 direction;
    float cutOff;
    float outerCutOff;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float constant;
    float linear;
    float quadratic;
};

out vec4 fragColor;

in vec2 BoxTexCoord;
in vec3 BoxNormal;
in vec3 FragPos;

uniform vec3 CameraPos;
uniform sampler2D TextureImage;
uniform Material BoxMaterial;
uniform Light BoxLight;

void main()
{
    vec3 lightDir = normalize(BoxLight.position - FragPos);

    float theta = dot(lightDir, normalize(-BoxLight.direction));
    float epsilon   = BoxLight.cutOff - BoxLight.outerCutOff;
    float intensity = clamp((theta - BoxLight.outerCutOff) / epsilon, 0.0, 1.0);

//    float distance = length(BoxLight.position - FragPos);
//    float attenuation = 1.0 / (BoxLight.constant + BoxLight.linear * distance + BoxLight.quadratic * (distance * distance));

    // 环境光
    vec3 environment = vec3(texture(BoxMaterial.diffuse, BoxTexCoord)) * BoxLight.ambient;

    // 漫反射光
    vec3 norm = normalize(BoxNormal);

    float diff = max(dot(norm, lightDir), 0.0f);
    vec3 diffuse = BoxLight.diffuse * vec3(texture(BoxMaterial.diffuse, BoxTexCoord)) * diff;

    // 镜面光
    vec3 viewDir = normalize(CameraPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0f), BoxMaterial.shininess);
    vec3 specular = vec3(texture(BoxMaterial.specular, BoxTexCoord)) * spec * BoxLight.specular;

    diffuse *= intensity;
    specular *= intensity;

    float distance = length(BoxLight.position - FragPos);
    float attenuation = 1.0 / (BoxLight.constant + BoxLight.linear * distance + BoxLight.quadratic * (distance * distance));

    fragColor = vec4(environment * attenuation + diffuse * attenuation + specular * attenuation, 1.0f);
}