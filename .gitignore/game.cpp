#include "game.h"
#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <Windows.h>
#include "level.h"
#include "wall.h"
#include <conio.h>

//#include "base.h"

#include "bullet.h"
#include "ghostPlayer.h"
#include "ghostEnemy.h"
#include "enemySpawner.h"

// Global
sf::Texture* g_atlas00 = 0;

// Class Game
Game::Game()
{
	m_isGameActive = true;
	m_clockLastFrame = 0;

	for (int i = 0; i < kObjectsCountMax; i++)
		m_objects[i] = 0;

	m_player = 0;
	m_diedEnemiesCount = 0;
	m_renderWindow = 0;
}

Game::~Game()
{
	if (g_atlas00)
		delete g_atlas00;

	if (m_renderWindow)
		delete m_renderWindow;
}

void Game::setupSystem()
{
	srand(time(0));

	m_renderWindow = new sf::RenderWindow(
		sf::VideoMode(kPixelsPerCell * kScreenColumns, kPixelsPerCell * kScreenRows, 32),
		"Ghost's City",
		sf::Style::Titlebar | sf::Style::Close);

	g_atlas00 = new sf::Texture();
	g_atlas00->loadFromFile("image/atlas00.png");
}

void Game::initialize()
{
	shutdown();

	m_diedEnemiesCount = 0;

	// Load level
	for (int r = 0; r < kLevelRows; r++)
	{
		for (int c = 0; c < kLevelColumns; c++)
		{
			unsigned char cellSymbol = kLevelData0[r][c];

			switch (cellSymbol)
			{
			case CellSymbol_BrickWall:
			{
				Wall* wall = (Wall*)createObject(GameObjectType_Wall, c, r);
				wall->setTextureRect(kBrickWallImage);
				break;
			}

			case CellSymbol_SteelWall:
			{
				Wall* wall = (Wall*)createObject(GameObjectType_Wall, c, r);
				wall->setTextureRect(kSteelWallImage);
				wall->setInvulnerable(true);
				break;
			}

			
			case CellSymbol_Player:
			{
				GhostPlayer* player = (GhostPlayer*)createObject(GameObjectType_GhostPlayer, c + 0.5, r + 0.5);
				player->setSpriteColor(sf::Color(255, 255, 255));
				player->setKeys('A', 'D', 'W', 'S', VK_SPACE);
				m_player = player;

				break;
			}

			case CellSymbol_EnemySpawner:
			{
				createObject(GameObjectType_EnemySpawner, c, r);
				break;
			}
			}
		}
	}
}

bool Game::loop()
{
	if (!m_renderWindow->isOpen())
		return false;

	// Calculate delta time
	clock_t clockNow = clock();
	clock_t deltaClock = clockNow - m_clockLastFrame;
	float deltaTime = float(deltaClock) / CLOCKS_PER_SEC;
	m_clockLastFrame = clockNow;

    sf::Event event;
	while (m_renderWindow->pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			m_renderWindow->close();
	}

    render();
	update(deltaTime);

	return m_isGameActive;
}

void Game::shutdown()
{
	for (int i = 0; i < kObjectsCountMax; i++)
		if (m_objects[i] != 0)
		{
			delete m_objects[i];
			m_objects[i] = 0;
		}
	
	
	
}

void Game::render()
{
	// Start frame
	m_renderWindow->clear(sf::Color(20, 20, 20));

	// Deaw all game objects
	int objectsCount = 0;
	for (int i = 0; i < kObjectsCountMax; i++)
		if (m_objects[i] != 0)
		{
			m_objects[i]->render(m_renderWindow);
			objectsCount++;
		}
		m_renderWindow->display();
}

void Game::update(float dt)
{
	for (int i = 0; i < kObjectsCountMax; i++)
		if (m_objects[i] != 0)
		{
			m_objects[i]->update(dt);

			if (m_objects[i]->getHealth() <= 0 && m_objects[i]->getDestroyAfterDeath())
				destroyObject(m_objects[i]);
		}

	// Player1 destroyed
	if (m_player && m_player->getHealth() <= 0)
	{
		destroyObject(m_player);
		m_player = NULL;
		initialize();
	}
    // All enemies destroyed
	if (m_diedEnemiesCount == kEnemiesPerLevel)
		initialize();
}

GameObject* Game::checkIntersects(float x, float y, float width, float height, GameObject* exceptObject)
{
	int r00 = int(y);
	int c00 = int(x);
	int r01 = r00 + height - 1;
	int c01 = c00 + width - 1;

	for (int i = 0; i < kObjectsCountMax; i++)
		if (m_objects[i] != 0 && m_objects[i]->getPhysical() && m_objects[i] != exceptObject)
		{
			int r10 = int(m_objects[i]->getY());
			int c10 = int(m_objects[i]->getX());
			int r11 = r10 + m_objects[i]->getHeight() - 1;
			int c11 = c10 + m_objects[i]->getWidth() - 1;

			if (r00 <= r11 && r01 >= r10 && c00 <= c11 && c01 >= c10)
				return m_objects[i];
		}

	return 0;
}

bool Game::moveObjectTo(GameObject* object, float x, float y)
{
	int r0 = int(y);
	int c0 = int(x);
	int r1 = r0 + object->getHeight() - 1;
	int c1 = c0 + object->getWidth() - 1;

	if (r0 < 0 || c0 < 0 || r1 >= kLevelRows || c1 >= kLevelColumns)
		return false;


	bool canMoveToCell = false;

	GameObject* otherObject = checkIntersects(x, y, object->getWidth(), object->getHeight(), object);

	if (otherObject)
		object->intersect(otherObject);
	else
		canMoveToCell = true;


	if (canMoveToCell)
	{
		object->setX(x);
		object->setY(y);
	}

	return canMoveToCell;
}

int Game::getObjectsCount(GameObjectType type)
{
	int totalCount = 0;

	for (int i = 0; i < kObjectsCountMax; i++)
	{
		if (m_objects[i] == 0)
			continue;

		if (m_objects[i]->getType() == type)
			totalCount++;
	}

	return totalCount;
}

GameObject* Game::createObject(GameObjectType type, float x, float y)
{
	// Find free pointer and create object
	for (int i = 0; i < kObjectsCountMax; i++)
	{
		if (m_objects[i] == 0)
		{
			GameObject* object = 0;

			switch (type)
			{
			case GameObjectType_Wall:			object = new Wall();			break;
			case GameObjectType_Bullet:			object = new Bullet();			break;
			case GameObjectType_GhostPlayer:	object = new GhostPlayer();		break;
			case GameObjectType_GhostEnemy:		object = new GhostEnemy();		break;
			case GameObjectType_EnemySpawner:	object = new EnemySpawner();	break;
			}
			if (object == 0)
				return 0;
			object->setGame(this);
			if (moveObjectTo(object, x, y) == false)
			{
				delete object;
				return 0;
			}
			m_objects[i] = object;
			return object;
		}
	}

	return 0;
}

void Game::destroyObject(GameObject* object)
{
	for (int i = 0; i < kObjectsCountMax; i++)
	{
		if (m_objects[i] == object)
		{
			delete m_objects[i];
			m_objects[i] = 0;
			return;
		}
	}
}

void Game::increaseDiedEnemiesCount()
{
	m_diedEnemiesCount++;
}
