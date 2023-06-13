#version 330 core
layout (location=0) in vec4 position;
layout (location=1) in vec4 texcoord;
out vec4 vertexColor;
out vec4 uv;
uniform float warpper;
uniform mat4 M;
uniform mat4 V;
uniform mat4 P;
void main()
{
   vec4 positionOS=vec4(position.xyz,1.0);
   vec4 positionWS=M*positionOS;
   vec4 positionVS=V*positionWS;
   vec4 positionHCS=P*positionVS;
   gl_Position=positionHCS;
   vertexColor=vec4(position.xyz,1.0);
   uv=texcoord;
}