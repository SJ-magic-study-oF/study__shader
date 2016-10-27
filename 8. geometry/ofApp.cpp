#include "ofApp.h"

/******************************
******************************/
ofApp::ofApp()
: color(0, 0, 255)
{
}

//--------------------------------------------------------------
void ofApp::setup(){
	
	/********************
	setGeometryInputType(), setGeometryOutputType()に指定可能なtypeは決まっている。
		http://openframeworks.cc/documentation/gl/ofShader/#show_setGeometryOutputType
		
	入力は、単に１入力プリミティブあたりに何個の頂点を送るか、だけと考えて良い。
		http://miffysora.wikidot.com/geometry-shader
		
	並べた順にshaderに渡される。
	
	outputは、「typeと順番」で描画内容が変わってくるので注意してoutputする。
	inputの時に、混乱なきよう、順序を考慮しておくのが良い。
		http://openframeworks.cc/documentation/gl/ofVbo/
	********************/
	//Enable detailed logging of openFrameworks messages in console
	ofSetLogLevel( OF_LOG_VERBOSE );

	//We must to specify geometry shader parameters before loading shader
	shader.setGeometryInputType( GL_LINES_ADJACENCY_EXT );
	shader.setGeometryOutputType( GL_TRIANGLE_STRIP );
	
	/********************
	ofVboでは、vbo.draw();で一気に描画コマンドを投げるが、shaderでは、setGeometryInputType()で指定した単位でgeometryが渡される。
	geometryが渡される度、geometry shaderが走る。
	shader:mainにて、EndPrimitiveにより、その回で出力するoutput geometryを終了。
	この、「その回で出力するgeometry」にてoutputするverticesをここで指定。
	********************/
	shader.setGeometryOutputCount( 4 );	//Maximal possible number of output vertices

	//Load shader
	shader.load( "shaderVert.c", "shaderFrag.c", "shaderGeom.c" );

	//printf("Maximum number of output vertices support is: %i\n", shader.getGeometryMaxOutputCount());
	
	/********************
	********************/
	ofSetVerticalSync(false);
	ofSetFrameRate(60);
	
	ofBackground(0);
	ofEnableDepthTest();
	ofEnableBlendMode(OF_BLENDMODE_ADD);
	
	/********************
	1---3
	|   |
	0---2
	********************/
	Verts[0].set( ofVec3f(100, 200) );
	Verts[1].set( ofVec3f(100, 100) );
	Verts[2].set( ofVec3f(200, 200) );
	Verts[3].set( ofVec3f(200, 100) );
	Verts[4].set( ofVec3f(300, 200) );
	Verts[5].set( ofVec3f(300, 100) );
	Verts[6].set( ofVec3f(400, 200) );
	Verts[7].set( ofVec3f(400, 100) );
	Verts[8].set( ofVec3f(100, 400) );
	Verts[9].set( ofVec3f(100, 300) );
	Verts[10].set( ofVec3f(200, 400) );
	Verts[11].set( ofVec3f(200, 300) );
	Verts[12].set( ofVec3f(300, 400) );
	Verts[13].set( ofVec3f(300, 300) );
	Verts[14].set( ofVec3f(400, 400) );
	Verts[15].set( ofVec3f(400, 300) );
	
	
	for(int i = 0; i < NUM_VERTS; i++ ){
		// Color[i].set(0.0, 0.3, 1.0, 1.0);
		Color[i].set(double(color.r)/255, double(color.g)/255, double(color.b)/255, double(color.a)/255);
	}
	
	Vbo.setVertexData(Verts, NUM_VERTS, GL_DYNAMIC_DRAW);
	Vbo.setColorData(Color, NUM_VERTS, GL_DYNAMIC_DRAW);
	
	/********************
	********************/
	image.loadImage( "img.png" );	
	fbo.allocate( image.getWidth(), image.getHeight() );
	
	/********************
	********************/
	b_sw = false;
}

//--------------------------------------------------------------
void ofApp::update(){
	for(int i = 0; i < NUM_VERTS; i++ ){
		// Color[i].set(0.0, 0.3, 1.0, 1.0);
		Color[i].set(double(color.r)/255, double(color.g)/255, double(color.b)/255, double(color.a)/255);
	}
	Vbo.updateColorData(Color, NUM_VERTS);
}

//--------------------------------------------------------------
void ofApp::draw(){
	/********************
	********************/
	fbo.begin();		
	ofBackground( 0, 0, 0 );
	ofSetColor( 255, 255, 255 );
	image.draw( 0, 0 );
	fbo.end();			
	
	/********************
	********************/
	ofEnableAlphaBlending();		

	/********************
	********************/
	// cam.begin();
	shader.begin();
	shader.setUniform1f( "b_sw", b_sw );
	shader.setUniform1f( "TextureImageSize", image.getWidth() );
	shader.setUniformTexture( "texture1", fbo.getTextureReference(), 1 ); 

	Vbo.draw(GL_LINES_ADJACENCY_EXT, 0, NUM_VERTS);
	shader.end();
	// cam.end();
	
	/*
	string info;
	info = "vertex num = " + ofToString(WIDTH * HEIGHT, 0) + "\n";
	info += "FPS = " + ofToString(ofGetFrameRate(), 2);
	ofDrawBitmapString(info, 30, 30);
	*/
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	switch(key){
		case 't':
			b_sw = !b_sw;
			break;
			
		case 'r':
			color.set(255, 0, 0, 255);
			break;
			
		case 'g':
			color.set(0, 255, 0, 255);
			break;
			
		case 'b':
			color.set(0, 0, 255, 255);
			break;
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
