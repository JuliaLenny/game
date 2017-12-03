#pragma once
// Include
#include "gameObject.h"
#include "level.h"

// Class Ghost
class EnemySpawner
	: public GameObject
{
public:
	EnemySpawner();
	virtual void update(float dt);

private:
	float m_spawnTimer;
	float m_spawnTime;
};
