#version 460 core

out vec4 FragColor;

in vec3 WorldPos;

uniform vec3 lightPos = vec3(3,3,3);
uniform vec3 viewPos  = vec3(0,0,3);

void main()
{
    vec3 color = vec3(0.2,0.6,1.0);

    vec3 normal = normalize(WorldPos);
    vec3 lightDir = normalize(lightPos - WorldPos);

    // Diffuse
    float diff = max(dot(normal,lightDir),0.0);

    // Specular
    vec3 viewDir = normalize(viewPos - WorldPos);
    vec3 reflectDir = reflect(-lightDir,normal);

    float spec = pow(max(dot(viewDir,reflectDir),0.0),64);

    vec3 result =
        color * diff +
        vec3(1.0)*spec +
        color*0.1;

    FragColor = vec4(result,1.0);
}
