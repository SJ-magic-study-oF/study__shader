/************************************************************
Geometry shader input/output 指定
ジオメトリシェーダで使う組み込み変数＆関数
	http://miffysora.wikidot.com/geometry-shader
************************************************************/
#version 120
#extension GL_ARB_texture_rectangle : enable
#extension GL_EXT_gpu_shader4 : enable

//Add this for using geometry shader
#extension GL_EXT_geometry_shader4 : enable

/************************************************************
************************************************************/
uniform float b_sw;
uniform float TextureImageSize = 300; // assume that texture is square.


/************************************************************
************************************************************/
/******************************
******************************/
void main() {
	/********************
	********************/
	vec2 p[4];
	for(int i = 0; i < 4; i++){
		p[i] = gl_PositionIn[i].xy;
	}
	
	/********************
	********************/
	vec2 center;
	center.x = (p[0].x + p[1].x + p[2].x + p[3].x) / 4;
	center.y = (p[0].y + p[1].y + p[2].y + p[3].y) / 4;
	
	vec2 delta;
	
	if(b_sw == 1.0){
		for(int i = 0; i < 4; i++){
			vec2 delta = p[i] - center;
			delta *= 1.2;
			p[i] = center + delta;
		}
	}
	
	/********************
	1---3
	|   |
	0---2
	********************/
	// const int TextureImageSize = 100;
	vec4 t[4];
	t[0] = vec4(0, TextureImageSize, 0, 1);
	t[1] = vec4(0, 0, 0, 1);
	t[2] = vec4(TextureImageSize, TextureImageSize, 0, 1);
	t[3] = vec4(TextureImageSize, 0, 0, 1);
	
	/********************
	********************/
	vec4 color = vec4(0.0, 1.0, 0.0, 1.0);
	for(int i = 0; i < 4; i++){
		gl_Position = gl_ModelViewProjectionMatrix * vec4(p[i], 0.0, 1.0);
		
		gl_FrontColor = gl_FrontColorIn[i];
		gl_TexCoord[0] = t[i];
		
		EmitVertex();
	}
	
	EndPrimitive();
}


