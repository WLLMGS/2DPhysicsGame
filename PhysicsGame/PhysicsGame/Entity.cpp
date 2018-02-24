#include "stdafx.h"
#include "Entity.h"


Entity::Entity(float halfSize, const Vector2f& startPos, b2World* world,int collisionGroup, bool isStatic) :
m_HalfWitdh(halfSize),
m_HalfHeight(halfSize),
m_StartPos(startPos)
{
	b2BodyDef bodyDef;
	bodyDef.type = (!isStatic) ? b2_dynamicBody : b2_staticBody;
	bodyDef.position.Set(m_StartPos.x, m_StartPos.y);
	bodyDef.allowSleep = false;
	bodyDef.active = true;
	bodyDef.linearDamping = 1.0f;
	bodyDef.bullet = true;
	bodyDef.userData = "hello world";


	m_pBody = world->CreateBody(&bodyDef);

	b2PolygonShape bodyBox;
	bodyBox.SetAsBox(halfSize / 2.0f, halfSize / 2.0f);

	m_fixtureDefine.userData = this;
	m_fixtureDefine.shape = &bodyBox;
	m_fixtureDefine.density = 1.0f;
	m_fixtureDefine.friction = 1.0f;
	m_fixtureDefine.restitution = 1.0f;

	m_fixtureDefine.filter.groupIndex = collisionGroup;

	m_pBody->CreateFixture(&m_fixtureDefine);

	//create m_Rectangle shape
	m_Entity.setSize(Vector2f(m_HalfWitdh * 2.0f, m_HalfHeight * 2.0f));
	m_Entity.setPosition(m_StartPos);
	m_Entity.setOrigin(Vector2f(m_HalfWitdh, m_HalfHeight));

}

Entity::~Entity()
{
	m_pBody = nullptr;
}

void Entity::Update(float elapsedSec)
{
	//change pos of rect
	Vector2f newPos(m_pBody->GetPosition().x, m_pBody->GetPosition().y);

	m_Entity.setPosition(newPos);

	if(Keyboard::isKeyPressed(Keyboard::Space))
	{
		m_pBody->ApplyLinearImpulseToCenter(b2Vec2(10000.0f, 10000.0f), true);
	}
}

void Entity::Draw(RenderWindow* pRenderWindow)
{
	if(m_pBody->IsActive())
	{
		pRenderWindow->draw(m_Entity);
	}
}

Vector2f Entity::GetPosition() const
{
	return m_Entity.getPosition();
}
