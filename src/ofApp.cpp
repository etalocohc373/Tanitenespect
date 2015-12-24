#include "ofApp.h"

float timerCount = 3;
float alpha = 0;
bool handsDetected = false;
bool ballDetect = false;
bool result = false;

float ballRadius = 0;
ofVec3f ballPoint;

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(0);
    appleImg.load("apple.png");
    ofSetFrameRate(50);
    ofSetVerticalSync(true);
    
    cam.setOrientation(ofPoint(-20, 0, 0));
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);
    
    leapMotion.open();
    
    ofEnableNormalizedTexCoords();
}

//--------------------------------------------------------------
void ofApp::update(){
    simpleHands = leapMotion.getSimpleHands();
    if (leapMotion.isFrameNew() && simpleHands.size()){
        handPos.clear();
        fingerPos.clear();
        
        leapMotion.setMappingX(-230, 230, -ofGetWidth() / 2, ofGetWidth() / 2);
        leapMotion.setMappingY(90, 490, -ofGetHeight() / 2, ofGetHeight() / 2);
        leapMotion.setMappingZ(-150, 150, -200, 200);
        
        fingerType fingerTypes[] = {THUMB, INDEX, MIDDLE, RING, PINKY};
        
        for (int i = 0; i < simpleHands.size(); i++) {
            handPos.push_back(simpleHands[i].handPos);
            for (int f = 0; f < 5; f++) {
                ofPoint mcp = simpleHands[i].fingers[fingerTypes[f]].mcp;
                fingerPos.push_back(mcp);
                
                ofPoint pip = simpleHands[i].fingers[fingerTypes[f]].pip;
                fingerPos.push_back(pip);
                
                ofPoint dip = simpleHands[i].fingers[fingerTypes[f]].dip;
                fingerPos.push_back(dip);
                
                ofPoint tip = simpleHands[i].fingers[fingerTypes[f]].tip;
                fingerPos.push_back(tip);
            }
        }
        leapMotion.markFrameAsOld();
    }
    
    if (!handsDetected && !ballDetect && !result){
        timerCount = 3.0;
    }
    if (handsDetected && !ballDetect && !result){
        timerCount -= 0.02;
        if (timerCount <= 0)
            ballDetect = true;
    }
    
    if (ballPoint.y > -400 + ballRadius && ballDetect)
        ballPoint.y -= 5;
    else if (ballPoint.y < -430 + ballRadius && ballDetect)
        ballPoint.y += 5;
    else if (ballDetect)
        result = true;
}

//--------------------------------------------------------------
void ofApp::draw(){
    cam.begin();
    
    for (int i = 0; i < simpleHands.size(); i++) {
        ofSetColor(0, 255, 0);
        ofDrawSphere(handPos.at(i), 20);
        for (int f = 0; f < 5; f++) {
            ofSetColor(255);
            ofDrawSphere(fingerPos.at(20 * i + 4 * f + 0), 10);
            
            ofSetColor(200);
            ofDrawSphere(fingerPos.at(20 * i + 4 * f + 1), 10);
            
            ofSetColor(155);
            ofDrawSphere(fingerPos.at(20 * i + 4 * f + 2), 10);
            
            ofSetColor(100);
            ofDrawSphere(fingerPos.at(20 * i + 4 * f + 3), 10);
            
            ofDrawLine(fingerPos.at(20 * i + 4 * f + 0), fingerPos.at(20 * i + 4 * f + 1));
            ofDrawLine(fingerPos.at(20 * i + 4 * f + 1), fingerPos.at(20 * i + 4 * f + 2));
            ofDrawLine(fingerPos.at(20 * i + 4 * f + 2), fingerPos.at(20 * i + 4 * f + 3));
        }
    }
    
    
    if (!ballDetect && !result){
        if (simpleHands.size() == 2){
            handsDetected = true;
            
            ofSetColor(100);
            ballPoint = (handPos.at(0) + handPos.at(1)) / 2;
            ballRadius = pow(pow(handPos.at(1).x - handPos.at(0).x, 2) + pow(handPos.at(1).y - handPos.at(0).y, 2) + pow(handPos.at(1).z - handPos.at(0).z, 2), 0.5) / 2;
            ofDrawSphere(ballPoint, ballRadius);
        }else
            handsDetected = false;
    }
    if (ballDetect){
        ofSetColor(100);
//        if (result)
//            appleImg.bind();
        
        //ofDrawSphere(ballPoint, ballRadius);
        
//        if (result)
//            appleImg.unbind();
        appleImg.draw(0,0,300,300);
    }
    cam.end();
    
    ofSetColor(255);
    if (ballDetect && result){
        if (ballRadius <= 150){
            ofDrawBitmapString("Apple", 50, 150);
            //appleImg.draw(ballPoint.x - ballRadius, ballPoint.y - ballRadius, ballRadius * 2, ballRadius * 2);
        }else
            ofDrawBitmapString("VolleyBall", 50, 150);
    }
    ofDrawBitmapString("Radius: " + ofToString(ballRadius), 50, 50);
    ofDrawBitmapString(ofToString(ceil(timerCount)), 50, 100);
    }

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    switch (key) {
        case ' ':
            timerCount = 3;
            alpha = 0;
            handsDetected = false;
            ballDetect = false;
            result = false;
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

//--------------------------------------------------------------
void ofApp::exit(){
    
}
