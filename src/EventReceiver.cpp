#include "EventReceiver.h"


EventReceiver::EventReceiver(void) {
	for(int i = 0; i < 2; i++) {
		mouseStates[i] = UP;
		nextMouseStates[i] = UP;
	}

	for(int i = 0; i < KEY_KEY_CODES_COUNT; i++) {
		keyStates[i] = UP;
		nextKeyStates[i] = UP;
	}

	mouseX = 0;
	mouseY = 0;
	scroll = 0;
	nextScroll = 0;
}


EventReceiver::~EventReceiver(void) {
}

bool EventReceiver::isLeftMouseDown(){
	return (mouseStates[0]==DOWN || mouseStates[0]==PRESSED);
}
bool EventReceiver::isLeftMouseUp(){
	return (mouseStates[0]==UP  || mouseStates[0]==RELEASED);
}
bool EventReceiver::isLeftMousePressed(){
	return (mouseStates[0]==PRESSED);
}
bool EventReceiver::isLeftMouseReleased(){
	return (mouseStates[0]==RELEASED);
}
bool EventReceiver::isRightMouseDown(){
	return (mouseStates[1]==DOWN || mouseStates[1]==PRESSED);
}
bool EventReceiver::isRightMouseUp(){
	return (mouseStates[1]==UP || mouseStates[1]==RELEASED);
}
bool EventReceiver::isRightMousePressed(){
	return (mouseStates[1]==PRESSED);
}
bool EventReceiver::isRightMouseReleased(){
	return (mouseStates[1]==RELEASED);
}
float EventReceiver::getScroll() {
	return scroll;
}
int EventReceiver::getMouseX() {
	return mouseX;
}
int EventReceiver::getMouseY() {
	return mouseY;
}
vector2d<int> EventReceiver::getMousePosition() {
	return vector2d<int>(mouseX, mouseY);
}


bool EventReceiver::isKeyDown(int key){
	return (keyStates[key]==DOWN || keyStates[key]==PRESSED);
}
bool EventReceiver::isKeyUp(int key){	
	return (keyStates[key]==UP || keyStates[key]==RELEASED);
}
bool EventReceiver::isKeyPressed(int key){	
	return (keyStates[key]==PRESSED);
}
bool EventReceiver::isKeyReleased(int key){
	return (keyStates[key]==RELEASED);
}

bool EventReceiver::OnEvent(const SEvent& event) {
	if(event.EventType == EET_MOUSE_INPUT_EVENT) {
		handleMouse(event);
	}

	if (event.EventType == EET_KEY_INPUT_EVENT) {
		handleKeys(event);
	}

	return false;
}

void EventReceiver::handleKeys(const SEvent& event) {
	if(event.KeyInput.PressedDown) {
		nextKeyStates[event.KeyInput.Key] = DOWN;
	} else {
		nextKeyStates[event.KeyInput.Key] = UP;
	}
}

void EventReceiver::handleMouse(const SEvent& event) {
	if(event.MouseInput.Event == EMIE_LMOUSE_PRESSED_DOWN) {
		nextMouseStates[0] = DOWN;
	}
	if(event.MouseInput.Event == EMIE_LMOUSE_LEFT_UP) {
		nextMouseStates[0] = UP;
	}

	if(event.MouseInput.Event == EMIE_RMOUSE_PRESSED_DOWN) {
		nextMouseStates[1] = DOWN;
	}
	if(event.MouseInput.Event == EMIE_RMOUSE_LEFT_UP) {
		nextMouseStates[1] = UP;
	}

	if(event.MouseInput.Event == EMIE_MOUSE_MOVED) {
		mouseX = event.MouseInput.X;
		mouseY = event.MouseInput.Y;
	}

	if(event.MouseInput.Event == EMIE_MOUSE_WHEEL) {
		nextScroll += event.MouseInput.Wheel;
	}
}

void EventReceiver::update() {
	//update mouse
	scroll = nextScroll;
	nextScroll = 0;

	for(int i = 0; i < 2; i++) {
		if(nextMouseStates[i] == DOWN) {
			if(mouseStates[i] == UP || mouseStates[i] == RELEASED) {
				mouseStates[i] = PRESSED;
			} else {
				mouseStates[i] = DOWN;
			}
		}
		if(nextMouseStates[i] == UP) {
			if(mouseStates[i] == DOWN || mouseStates[i] == PRESSED) {
				mouseStates[i] = RELEASED;
			} else {
				mouseStates[i] = UP;
			}
		}
	}

	//update keyboard keys
	for(int i = 0; i < KEY_KEY_CODES_COUNT; i++) {
		if(nextKeyStates[i] == DOWN) {
			if(keyStates[i] == UP || keyStates[i] == RELEASED) {
				keyStates[i] = PRESSED;
			} else {
				keyStates[i] = DOWN;
			}
		}

		if(nextKeyStates[i] == UP) {
			if(keyStates[i] == DOWN || keyStates[i] == PRESSED) {
				keyStates[i] = RELEASED;
			} else {
				keyStates[i] = UP;
			}
		}
	}
}