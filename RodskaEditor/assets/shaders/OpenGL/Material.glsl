#type vertex
#version 330 core
layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec3 a_Normal;
uniform mat3 u_NormMat;
uniform mat4 u_ViewProjection;
uniform mat4 u_Transform;
out vec3 v_Position;
out vec3 v_Normal;
out vec3 fPos;  
void main()
{
	v_Position = vec3(u_Transform * vec4(a_Position, 1.0));
	gl_Position =  u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
	v_Normal =  u_NormMat * a_Normal;  

}
#type fragment
#version 330 core
layout(location = 0) out vec4 color;			
uniform vec4 u_Color;
uniform vec4 u_LightColor;
uniform vec3 u_LightPos;  
in vec3 v_Position;
in vec3 v_Normal;  

void main()
{
	vec3 norm = normalize(v_Normal);
	vec3 lightDir = normalize(u_LightPos - v_Position);  
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diff * vec3(u_LightColor.x,u_LightColor.y,u_LightColor.z);

	float emissive = 0.8;
	vec3 ambient = emissive * vec3(u_LightColor.x,u_LightColor.y,u_LightColor.z);
	vec3 result = (ambient + diffuse) * vec3(u_Color.x,u_Color.y,u_Color.z);

	color = vec4(result, 1.0);
}