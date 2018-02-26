#pragma once
#include "Bullet.h"

class BulletManager
{
public:
	BulletManager();
	~BulletManager();
	void Update(float elapsedSec);
	void Draw(RenderWindow* pWindow);
	void PushBack(Bullet* bullet);
private:
	vector<Bullet*> m_pBullets;

private:
	void Remove(size_t t);
	
};

