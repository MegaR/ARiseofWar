#pragma once

#include <irrlicht.h>
using namespace irr;
using namespace core;

#include <iostream>
using namespace std;

enum keyState {UP, DOWN, PRESSED, RELEASED};

class EventReceiver :
	public IEventReceiver
{
public:
	EventReceiver(void);
	~EventReceiver(void);
	virtual bool OnEvent(const SEvent& event);
	void update();

	bool isLeftMouseDown();
	bool isLeftMouseUp();
	bool isLeftMousePressed();
	bool isLeftMouseReleased();
	bool isRightMouseDown();
	bool isRightMouseUp();
	bool isRightMousePressed();
	bool isRightMouseReleased();

	bool isKeyDown(int key);
	bool isKeyUp(int key);
	bool isKeyPressed(int key);
	bool isKeyReleased(int key);

	float getScroll();
	int getMouseX();
	int getMouseY();
	vector2d<int> getMousePosition();

private:
	void handleKeys(const SEvent& event);
	void handleMouse(const SEvent& event);

	keyState mouseStates[2];
	keyState keyStates[KEY_KEY_CODES_COUNT];
	keyState nextMouseStates[2];
	keyState nextKeyStates[KEY_KEY_CODES_COUNT];
	int mouseX;
	int mouseY;
	float scroll;
	float nextScroll;
};



