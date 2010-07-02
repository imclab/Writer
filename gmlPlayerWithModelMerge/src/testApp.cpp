#include "testApp.h"

float tagScale = 6.0;

//--------------------------------------------------------------
void testApp::setup(){
	panel.setup("panel", 0, 0, 340, 700);
	panel.addPanel("gml lister", 4);
	
	lister.allowExt("gml");
	lister.listDir("gml/");
	panel.addFileLister("gml lister", &lister, 280, 200);

	panel.addToggle("restart tag", "restart", false);
	panel.addSlider("drawSpeed", "drawSpeed", 0.001, 0.00001, 0.01, false);

	panel.addSlider("shiftX", "shiftX", 0, -400.0, 400.0, false);
	panel.addSlider("shiftY", "shiftY", 0, -400.0, 400.0, false);
	panel.addSlider("rotate 3D", "rotate", 0, -360.0, 360.0, false);
	panel.addChartPlotter("drawPct", guiStatVarPointer("drawPct", &drawPct, GUI_VAR_FLOAT, true, 2), 200, 100, 200, -0.2, 2.0);

	panel.loadSettings("panel.xml");

	drawPct = 0.0;
	
	ofSetVerticalSync(true);
	
	loadNewTag(lister.getPath(0));
	

	ofSetFrameRate( 60.0f ) ;

	ofxVec3f start_eye_pos( 0, 2.0, 15 );
	util_3d.setup( start_eye_pos );
	
	
	z = 0;
	
	tagger.setup();
	tagger.setOtherArmTarget( ofxVec3f(-1.0, -1.5, 2.0) );	
		
	shiftX = 0.0;
}

//--------------------------------------------------------------
void testApp::loadNewTag(string path){
	loadGml(path, tag, true);
	startOffset = ofPoint(0.18 + tag.getFirstPoint().x, -1.0+tag.getFirstPoint().y, 0);
	startOffset *= tagScale;
	drawPct = 0.0;
	tag.setPct(drawPct);
	panel.setValueB("restart", false);	
	printf("LOAD NEW TAG\n");
}

//--------------------------------------------------------------
void testApp::update(){
	panel.update();
	
	if( panel.getValueB("restart") ){
		drawPct = 0.0;
		tag.setPct(0);		
		tagger.setRootPosition(ofxVec3f());
		panel.setValueB("restart", false);
	}

	tagger.update( ofGetLastFrameTime() );
	
	if( lister.selectedHasChanged() ){
		loadNewTag(lister.getSelectedPath());
		lister.clearChangedFlag();
	}
	
	if( tag.totalNumPoints() ){
		tag.setPct( ofClamp(drawPct, 0, 1) );
		drawPct += panel.getValueF("drawSpeed");
		if( drawPct >= 1.5 ){
			drawPct = 0.0;
		}
	}
	
	panel.clearAllChanged();
}


//--------------------------------------------------------------
void testApp::draw(){
	
	float relX = tag.currentPt.x * tagScale;
	float relY = (tag.currentPt.y-0.4) * tagScale*1.8;
	
	tagger.setTagArmTarget( ofxVec3f(relX, relY, 3.9) );
	
	bool draw_ground_plane = true;
	
	util_3d.begin3dDrawing( draw_ground_plane );
	
	ofRotate(panel.getValueF("rotate"), 0, 1, 0);

	ofPushStyle();
	ofSetLineWidth(2);
	ofNoFill();
	tag.draw(startOffset.x , startOffset.y, tagScale, tagScale);
	ofPopStyle();
		
	ofCircle(-0.5, 0.0, 0.1);
		
	glTranslatef(0, 0, 3.5);
	glColor4f( 0, 0, 0, 1);
	tagger.draw();
	
	util_3d.end3dDrawing();
	
	ofSetupScreen();
	panel.draw();
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
	panel.mouseDragged(x, y, button);

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
	panel.mousePressed(x, y, button);
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
	panel.mouseReleased();
}

//--------------------------------------------------------------
void testApp::resized(int w, int h){

}

