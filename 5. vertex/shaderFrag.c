#version 120
#extension GL_ARB_texture_rectangle : enable
#extension GL_EXT_gpu_shader4 : enable

void main(){
	/********************
	lightingなどは考慮されていない.
	ofSetColor();
	の色がそのまま渡される.
	********************/
	gl_FragColor = gl_Color;
}
