#type vertex
#version 330 core
layout (location=0) in vec3 a_Position;
layout (location=1) in vec2 a_TexCoord;


out vec2 outTexCoord;

uniform mat4 u_Transform;
uniform mat4 u_ViewProjection;

uniform float texXOffset;
uniform float texYOffset;
uniform int numCols;
uniform int numRows;

void main()
{
    gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
    float x = (a_TexCoord.x / numCols + texXOffset);
    float y = (a_TexCoord.y / numRows + texYOffset);

    outTexCoord = vec2(x, y);
}


#type fragment
#version 330 core
layout(location = 0) out vec4 fragColor;

in vec2 outTexCoord;

uniform sampler2D texture_sampler;

void main()
{
    fragColor = texture(texture_sampler, outTexCoord);
}