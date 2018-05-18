#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    yaml.load("cameraDB.yml");
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
    
    yaml.load("camerasettings.yml");
    float autoExposureValue     = yaml["autoexposure"].as<int>();
    float exposureValue     = yaml["exposure"].as<float>();
    float autoFocusValue        = yaml["autofocus"].as<int>();
    float focusValue        = yaml["focus"].as<float>();
    float autoWhitebalanceValue = yaml["autowhitebalance"].as<int>();
    float whitebalanceValue = yaml["whitebalance"].as<float>();
    float gainValue         = yaml["gain"].as<float>();
    float brightnessValue   = yaml["brightness"].as<float>();
    float contrastValue     = yaml["contrast"].as<float>();
    float saturationValue   = yaml["saturation"].as<float>();
    float sharpnessValue    = yaml["sharpness"].as<float>();
    
    gui.setup(name);
    gui.add(autoexposure.set("autoexposure", autoExposureValue));
    gui.add(exposure.set("exposure", exposureValue, 0.0, 1.0));
    gui.add(autofocus.set("autofocus", autoFocusValue));
    gui.add(focus.set("focus", focusValue, 0.0, 1.0));
    gui.add(autowhitebalance.set("autowhitebalance", autoWhitebalanceValue));
    gui.add(whitebalance.set("whitebalance", whitebalanceValue, 0.0, 1.0));
    gui.add(gain.set("gain", gainValue, 0.0, 1.0));
    gui.add(brightness.set("brightness", brightnessValue, 0.0, 1.0));
    gui.add(contrast.set("contrast", contrastValue, 0.0, 1.0));
    gui.add(saturation.set("saturation", saturationValue, 0.0, 1.0));
    gui.add(sharpness.set("sharpness", sharpnessValue, 0.0, 1.0));
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
    ofDrawBitmapString("CMD-S to save / SPACEBAR to load", 20, ofGetHeight() - 40);
}

void ofApp::save(){
    ofFile file("camerasettings.yml", ofFile::WriteOnly);
    
    string str = "";
    str += "autoexposure: " + ofToString(autoexposure) + "\n";
    str += "exposure: " + ofToString(exposure) + "\n";
    str += "autofocus: " + ofToString(autofocus) + "\n";
    str += "focus: " + ofToString(focus) + "\n";
    str += "autowhitebalance: " + ofToString(autowhitebalance) + "\n";
    str += "whitebalance: " + ofToString(whitebalance) + "\n";
    str += "gain: " + ofToString(gain) + "\n";
    str += "brightness: " + ofToString(brightness) + "\n";
    str += "contrast: " + ofToString(contrast) + "\n";
    str += "saturation: " + ofToString(saturation) + "\n";
    str += "sharpness: " + ofToString(sharpness);
    file << str;
    file.close();
}

void ofApp::load(){
    
    yaml.load("cameraDB.yml");
    int cameraToUse     = yaml["cameraToUse"].as<int>();
    int vendorId        = yaml["cameras"][cameraToUse]["vendorId"].as<int>();
    int productId       = yaml["cameras"][cameraToUse]["productId"].as<int>();
    int interfaceNum    = yaml["cameras"][cameraToUse]["interfaceNum"].as<int>();
    string name            = yaml["cameras"][cameraToUse]["name"].as<string>();
    int width           = yaml["cameras"][cameraToUse]["width"].as<int>();
    int height          = yaml["cameras"][cameraToUse]["height"].as<int>();
    
    uvc.useCamera(vendorId, productId, interfaceNum);
    
    
    yaml.load("camerasettings.yml");
    autoexposure     = yaml["autoexposure"].as<int>();
    exposure     = yaml["exposure"].as<float>();
    autofocus        = yaml["autofocus"].as<int>();
    focus        = yaml["focus"].as<float>();
    autowhitebalance = yaml["autowhitebalance"].as<int>();
    whitebalance = yaml["whitebalance"].as<float>();
    gain        = yaml["gain"].as<float>();
    brightness   = yaml["brightness"].as<float>();
    contrast     = yaml["contrast"].as<float>();
    saturation   = yaml["saturation"].as<float>();
    sharpness    = yaml["sharpness"].as<float>();
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
    if(key == ' ') load();
    if(key == 's' && ofGetKeyPressed(OF_KEY_COMMAND)) save();
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
