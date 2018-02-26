#include "stdafx.h"
#include "Bullet.h"
#include "TextureManager.h"

Bullet::Bullet(float halfSize, const Vector2f& startPos, b2World* world, const float angle) :
Entity(halfSize, startPos, world,-2),
m_Angle(angle)
{
	m_Entity.setTexture(TextureManager::GetInstance()->GetTexture(BULLET_0));

	int i = 13;

	m_pBody->SetUserData((void*)i);

}

Bullet::~Bullet()
{

}

void Bullet::Update(float elapsedSec)
{
	if(m_pBody->IsActive())
	{
		//change pos of rect
		Vector2f newPos(m_pBody->GetPosition().x, m_pBody->GetPosition().y);

		m_pBody->SetTransform(m_pBody->GetPosition(), m_Angle);

		m_Entity.setPosition(newPos);
		m_Entity.setRotation(m_Angle * 180.0f / b2_pi + 90.0f);

		//handle movement
		HandleMovement();
	}
	else
	{
		m_IsDead = true;
	}
	

}

bool Bullet::IsDead() const
{
	return m_IsDead;
}

void Bullet::HandleMovement()
{
	if(m_pBody->IsActive())
	{
		m_pBody->SetLinearVelocity(b2Vec2(cos(m_Angle) * m_Speed, sin(m_Angle) * m_Speed));
	}
	
}
