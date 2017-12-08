#include "ghost.h"
#include "bullet.h"

// Class GameObject
Ghost::Ghost()
{
	m_type = GameObjectType_Ghost;

	m_width = kGhostSize;
	m_height = kGhostSize;

	m_speed = 0;
	m_recoveryTime = 0.0;
}

void Ghost::update(float dt)
{
	GameObject::update(dt);

	if (m_recoveryTime > 0)
		m_recoveryTime -= dt;
}

void Ghost::render(sf::RenderWindow* rw)
{
	sf::IntRect texRect = kGhostImage;
	texRect.left += m_width * kPixels * m_direction;
	setTextureRect(texRect);

	GameObject::render(rw);
}

void Ghost::move(Direction direction)
{
	setDirection(direction);

	setXSpeed(0);
	setYSpeed(0);

	switch (m_direction)
	{
	case Direction_Left: setXSpeed(-m_speed); break;
	case Direction_Right: setXSpeed(m_speed); break;
	case Direction_Up: setYSpeed(-m_speed); break;
	case Direction_Down: setYSpeed(m_speed); break;
	}
}

void Ghost::fire()
{
	if (m_recoveryTime > 0)
		return;

	m_recoveryTime = kGhostRecoveryTime;

	float x = 0.0;
	float y = 0.0;
	float xSpeed = 0.0;
	float ySpeed = 0.0;

	calculateFrontCellPosition(&x, &y);

	switch (m_direction)
	{
	case Direction_Left: xSpeed = -kBulletSpeed; break;
	case Direction_Right: xSpeed = kBulletSpeed; break;
	case Direction_Up: ySpeed = -kBulletSpeed; break;
	case Direction_Down: ySpeed = kBulletSpeed; break;
	}

	Bullet* bullet = (Bullet*)m_game->createObject(GameObjectType_Bullet, x, y);
	if (bullet)
	{
		bullet->setOwnerType(m_type);
		bullet->setXSpeed(xSpeed);
		bullet->setYSpeed(ySpeed);
	}
}

void Ghost::calculateFrontCellPosition(float* x, float* y)
{
	switch (m_direction)
	{
	case Direction_Left:
		(*x) = int(getX()) - 0.01;
		(*y) = int(getY()) + (getHeight() / 2.0);

		break;
	case Direction_Right:
		(*x) = int(getX()) + getWidth() + 0.01;
		(*y) = int(getY()) + (getHeight() / 2.0);
		break;
	case Direction_Up:
		(*y) = int(getY()) - 0.01;
		(*x) = int(getX()) + (getWidth() / 2.0);
		break;
	case Direction_Down:
		(*y) = int(getY()) + getHeight() + 0.01;
		(*x) = int(getX()) + (getWidth() / 2.0);
		break;
	}
}
