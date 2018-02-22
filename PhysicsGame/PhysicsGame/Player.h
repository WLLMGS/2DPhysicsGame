#pragma once
#include "BulletManager.h"

class Player
{
public:
	Player(float size, Vector2f& startPos, b2World* world,BulletManager* pBulletManager, float speed = 500.0f);
	~Player();
	void Update(float elapsedSec);
	void Draw(RenderWindow* pWindow);
	Vector2f GetPosition() const;
	void SetPosition(Vector2f pos);
private:
	//helper functions
	void HandleControls();
	void HandleShooting();
private:
	//variables
	float m_Speed = 0.0f;

	BulletManager* m_pBulletManager;
	b2World* m_pWorld;

	float m_Cooldown = 0.0f;

	Vector2f m_MousePos;

	float m_Angle = 0.0f;

	const float m_HalfSize = 32.0f;

	RectangleShape m_Entity;


	b2Body* m_pBody;
};

