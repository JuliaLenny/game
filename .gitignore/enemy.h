#pragma once
// Include
#include "gameObject.h"
#include "level.h"

// Class Ghost
class Enemy
	: public GameObject
{
public:
	Enemy();
	virtual void update(float dt);

private:
	float m_spawnTimer;
	float m_spawnTime;
};
