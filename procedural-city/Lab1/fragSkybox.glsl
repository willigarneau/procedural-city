#version 430 core

in vec3 TexCoord;

out vec4 fragColor;

uniform samplerCube Skybox;


void main(void)
{
	fragColor = texture(Skybox, TexCoord);



}
