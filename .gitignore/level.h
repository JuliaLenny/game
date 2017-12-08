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
const int kPixels = 15;

const unsigned char	CellSymbol_Player = '1';
const unsigned char	CellSymbol_Ghost = 'T';
const unsigned char	CellSymbol_BrickWall = '#';
const unsigned char	CellSymbol_SteelWall = '@';
const unsigned char	CellSymbol_Enemy = 'S';


const unsigned char kLevelData0[kLevelRows][kLevelColumns + 1] =
{
	"@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@",
	"@S                                @@                              S  @",
	"@                                 @@                                 @",
	"@                                 @@                                 @",
	"@                                          S        @@@@             @",
	"@                                                   @                @",
	"@                                                   @                @",
	"@@@@@@@@@@@@@@@@@@@@@@@@@@@@                        @                @",
	"@                         @                         @                @",
	"@                         @                         @                @",
	"@                         @                          @@@@@@@@        @",
	"@                         @                                          @",
	"@            @            @@@@@                                      @",
	"@            @                                                       @",
	"@            @                                                       @",
	"@            @                           @@@@@@@@@@@@@@@@@@@@@@@@@@@@@",
	"@   S        @                                      @                @",
	"@            @                                       @               @",
	"@            @                @                      @               @",
	"@@@@@@@@@@@@@@@@         @    @                      @               @",
	"@                        @                           @               @",
	"@                        @                           @               @",
	"@                   @@@@@@                            @@@@           @",
	"@                   @                                    @@          @",
	"@                   @                                                @",
	"@                   @                                         S      @",
	"@@@@@@@@@@@@@@@@@@@@@                    @@                          @",
	"@             @                         @@                           @",
	"@         1   @                        @@                            @",
	"@             @                       @@               @@@           @",
	"@                                    @@                @@@           @",
	"@                                   @@                @              @",
	"@                                  @@                 @              @",
	"@                                 @@                  @              @",
	"@             @                  @@                   @              @",
	"@             @                 @@                    @              @",
	"@             @               @@                     @               @",
	"@             @               @                      @               @",
	"@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@",
};


const sf::IntRect kBrickWallImage = sf::IntRect(0, 3 * kPixels, kPixels, kPixels);
const sf::IntRect kSteelWallImage = sf::IntRect(kPixels, 3 * kPixels, kPixels, kPixels);

// Ghost's data
const float kGhostRecoveryTime = 0.5; //FireCooldown воссстановление
const int kGhostSize = 3; //размер призрака
const sf::IntRect kGhostImage = sf::IntRect(0, 0, kGhostSize*kPixels, kGhostSize*kPixels);

// Player data
const int kPlayerHealth = 16; //здоровье
const int kPlayerSpeed = 10; //скорость

							 // Enemy data
const int kEnemiesLevel = 10;  //количество врагов    
const int kEnemiesLevelInOneMoment = 6; //масимальное кооличество врагов в один момент  
const int kEnemyHealth = 5; //здоровье врага
const int kEnemySpeed = 5;  //скорость врагов
const float kEnemyEmergenceTime = 10.0; // востанновление
const float kEnemyAIAnalizeTime = 0.5;

// Bullet data
const float kBulletSpeed = 30.0;
const sf::IntRect kBulletImage = sf::IntRect(0, 4 * kPixels, kPixels, kPixels);
