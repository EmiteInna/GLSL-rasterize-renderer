#version 330 core
layout (location=0) in vec4 position;
layout (location=1) in vec4 texcoord;
layout (location=2) in vec4 normal;
layout (location=3) in vec4 tangent;
layout (location=4) in vec4 color;
out vec4 vertexColor;
out vec4 uv;
out vec4 normalWS;
out vec4 tangentWS;
out vec4 positionWS;

uniform float warpper;
uniform mat4 M;
uniform mat4 V;
uniform mat4 P;
uniform vec3 lightDirection;
uniform vec3 lightColor;
void main()
{
   vec4 positionOS=vec4(position.xyz,1.0);
   positionWS=M*positionOS;
   vec4 positionVS=V*positionWS;
   vec4 positionHCS=P*positionVS;
   gl_Position=positionHCS;
   
   mat3 M_IT=mat3(transpose(inverse(M)));

   vertexColor=color;
   uv=texcoord;
   normalWS=vec4(normalize(M_IT*normal.xyz),0);
   tangentWS=vec4(normalize(M_IT*tangent.xyz),0);
}