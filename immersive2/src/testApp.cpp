#include "testApp.h"

//#include <stdio.h>
//#include <stdlib.h>

//--------------------------------------------------------------
void testApp::setup(){
    // Load a movie file
    player.load("movies/113.mov");
    
    // Start playback
    player.play();
    
    ofBackground(0);
	ofEnableAlphaBlending();
    ofSetFrameRate(100);
    ofSetEscapeQuitsApp(false);
	ofSetCircleResolution(100);
    
    ofDisableArbTex();
    shadertoy.load("shader/shadertoy");


    
    mFbo.allocate(4*1280, 720, GL_RGBA);
    mTex.allocate(4*1280, 720, GL_RGBA);    
    syphonOutTexture.setName("ImmersiveLab_basic");
	
    // panelVideoMapper
    sendIP[0] = "224.0.0.1";
//    sendPort[0] = 64000;
sendPort[0] = 8400;
	// masterTracker
    sendIP[1] = "224.0.0.1";
//    sendPort[1] = 8400;
        sendPort[1] = 64000;
	
	// your Audio Engine
	sendIP[2] = "224.0.0.1";
	sendPort[2] = 34567; // a port of your choice
	
    oscSender[0].setup(sendIP[0], sendPort[0]);
    oscSender[1].setup(sendIP[1], sendPort[1]);
    oscSender[2].setup(sendIP[2], sendPort[2]);

	receivePort = 23456; // a port of your choice, preset-able
    oscReceiver.setup(receivePort);
    
    startTime = ofGetElapsedTimef();
    
    // trackerMaster init
    ofxOscMessage n;
    n.setAddress( "/trackerMaster/requestTuiostream" );
    n.addIntArg( receivePort );
    oscSender[0].sendMessage( n );
    
    // pannelmapper init
    ofxOscMessage m;
    m.setAddress( "/SwitchSyphonClient" );
    m.addStringArg( "immersive2Debug" );
    m.addStringArg( "ImmersiveLab_basic" );
    m.addFloatArg( 1.0 );
    oscSender[1].sendMessage( m );
	
	minimumAge  = 5.0;
	
	time_t t;
	srandom( (unsigned) time(&t));  /* Seed the PRNG */
    
    camWidth = 320;  // try to grab at this size.
    camHeight = 240;
    
    //we can now get back a list of devices.
    vector<ofVideoDevice> devices = vidGrabber.listDevices();
    
    for(int i = 0; i < devices.size(); i++){
        if(devices[i].bAvailable){
            ofLogNotice() << devices[i].id << ": " << devices[i].deviceName;
        }else{
            ofLogNotice() << devices[i].id << ": " << devices[i].deviceName << " - unavailable ";
        }
    }
    
//    vidGrabber.setDeviceID(0);
//    vidGrabber.setDesiredFrameRate(60);
//    vidGrabber.initGrabber(camWidth, camHeight);
//    
//    videoInverted.allocate(camWidth, camHeight, OF_PIXELS_RGB);
//    videoTexture.allocate(videoInverted);
    ofSetVerticalSync(true);
}

//--------------------------------------------------------------
void testApp::update()
{
    double now = ofGetElapsedTimef();
    double runningSeconds = now - startTime;
	
	checkForOscMessages();
    
    player.update();
    
//    vidGrabber.update();
//    
//    if(vidGrabber.isFrameNew()){
//        ofPixels & pixels = vidGrabber.getPixels();
//        for(int i = 0; i < pixels.size(); i++){
//            videoInverted[i] = 255 - pixels[i];
//        }
//        videoTexture.loadData(videoInverted);
//    }
}

//--------------------------------------------------------------
void testApp::draw()
{
	float x;
	
	mFbo.begin(); // technique 1: draw to an fbo, for further texture sharing
//	
//    ofBackground(0, 0, 0);
//	ofSetColor(127, 127, 255, 192);
    
    ofSetWindowTitle(ofToString(ofGetFrameRate()));
    
    shadertoy.begin();
    shadertoy.setUniform3f("iResolution", ofGetWidth(), ofGetHeight(), 0.0);
    shadertoy.setUniform1f("iGlobalTime", ofGetElapsedTimef());
    shadertoy.setUniform4f("iMouse", draggedX, draggedY, clickX, clickY);
    shadertoy.setUniform4f("iDate", ofGetYear(), ofGetMonth(), ofGetDay(), ofGetSeconds());
    
    ofRect(0, 0, ofGetWidth(), ofGetHeight());
    
    shadertoy.end();
player.draw(999, 744);	x = 0;
//	ofLine(0+x,	 0.0, 0+x, 720);
//	ofLine(213.3333+x, 0.0, 213.3333+x, 720);
//	ofLine(426.666666666667+x, 0.0, 426.666666666667+x, 720);
//	ofLine(640+x, 0.0, 640+x, 720);
//	ofLine(853.333333333333+x, 0.0, 853.333333333333+x, 720);
//	ofLine(1066.666666666667+x, 0.0, 1066.666666666667+x, 720);
//
//    vidGrabber.draw(1, 1);
//    videoTexture.draw(0 , 0, .05, .05);
   
//    vidGrabber.draw(1000, 100);
//    videoTexture.draw(40 + camWidth, 40, camWidth, camHeight);
//    vidGrabber.draw(2000, 200);
//    videoTexture.draw(60 + camWidth, 60, camWidth, camHeight);
//    vidGrabber.draw(3000, 300);
//    videoTexture.draw(80 + camWidth, 80, camWidth, camHeight);
	ofSetColor(255, 127, 127, 192);

	x = 1280;
//	ofLine(0+x,	 0.0, 0+x, 720);
//	ofLine(213.3333+x, 0.0, 213.3333+x, 720);
//	ofLine(426.666666666667+x, 0.0, 426.666666666667+x, 720);
//	ofLine(640+x, 0.0, 640+x, 720);
//	ofLine(853.333333333333+x, 0.0, 853.333333333333+x, 720);
//	ofLine(1066.666666666667+x, 0.0, 1066.666666666667+x, 720);

	ofSetColor(127, 255, 127, 192);
	
	x = 2560;
//	ofLine(0+x,	 0.0, 0+x, 720);
//	ofLine(213.3333+x, 0.0, 213.3333+x, 720);
//	ofLine(426.666666666667+x, 0.0, 426.666666666667+x, 720);
//	ofLine(640+x, 0.0, 640+x, 720);
//	ofLine(853.333333333333+x, 0.0, 853.333333333333+x, 720);
//	ofLine(1066.666666666667+x, 0.0, 1066.666666666667+x, 720);
	
	ofSetColor(255, 255, 127, 192);
	
	x = 3840;
//	ofLine(0+x,	 0.0, 0+x, 720);
//	ofLine(213.3333+x, 0.0, 213.3333+x, 720);
//	ofLine(426.666666666667+x, 0.0, 426.666666666667+x, 720);
//	ofLine(640+x, 0.0, 640+x, 720);
//	ofLine(853.333333333333+x, 0.0, 853.333333333333+x, 720);
//	ofLine(1066.666666666667+x, 0.0, 1066.666666666667+x, 720);
	
	ofSetColor(255, 255, 255, 192);
//	
//	ofLine(0.0, 120, 5120, 120);
//	ofLine(0.0, 240, 5120, 240);
//	ofLine(0.0, 360, 5120, 360);
//	ofLine(0.0, 480, 5120, 480);
//	ofLine(0.0, 600, 5120, 600);
	

	// draw the blobs
	ofNoFill();
	for(int i = 0; i < MAX_BLOBS; i++) { // loop running the blobs
	 
		 if(blobs[i].active == true) { // we have a live blob
			 ofSetColor(255, 255, 127, 255);
			 ofSetLineWidth(2.0);
			 ofSetCircleResolution(50);
			 ofCircle( blobs[i].x*1280, blobs[i].y*720, 6);
             player.draw(blobs[i].x*1280, blobs[i].y*720);
			 ofSetColor(255, 255, 255, 192);

			 ofDrawBitmapString(ofToString(i) + " " + ofToString(blobs[i].x) + " " + ofToString(blobs[i].y), blobs[i].x*1280+20, blobs[i].y*720+10);
		 }
	 }
	
	mFbo.end(); // capture all the drawing in the fbo
	ofSetColor(255, 255, 255, 255);

    mFbo.draw(0, 0);

    mTex.loadScreenData(0, 0, 4*1280, 720);
	
    ofSetColor(255, 255, 255, 255);
    ofEnableAlphaBlending();
    syphonOutTexture.publishTexture(&mTex);
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}

void testApp::checkForOscMessages()
{
	long i;
	int tempInt, ID;
	string tempStr;
	string oscString;
	
	while( oscReceiver.hasWaitingMessages() ) {
		ofxOscMessage m;
		oscReceiver.getNextMessage( &m );
		oscString = m.getAddress();
		
		
		if ( !strcmp( oscString.c_str(), "/tuio/2Dcur")) {
//			cout << "OSC msg received" << endl;
			parseTuio(m); // go do the tuio parsing
        }
    }
}

// TODO implement the IL tuioManager class with clustering ect. from Processing

void testApp::parseTuio(ofxOscMessage m)
{
	long i, j, k;
	long blobID = -1;
	double now = ofGetElapsedTimef();
	//	point t;
	//	t.x = t.y = t.z = 0.0;
	
	string tempStr = m.getArgAsString( 0 );
	int numArgs = m.getNumArgs();
	
#pragma mark	alive
	if(!strcmp(tempStr.c_str(), "alive")) {
		fseqStatus = false; // check for empty frames

		if(numArgs > 1) {
			//			for(i = 0; i < MAX_BLOBS; i++) {
			//				blobStatus[i] = 0;
			//			}
			maxBlobAlive = -1;
			for(i = 1; i < numArgs; i++) {
				if(m.getArgType(i) == OFXOSC_TYPE_INT32){
					blobID = m.getArgAsInt32(i);
					blobID = blobID % MAX_BLOBS;
					
                    if(blobs[blobID].active == false) { // a new blob is born
                        blobs[blobID].age = now;
                        blobs[blobID].active = true;
//						blobs[blobID].rect.setX(blobs[blobID].x);
//						blobs[blobID].rect.setY(blobs[blobID].y);
						blobs[blobID].canTrigger = true; // the first appearance needed for storage
                    }
					blobStatus[blobID] = 1;	// set tempblob flags
					if(maxBlobAlive < blobID) {
						maxBlobAlive = blobID; // store largest blob alive
					}
				}
			}
            // check which ones have gone
            for(i = 0; i < MAX_BLOBS; i++){
                if(blobStatus[i] == false && blobs[i].active == true) {
                    blobs[i].active = false;
					blobs[i].newTrigger = true;
					
					if(blobs[i].age > minimumAge) { // minimum age reached we can trigger now
						if( blobs[i].rect.width < 0.0){
							selectedDirection[i] = -1.;
						}else{
							selectedDirection[i] = 1;
						}
						double interval = blobs[i].age * 0.005;
						double centre_y = (blobs[i].rect.y * 720);
						
						
						uint64 R = random();  /* Generate a random integer */
						double stepSize = ((R % 700) + 200) * 0.0001; // scale to max-range of invTable

						double dimensions_x = blobs[i].rect.width * 1280;
						double dimensions_y = blobs[i].rect.y * ((R % 700)+20);

					
						int direction = selectedDirection[i];
						double anglePosition = blobs[i].rect.x * 90.0;
						anglePosition =  fmod(anglePosition, 360.0);
						
//						cout << "blob:  age " << blobs[i].age << " rect.x " << blobs[i].rect.x << " width " << blobs[i].rect.width << endl;


					}
                    blobs[i].age = -1.0;
					blobs[i].active = false;

                }
            }
		}
	}
	
#pragma mark set
	else if(!strcmp(tempStr.c_str(), "set")) { // format: set ID x y accel-x accel-y
		
		if(numArgs > 3) {
			// blob ID
			if(m.getArgType(1) == OFXOSC_TYPE_INT32) {
				blobID = m.getArgAsInt32(1);
				blobID = blobID % MAX_BLOBS; // safety!! wrap to existing array sizes
			}
			if(m.getArgType(2) == OFXOSC_TYPE_FLOAT){
				blobs[blobID].x = m.getArgAsFloat(2);
			}else if(m.getArgType(2) == OFXOSC_TYPE_INT32) {
				blobs[blobID].x = (double)m.getArgAsInt32(2);
			}
			
			if(m.getArgType(3) == OFXOSC_TYPE_FLOAT){
				blobs[blobID].y = m.getArgAsFloat(3);
			}else if(m.getArgType(3) == OFXOSC_TYPE_INT32) {
				blobs[blobID].y = (double)m.getArgAsInt32(3);
			}
//			printf("tuio received: set %ld %f %f\n", blobID, blobs[blobID].x, blobs[blobID].y);
			
		}
	}
	
#pragma mark	fseq
	else if(!strcmp(tempStr.c_str(), "fseq")) {
		if(fseqStatus == true) { // there was NO alive part in the message
			for(i = 0; i < MAX_BLOBS; i++) { // loop running the blobs
				blobs[i].active = false;
			}
			return;
		}
		for(i = 0; i < MAX_BLOBS; i++) { // loop running the blobs
            
			if(blobStatus[i] == true) { // we have a live one
				
				// collect min and max coords in x and y and delta between min.x and max.x for direction

				if(blobs[i].canTrigger){ // store the beginning point
				    blobs[i].rect.setX(blobs[i].x);
				    blobs[i].rect.setY(blobs[i].y);
					blobs[i].canTrigger = false;
				}else{ // update the following points, thus growing the rectangle, until we reach end of blob
					
					blobs[i].rect.setWidth(blobs[i].x - blobs[i].rect.x);
					blobs[i].rect.setHeight(blobs[i].y - blobs[i].rect.y);
				}
//				printf("blob %ld %f %f\n", i, blobs[i].x, blobs[i].y);
            }
        } // end of running the blobs loop
        
        for(i = 0; i < MAX_BLOBS; i++) {
            blobStatus[i] = 0;
        }
		fseqStatus = true;
	} // end "fseq case"
}

