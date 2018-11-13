#version 430 core


in vec2 TexCoord;

out vec4 fragColor;

uniform sampler2D ourTexture1;


void main(void)
{
	fragColor = texture(ourTexture1, TexCoord);
	


}
