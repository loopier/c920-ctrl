#pragma once

#include "ofMain.h"
#include "ofxUVC.h"
#include "ofxYAML.h"
#include "ofxGui.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
    void    autoExposureChanged(bool & bAutoExposure);
    void    exposureChanged(float & exposure);
    void    autoFocusChanged(bool & bAutoFocus);
    void    focusChanged(float & focus);
    void    autoWhiteBalanceChanged(bool & bWhiteBalance);
    void    whiteBalanceChanged(float & whiteBalance);
    void    gainChanged(float & gain);
    void    brightnessChanged(float & brightness);
    void    contrastChanged(float & contrast);
    void    saturationChanged(float & saturation);
    void    sharpnessChanged(float & sharpness);
    
    
    ofVideoGrabber  cam;
    ofxUVC          uvc;
    ofxYAML         yaml;
    vector<ofxUVCControl>   controls;
    ofxPanel          gui;
    ofParameter<bool>   autoexposure;
    ofParameter<float>  exposure;
    ofParameter<bool>   autofocus;
    ofParameter<float>  focus;
    ofParameter<bool>   autowhitebalance;
    ofParameter<float>  whitebalance;
    ofParameter<float>  gain;
    ofParameter<float>  brightness;
    ofParameter<float>  contrast;
    ofParameter<float>  saturation;
    ofParameter<float>  sharpness;
};
