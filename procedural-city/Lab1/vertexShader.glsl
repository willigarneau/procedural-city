#version 430 core    
                      
layout(location = 0) in vec3 in_sommet; 
layout(location = 1) in vec3 in_color;
layout(location = 2) in vec2 texCoord;

uniform mat4 gVue;
uniform mat4 gModele;
uniform mat4 gProjection;


out vec4 Color;
out vec2 TexCoord;

void main()
{
  gl_Position = gProjection * gVue * gModele * vec4(in_sommet,1.0);
	TexCoord = vec2(texCoord.x, 1.0 - texCoord.y);
	Color = vec4(in_color,1.0);
}
