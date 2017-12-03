#pragma once
// Include
#include <SFML/Graphics.hpp>
#include "direction.h"
// Extern
extern sf::Texture* g_atlas00;
// Level data
const int kScreenRows = 40;
const int kScreenColumns = 80;
const int kLevelRows = kScreenRows;
const int kLevelColumns = 70;
const int kPixelsPerCell = 15;

const unsigned char	CellSymbol_Player = '1';
const unsigned char	CellSymbol_Ghost = 'T';
const unsigned char	CellSymbol_BrickWall = '#';
const unsigned char	CellSymbol_SteelWall = '@';
const unsigned char	CellSymbol_EnemySpawner = 'S';
//const char win[] = "You win, motherfucker!!!";


const unsigned char kLevelData0[kLevelRows][kLevelColumns + 1] =
{
	"@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@",
	"@S                                @@                              S  @",
	"@                                 @@                                 @",
	"@                                 @@                                 @",
	"@                                          S         @@@             @",
	"@                                                                    @",
	"@                                                                    @",
	"@@@@@@@@@@@@@@@@@@@@@@@@@@@@                                         @",
	"@                                                                    @",
	"@                                                                    @",
	"@                                                                    @",
	"@                                                                    @",
	"@            @                                                       @",
	"@            @                                                       @",
	"@            @                                                       @",
	"@            @                           @@@@@@@@@@@@@@@@@@@@@@@@@@@@@",
	"@   S        @                                                       @",
	"@            @                                                       @",
	"@            @                                                       @",
	"@@@@@@@@@@@@@@@@         @                                           @",
	"@                        @                                           @",
	"@                        @                                           @",
	"@                   @@@@@@             @                             @",
	"@                   @                  @                             @",
	"@                   @                  @                             @",
	"@                   @                  @                      S      @",
	"@@@@@@@@@@@@@@@@@@@@@                  @                             @",
	"@             @                        @                             @",
	"@         1   @                        @                             @",
	"@             @                        @              @@@            @",
	"@                                      @              @@@            @",
	"@                                      @                             @",
	"@                                      @                             @",
	"@                                      @                             @",
	"@             @                        @                             @",
	"@             @                        @                             @",
	"@             @                        @                             @",
	"@             @                        @                             @",
	"@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@",
};


const sf::IntRect kBrickWallImage = sf::IntRect(0, 3 * kPixelsPerCell, kPixelsPerCell, kPixelsPerCell);
const sf::IntRect kSteelWallImage = sf::IntRect(kPixelsPerCell, 3 * kPixelsPerCell, kPixelsPerCell, kPixelsPerCell);

// Ghost's data
const float kGhostFireCooldownTime = 0.5;
const int kGhostSize = 3;
const sf::IntRect kGhostImage = sf::IntRect(0, 0, kGhostSize*kPixelsPerCell, kGhostSize*kPixelsPerCell);

// Player data
const int kPlayerHealth = 16;
const int kPlayerSpeed = 10;

// Enemy data
const int kEnemiesPerLevel = 24;
const int kEnemiesPerLevelInOneMoment = 6;
const int kEnemyHealth = 5;
const int kEnemySpeed = 5;
const float kEnemySpawnerSpawnTime = 10.0;
const float kEnemyAIAnalizeTime = 0.5;

// Bullet data
const float kBulletSpeed = 30.0;
const sf::IntRect kBulletImage = sf::IntRect(0, 4 * kPixelsPerCell, kPixelsPerCell, kPixelsPerCell);
