#type vertex
#version 330 core
layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec3 a_Normal;
layout(location = 2) in vec2 texCoord;

uniform mat4 u_ViewProjection;
uniform mat4 u_Transform;
uniform mat4 u_View;
uniform mat4 u_Projection;
uniform mat3 u_NormMat;

out vec3 v_Position;
out vec3 v_Normal;
out vec2 outTexCoord;


void main()
{
	v_Position =   vec3(u_Transform * vec4(a_Position, 1.0));
    gl_Position = u_Projection * u_View * vec4(v_Position, 1.0);
	v_Normal =  u_NormMat * a_Normal;  
    outTexCoord = texCoord;
}

#type fragment
#version 330 core
out vec4 fragColor;

in vec3 v_Position;
in vec3 v_Normal;  
in vec2 outTexCoord;

struct Attenuation
{
    float constant;
    float linear;
    float exponent;
};

struct PointLight
{
    vec3 colour;
    vec3 position;
    float intensity;
    Attenuation att;
};

struct Material {
	vec4 ambient;
	vec4 diffuse;
	vec4 specular;
	int hasTexture;
	float reflectance;
};

uniform vec3 ambientLight;
uniform float specularPower;
uniform Material material;
uniform PointLight pointLight;
uniform vec3 u_ViewPos;

vec3 ambientC;
vec3 diffuseC;
vec3 speculrC;





void main()
{
        float specularStrength = 0.5;
        float ambientStrength = 0.1;
        ambientC = material.ambient.xyz * ambientStrength;
        diffuseC = material.diffuse.xyz;
        speculrC = material.specular.xyz;

    vec3 normal2 = normalize(v_Normal);
   
    vec3 to_light_source  = normalize(pointLight.position - v_Position);
    float diffuseFactor = max(dot(normal2, to_light_source ), 0.0);
    vec3 diffuseColour = (pointLight.colour * diffuseFactor);
    vec3 viewDir = normalize(u_ViewPos - v_Position);
    vec3 reflectDir = reflect(-to_light_source, viewDir);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32 * material.reflectance);
    vec3 specular = specularStrength * spec * pointLight.colour; 

    vec3 result = (ambientC + diffuseColour + specular) * (diffuseC * diffuseFactor);
    fragColor = vec4(result, 1.0);
}