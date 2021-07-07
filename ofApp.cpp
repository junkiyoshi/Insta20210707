#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openframeworks");

	ofBackground(239);
	ofSetLineWidth(2);
	ofSetRectMode(ofRectMode::OF_RECTMODE_CENTER);

	this->image.loadImage("images/lenna.png");
	this->image.resize(720, 720);
	this->fbo.allocate(720, 720);
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);

	this->fbo.begin();
	ofClear(0);
	ofEnableBlendMode(ofBlendMode::OF_BLENDMODE_ADD);

	ofTranslate(this->fbo.getWidth() * 0.5, this->fbo.getHeight() * 0.5);

	for (int i = 0; i < 350; i++) {

		auto noise_seed = glm::vec2(ofRandom(1000), ofRandom(1000));
		auto target = glm::vec2(ofMap(ofNoise(noise_seed.x, ofGetFrameNum() * 0.001), 0, 1, -450, 450), ofMap(ofNoise(noise_seed.y, ofGetFrameNum() * 0.001), 0, 1, -450, 450));
		auto next = glm::vec2(ofMap(ofNoise(noise_seed.x, (ofGetFrameNum() + 1) * 0.001), 0, 1, -450, 450), ofMap(ofNoise(noise_seed.y, (ofGetFrameNum() + 1) * 0.001), 0, 1, -450, 450));

		this->draw_arrow(target, next, ofRandom(30, 50), ofColor(255), ofColor(0));
	}

	this->fbo.end();

	this->image.getTextureReference().setAlphaMask(this->fbo.getTexture());
	this->image.update();
}

//--------------------------------------------------------------
void ofApp::draw() {

	ofSetColor(255);
	this->image.draw(ofGetWindowSize() * 0.5);
}

//--------------------------------------------------------------
void ofApp::draw_arrow(glm::vec2 location, glm::vec2 target, float size, ofColor fill_color, ofColor no_fill_color) {

	auto angle = std::atan2(target.y - location.y, target.x - location.x);

	ofSetColor(fill_color);
	ofFill();
	ofBeginShape();
	ofVertex(location + glm::vec2(size * cos(angle), size * sin(angle)));
	ofVertex(location + glm::vec2(size * 0.5 * cos(angle + PI * 0.5), size * 0.5 * sin(angle + PI * 0.5)));
	ofVertex(location + glm::vec2(size * 0.5 * cos(angle - PI * 0.5), size * 0.5 * sin(angle - PI * 0.5)));
	ofEndShape();

	ofBeginShape();
	ofVertex(location + glm::vec2(size * 0.5 * cos(angle + PI * 0.5), size * 0.5 * sin(angle + PI * 0.5)) * 0.25);
	ofVertex(location + glm::vec2(size * 0.5 * cos(angle + PI * 0.5), size * 0.5 * sin(angle + PI * 0.5)) * 0.25 - glm::vec2(size * cos(angle), size * sin(angle)) * 0.5);
	ofVertex(location + glm::vec2(size * 0.5 * cos(angle - PI * 0.5), size * 0.5 * sin(angle - PI * 0.5)) * 0.25 - glm::vec2(size * cos(angle), size * sin(angle)) * 0.5);
	ofVertex(location + glm::vec2(size * 0.5 * cos(angle - PI * 0.5), size * 0.5 * sin(angle - PI * 0.5)) * 0.25);
	ofEndShape();

	ofSetColor(no_fill_color);
	ofNoFill();
	ofBeginShape();
	ofVertex(location + glm::vec2(size * 0.5 * cos(angle + PI * 0.5), size * 0.5 * sin(angle + PI * 0.5)) * 0.25);
	ofVertex(location + glm::vec2(size * 0.5 * cos(angle + PI * 0.5), size * 0.5 * sin(angle + PI * 0.5)));
	ofVertex(location + glm::vec2(size * cos(angle), size * sin(angle)));
	ofVertex(location + glm::vec2(size * 0.5 * cos(angle - PI * 0.5), size * 0.5 * sin(angle - PI * 0.5)));
	ofVertex(location + glm::vec2(size * 0.5 * cos(angle - PI * 0.5), size * 0.5 * sin(angle - PI * 0.5)) * 0.25);
	ofEndShape();

	ofBeginShape();
	ofVertex(location + glm::vec2(size * 0.5 * cos(angle - PI * 0.5), size * 0.5 * sin(angle - PI * 0.5)) * 0.25);
	ofVertex(location + glm::vec2(size * 0.5 * cos(angle - PI * 0.5), size * 0.5 * sin(angle - PI * 0.5)) * 0.25 - glm::vec2(size * cos(angle), size * sin(angle)) * 0.5);
	ofVertex(location + glm::vec2(size * 0.5 * cos(angle + PI * 0.5), size * 0.5 * sin(angle + PI * 0.5)) * 0.25 - glm::vec2(size * cos(angle), size * sin(angle)) * 0.5);
	ofVertex(location + glm::vec2(size * 0.5 * cos(angle + PI * 0.5), size * 0.5 * sin(angle + PI * 0.5)) * 0.25);
	ofEndShape();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}