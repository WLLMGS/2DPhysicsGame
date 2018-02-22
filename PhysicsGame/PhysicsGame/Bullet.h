#pragma once
#include "Entity.h"
class Bullet : public Entity
{
public:
	Bullet(float halfSize, const Vector2f& startPos, b2World* world, const float angle);
	virtual ~Bullet();
	virtual void Update(float elapsedSec);
	bool IsDead() const;

private:
	void HandleMovement();

private:
	const float m_Speed = 1250.0f;
	float m_Angle;
	const float m_HalfSize = 16.0f;

	bool m_IsDead = false;
};

