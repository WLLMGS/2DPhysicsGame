#pragma once

class Entity
{
public:
	Entity(float halfSize, const Vector2f& startPos, b2World* world,int collisionGroup = 1 ,bool isStatic = false);
	virtual ~Entity();
	virtual void Update(float elapsedSec);
	void Draw(RenderWindow* pRenderWindow);
	Vector2f GetPosition() const;
protected:
	float m_HalfWitdh;
	float m_HalfHeight;
	Vector2f m_StartPos;


	RectangleShape m_Entity;


	b2Body* m_pBody;
	

	b2FixtureDef m_fixtureDefine;

};

