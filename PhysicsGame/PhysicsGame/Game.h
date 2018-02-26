#pragma once

#include "Entity.h"
#include "LevelGeneratorV2.h"

class Player;
class BulletManager;

class Game
{
public:
	Game();
	~Game();
	void Run();
private:
	//functions
	void ProcessEvents();
	void Update(float deltaTime);
	void Draw();

	
	//members
	RenderWindow* m_pWindow;
	View m_View;

	//box2d
	b2World* m_pWorld;
	b2Body* m_pGroundBody;

	RectangleShape m_RectGroundBox;

	int m_velocityIterations = 1;
	int m_positionIterations = 1;

	//entity
	Entity* m_pEntity1;


	Player* m_pPlayer = nullptr;
	BulletManager* m_pBulletManager = nullptr;

	//testing level gen
	LevelGeneratorV2 m_LevelGenerator;

};

