#include "enemy.h"
#include "ghostEnemy.h"
#include "utils.h"


/////////////////////////////////////
// Class Enemy
Enemy::Enemy()
{
	m_type = GameObjectType_Enemy;


	m_spawnTime = kEnemyEmergenceTime; //spawn - место появления spawner - моб
	m_spawnTimer = GetRandomFloat(0.0, m_spawnTime);

	m_physical = false;
}


void Enemy::update(float dt)
{
	GameObject::update(dt);
	m_spawnTimer += dt;

	if (m_spawnTimer > m_spawnTime)
	{
		m_spawnTimer = 0.0f;
		int enemiesOnLevel = m_game->getObjectsCount(GameObjectType_GhostEnemy);
		int enemiesStorageLeft = kEnemiesLevel - enemiesOnLevel - m_game->getDiedEnemiesCount();
		if (enemiesStorageLeft > 0 && enemiesOnLevel < kEnemiesLevelInOneMoment)
			m_game->createObject(GameObjectType_GhostEnemy, getX(), getY());
	}
}
