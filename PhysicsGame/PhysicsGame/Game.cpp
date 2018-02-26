#include "stdafx.h"

#include "Game.h"
#include <iostream>
#include "Player.h"
#include "BulletManager.h"
#include "TextureManager.h"

using namespace std;


Game::Game() :
m_LevelGenerator()
{
	m_pWindow = new RenderWindow(VideoMode(1920, 1080), "phyics test");

	//m_pWindow->setVerticalSyncEnabled(true);

	//create world
	b2Vec2 gravity(0.0f, 0.0f);
	m_pWorld = new b2World(gravity);

	//create groundbox
	b2BodyDef bodyDef;
	bodyDef.type = b2_staticBody;
	bodyDef.position.Set(0.0f, 200.0f);

	m_pGroundBody = m_pWorld->CreateBody(&bodyDef);

	b2PolygonShape groundShape;

	groundShape.SetAsBox(50.0f, 10.0f);

	b2FixtureDef fixtureGround;

	fixtureGround.shape = &groundShape;
	fixtureGround.filter.groupIndex = 10;


	m_pGroundBody->CreateFixture(&fixtureGround);


	//create rectangleshape for groundbox;
	m_RectGroundBox.setSize(Vector2f(100.0f, 20.0f));
	m_RectGroundBox.setPosition(0.0f, 200.0f);
	m_RectGroundBox.setOrigin(Vector2f(50.0f, 10.0f));


	m_pEntity1 = new Entity(32.0f, Vector2f(500.0f, 500.0f), m_pWorld,1, false);


	m_pBulletManager = new BulletManager();
	m_pPlayer = new Player(32.0f, Vector2f(64.0f, 64.0f), m_pWorld, m_pBulletManager);

	m_pPlayer->SetPosition(m_LevelGenerator.GetPlayerSpawn());

	//create view
	m_View.setCenter(m_pPlayer->GetPosition());
	m_View.setSize(1080.0f, 720.0f);

	cout << sizeof(TextureManager::GetInstance()->GetTexture(HERO_0)) << endl;
}

Game::~Game()
{
	delete m_pPlayer;
	m_pPlayer = nullptr;
	delete m_pBulletManager;
	m_pBulletManager = nullptr;
	delete m_pEntity1;
	m_pEntity1 = nullptr;

}

void Game::Run()
{
	Clock clock;
	float deltaTime{};
	
	while (m_pWindow->isOpen())
	{
		deltaTime = clock.restart().asSeconds();
		ProcessEvents();
		Update(deltaTime);
		Draw();
	}
}

void Game::ProcessEvents()
{
	Event event{};
	while (m_pWindow->pollEvent(event))
	{
		if (event.type == Event::Closed) m_pWindow->close();
	}
}
void Game::Update(float deltaTime)
{
	//testing contacts
	for (b2Contact* c = m_pWorld->GetContactList(); c; c->GetNext())
	{
		int uid = int(c->GetFixtureB()->GetBody()->GetUserData());

		if(uid == 12)
		{
			
			break;
		}
		else if (uid == 13)
		{
			c->GetFixtureB()->GetBody()->SetActive(false);
			//apply force to other obj later
			break;
		}
		break;
	}

	//update world sim
	m_pWorld->Step(deltaTime, m_velocityIterations, m_positionIterations);

	m_pEntity1->Update(deltaTime);
	m_pPlayer->Update(deltaTime);
	m_pBulletManager->Update(deltaTime);

	//update view
	m_View.setCenter(m_pPlayer->GetPosition());

	
}

void Game::Draw()
{
	m_pWindow->clear();
	m_pWindow->setView(m_View);
	m_LevelGenerator.Draw(m_pWindow);
	
	m_pEntity1->Draw(m_pWindow);
	m_pPlayer->Draw(m_pWindow);
	m_pBulletManager->Draw(m_pWindow);

	m_pWindow->draw(m_RectGroundBox);
	m_pWindow->display();
}