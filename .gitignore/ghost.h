#pragma once
// Include
#include "gameObject.h"
#include "level.h"

// Class Ghost
class Ghost
	: public GameObject
{
public:
	Ghost();

	virtual void update(float dt);
	virtual void render(sf::RenderWindow* rw);

	void move(Direction direction);
	void fire();


protected:
	void calculateFrontCellPosition(float* x, float* y);

protected:
	float m_fireCooldownTime;
	float m_speed;
};
