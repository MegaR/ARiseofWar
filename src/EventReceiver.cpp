#include "EventReceiver.h"


EventReceiver::EventReceiver(void) {
	for(int i = 0; i < 2; i++) {
		mouseStates[i] = UP;
		mouseStates[i] = UP;
	}
}


EventReceiver::~EventReceiver(void) {
}

bool EventReceiver::isLeftMouseDown(){
	return (mouseStates[0]==DOWN);
}
bool EventReceiver::isLeftMouseUp(){
	return (mouseStates[0]==UP);
}
bool EventReceiver::isLeftMousePressed(){
	return (mouseStates[0]==PRESSED);
}
bool EventReceiver::isLeftMouseReleased(){
	return (mouseStates[0]==RELEASED);
}
bool EventReceiver::isRightMouseDown(){
	return (mouseStates[1]==DOWN);
}
bool EventReceiver::isRightMouseUp(){
	return (mouseStates[1]==UP);
}
bool EventReceiver::isRightMousePressed(){
	return (mouseStates[1]==PRESSED);
}
bool EventReceiver::isRightMouseReleased(){
	return (mouseStates[1]==RELEASED);
}


bool EventReceiver::isKeyDown(int key){
	return (keyStates[key]==DOWN);
}
bool EventReceiver::isKeyUp(int key){	
	return (keyStates[key]==UP);
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
}

void EventReceiver::update() {
	//update mouse
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
}