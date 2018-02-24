#include "stdafx.h"
#include "Player.h"

#include "TextureManager.h"

Player::Player(float size, Vector2f& startPos, b2World* world, BulletManager* pBulletManager, float speed) : 
m_Speed(speed),
m_pBulletManager(pBulletManager),
m_pWorld(world)
{
	m_Entity.setTexture(TextureManager::GetInstance()->GetTexture(HERO_0));


	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(startPos.x, startPos.y);
	bodyDef.allowSleep = false;
	bodyDef.active = true;
	bodyDef.linearDamping = 1.0f;
	bodyDef.bullet = true;
	
	m_pBody = world->CreateBody(&bodyDef);
	int i = 12;
	m_pBody->SetUserData((void*)i);


	b2PolygonShape bodyBox;
	bodyBox.SetAsBox(m_HalfSize / 2.0f, m_HalfSize / 2.0f);



	b2FixtureDef fixtureDef;

	fixtureDef.userData = "hello world";
	fixtureDef.shape = &bodyBox;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 1.0f;
	fixtureDef.restitution = 1.0f;

	fixtureDef.filter.groupIndex = -2;

	m_pBody->CreateFixture(&fixtureDef);


	//create m_Rectangle shape
	m_Entity.setSize(Vector2f(size * 2.0f, size * 2.0f));
	m_Entity.setPosition(startPos);
	m_Entity.setOrigin(Vector2f(size, size));
}
Player::~Player()
{
}
void Player::Update(float elapsedSec)
{
	//change pos of rect
	Vector2f newPos(m_pBody->GetPosition().x, m_pBody->GetPosition().y);

	
	HandleControls();
	HandleShooting();

	m_Cooldown += elapsedSec;
	
	m_pBody->SetTransform(m_pBody->GetPosition(), m_Angle);
	m_Entity.setPosition(newPos);
	m_Entity.setRotation((m_pBody->GetAngle() * 180.0f / b2_pi) - 90.0f);

}


void Player::Draw(RenderWindow* pWindow)
{
	pWindow->draw(m_Entity);
	m_MousePos = pWindow->mapPixelToCoords(Mouse::getPosition());
}

Vector2f Player::GetPosition() const
{
	return m_Entity.getPosition();
}

void Player::SetPosition(Vector2f pos)
{
	m_pBody->SetTransform(b2Vec2(pos.x, pos.y), m_Angle);
}


void Player::HandleControls()
{
	b2Vec2 velocity{};

	if (Keyboard::isKeyPressed(Keyboard::Space)) m_pBody->ApplyLinearImpulse(b2Vec2(10000.0f, 0.0f), m_pBody->GetWorldCenter(), true);

	if (Keyboard::isKeyPressed(Keyboard::Z))
	{
		velocity.y = -m_Speed;
	}
	else if (Keyboard::isKeyPressed(Keyboard::S))
	{
		velocity.y = m_Speed;
	}
	else
	{
		velocity.y = 0.0f;
	}

	if (Keyboard::isKeyPressed(Keyboard::Q))
	{
		velocity.x = -m_Speed;
	}
	else if (Keyboard::isKeyPressed(Keyboard::D))
	{
		velocity.x = m_Speed;
	}
	else
	{
		velocity.x = 0.0f;
	}

	m_pBody->SetLinearVelocity(velocity);

	
}

void Player::HandleShooting()
{
	Vector2f differenceVector(m_MousePos.x - m_Entity.getPosition().x,m_MousePos.y - m_Entity.getPosition().y);

	m_Angle = atan2f(differenceVector.y, differenceVector.x);

	if(Mouse::isButtonPressed(Mouse::Left))
	{
		if(m_Cooldown > 0.25f)
		{
			m_Cooldown = 0.0f;
			m_pBulletManager->PushBack(new Bullet(16.0, m_Entity.getPosition(), m_pWorld, m_Angle));
		}
	}
}
