#version 430 core    
                      
layout(location = 0) in vec3 in_sommet; 


uniform mat4 gVue;
uniform mat4 gProjection;

out vec3 TexCoord;

void main()
{
	vec4 pos = gProjection * gVue * vec4(in_sommet,1.0);
	gl_Position = pos.xyww;
	TexCoord = normalize(in_sommet);
}
