#pragma once

#include "ofMain.h"
#include "ofxOsc.h"
#include "ofxSyphon.h"
#include "ofxHapPlayer.h"


#define MAX_BLOBS 100
#define MAX_TRACKS 32

typedef struct {
	int ID;
	int	parentID;
	double x;
	double y;
	double z;
	bool active;
	double age;
	int impactPartner;
	bool bound;
	double originDistance;
	double parentDistance;
	double angle;
	bool newTrigger;
	bool prevTrigger;
	bool canTrigger;
    int colorCode;
    ofColor color;
	
	ofRectangle rect;
	bool direction;
} point;

class testApp : public ofBaseApp{
	public:
		void setup();
		void update();
		void draw();
		
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y);
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		void checkForOscMessages();
		void parseTuio(ofxOscMessage m);
		void sendNote(int colorCode, int x, int y, int blobID);

        ofFbo   mFbo;
	
        ofTexture mTex;
    	ofxSyphonServer syphonOutTexture;
    
        ofxOscSender    oscSender[3];
        string          sendIP[3];
        int             sendPort[3];
        
        ofxOscReceiver  oscReceiver;
        int             receivePort;
    
        double startTime;
        bool createFlag[100];
	
		point blobs[MAX_BLOBS];
		long maxBlobAlive;
		bool blobStatus[MAX_BLOBS];
		bool prevBlobStatus[MAX_BLOBS];
		bool fseqStatus;
		
		int minimumAge;
		int selectedDirection[MAX_BLOBS];
		int selectionMinimumLength;
    
    ofVideoGrabber vidGrabber;
    ofPixels videoInverted;
    ofTexture videoTexture;
    int camWidth;
    int camHeight;
    
    ofShader shadertoy;
    ofImage color_noise, gray_rock, shell, vulcanic_rock;
    int draggedX, draggedY, clickX, clickY;
     ofxHapPlayer player;
};
