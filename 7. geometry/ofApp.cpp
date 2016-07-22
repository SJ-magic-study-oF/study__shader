#include "ofApp.h"

ofImage image;

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
	
	shader.setGeometryOutputCount( 128 );	//Maximal possible number of output vertices

	//Load shader
	shader.load( "shaderVert.c", "shaderFrag.c", "shaderGeom.c" );

	//printf("Maximum number of output vertices support is: %i\n", shader.getGeometryMaxOutputCount());
	
	/********************
	********************/
	ofSetVerticalSync(false);
	
	ofBackground(0);
	ofEnableDepthTest();
	ofEnableBlendMode(OF_BLENDMODE_ADD);
	
	float size = 100;
	ofVec3f point0(-size/2, size/2);
	ofVec3f point1(-size/2, -size/2);
	ofVec3f point2(size/2, size/2);
	ofVec3f point3(size/2, -size/2);
	
	Verts[0].set(point0);
	Verts[1].set(point1);
	Verts[2].set(point2);
	Verts[3].set(point3);
	
	/*
	Color[0].set(1.0, 1.0, 0.0, 1.0);
	Color[1].set(Color[0]);
	Color[2].set(Color[0]);
	Color[3].set(Color[0]);
	/*/
	Color[0].set(1.0, 0.0, 0.0, 1.0);
	Color[1].set(0.0, 1.0, 0.0, 1.0);
	Color[2].set(0.0, 0.0, 1.0, 1.0);
	Color[3].set(1.0, 1.0, 0.0, 1.0);
	//*/
	
	Vbo.setVertexData(Verts, NUM_VERTS, GL_DYNAMIC_DRAW);
	Vbo.setColorData(Color, NUM_VERTS, GL_DYNAMIC_DRAW);
	
	/********************
	********************/
	b_sw = false;
}

//--------------------------------------------------------------
void ofApp::update(){
}

//--------------------------------------------------------------
void ofApp::draw(){

	// ofSetHexColor(0xffffff);
	ofSetColor(255, 0, 255, 255);
	
	cam.begin();
	shader.begin();
	shader.setUniform1f( "b_sw", b_sw );

	Vbo.draw(GL_LINES_ADJACENCY_EXT, 0, NUM_VERTS);
	shader.end();
	cam.end();
	
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
