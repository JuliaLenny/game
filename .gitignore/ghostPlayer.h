#pragma once
// Include
#include "ghost.h"
// Class GhostPlayer
class GhostPlayer
	: public Ghost
{
public:
	GhostPlayer();

	void update(float dt);

	void setKeys(int keyLeft, int keyRight, int keyUp, int keyDown, int keyFire);

protected:
	int m_keyLeft;
	int m_keyRight;
	int m_keyUp;
	int m_keyDown;
	int m_keyFire;
};
