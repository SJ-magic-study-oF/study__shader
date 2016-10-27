/******************************
******************************/
#version 120
#extension GL_ARB_texture_rectangle : enable
#extension GL_EXT_gpu_shader4 : enable


/******************************
******************************/
// uniform sampler2DRect texture0;
uniform sampler2DRect texture1;


/******************************
******************************/
void main(){
	vec2 pos = gl_TexCoord[0].st;
	vec4 color = texture2DRect(texture1, pos);
	
	gl_FragColor = color * gl_Color;
	// gl_FragColor = gl_Color;
}
