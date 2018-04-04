#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    yaml.load("camerasettings.yml");
    int cameraToUse     = yaml["cameraToUse"].as<int>();
    int vendorId        = yaml["cameras"][cameraToUse]["vendorId"].as<int>();
    int productId       = yaml["cameras"][cameraToUse]["productId"].as<int>();
    int interfaceNum    = yaml["cameras"][cameraToUse]["interfaceNum"].as<int>();
    string name            = yaml["cameras"][cameraToUse]["name"].as<string>();
    int width           = yaml["cameras"][cameraToUse]["width"].as<int>();
    int height          = yaml["cameras"][cameraToUse]["height"].as<int>();
    
    vector<ofVideoDevice>  devices = cam.listDevices();
    
    int deviceId = 0;
    for(int i = 0; i < devices.size(); i++) {
        if (devices[i].deviceName == name) {
            deviceId = i;
        }
    }
    
    cam.setDeviceID(deviceId);
    cam.initGrabber(ofGetWidth(), ofGetHeight());
    
    uvc.useCamera(vendorId, productId, interfaceNum);
    
    autoexposure.addListener(this, &ofApp::autoExposureChanged);
    exposure.addListener(this, &ofApp::exposureChanged);
    autofocus.addListener(this, &ofApp::autoFocusChanged);
    focus.addListener(this, &ofApp::focusChanged);
    autowhitebalance.addListener(this, &ofApp::autoWhiteBalanceChanged);
    whitebalance.addListener(this, &ofApp::whiteBalanceChanged);
    gain.addListener(this, &ofApp::gainChanged);
    brightness.addListener(this, &ofApp::brightnessChanged);
    contrast.addListener(this, &ofApp::contrastChanged);
    saturation.addListener(this, &ofApp::saturationChanged);
    sharpness.addListener(this, &ofApp::sharpnessChanged);
    
    gui.setup(name);
    gui.add(autoexposure.set("autoexposure", true));
    gui.add(exposure.set("exposure", 0.9, 0.0, 1.0));
    gui.add(autofocus.set("autofocus", true));
    gui.add(focus.set("focus", 0.1, 0.0, 1.0));
    gui.add(autowhitebalance.set("autowhitebalance", true));
    gui.add(whitebalance.set("whitebalance", 0.5, 0.0, 1.0));
    gui.add(gain.set("gain", 0.15, 0.0, 1.0));
    gui.add(brightness.set("brightness", 0.5, 0.0, 1.0));
    gui.add(contrast.set("contrast", 0.5, 0.0, 1.0));
    gui.add(saturation.set("saturation", 0.5, 0.0, 1.0));
    gui.add(sharpness.set("sharpness", 0.5, 0.0, 1.0));
}

//--------------------------------------------------------------
void ofApp::update(){
    cam.update();
    controls = uvc.getCameraControls();
}

//--------------------------------------------------------------
void ofApp::draw(){
    cam.draw(0,0);
    gui.draw();
}

void    ofApp::autoExposureChanged(bool & bAutoExposure)
{
    uvc.setAutoExposure(bAutoExposure);
}

void    ofApp::exposureChanged(float & exposure)
{
    uvc.setExposure(exposure);
}

void    ofApp::autoFocusChanged(bool & bAutoFocus)
{
    uvc.setAutoFocus(bAutoFocus);
}

void    ofApp::focusChanged(float & focus)
{
    uvc.setAbsoluteFocus(focus);
}

void    ofApp::autoWhiteBalanceChanged(bool & bAutoWhiteBalance)
{
    uvc.setAutoWhiteBalance(bAutoWhiteBalance);
}

void    ofApp::whiteBalanceChanged(float & whiteBalance)
{
    uvc.setWhiteBalance(whiteBalance);
}

void    ofApp::gainChanged(float & gain)
{
    uvc.setGain(gain);
}

void    ofApp::brightnessChanged(float & brightness)
{
    uvc.setBrightness(brightness);
}

void    ofApp::contrastChanged(float & constrast)
{
    uvc.setContrast(contrast);
}

void    ofApp::saturationChanged(float & saturation)
{
    uvc.setSaturation(saturation);
}

void    ofApp::sharpnessChanged(float & sharpness)
{
    uvc.setSharpness(sharpness);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

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
