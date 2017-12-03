#pragma once
// Include
#include "ghost.h"
// Class GhostEnemy
class GhostEnemy
	: public Ghost
{
public:
	GhostEnemy();
	~GhostEnemy();

	void update(float dt);

protected:

	void analize();
	void moveRandomDirection();

protected:
	float m_analizeTimer;
	float m_analizeTime;

	float m_lastAnalizeX;
	float m_lastAnalizeY;
};
