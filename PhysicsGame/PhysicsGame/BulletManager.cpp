#include "stdafx.h"
#include "BulletManager.h"


BulletManager::BulletManager()
{
}


BulletManager::~BulletManager()
{
	for(Bullet* b : m_pBullets)
	{
		delete b;
		b = nullptr;
	}
}

void BulletManager::Update(float elapsedSec)
{
	for(size_t i{}; i < m_pBullets.size(); ++i)
	{
		if(!m_pBullets[i]->IsDead())
		{
			m_pBullets[i]->Update(elapsedSec);
		}
		else
		{
			Remove(i);
		}

	}
}

void BulletManager::Draw(RenderWindow* pWindow)
{
	for (Bullet* b : m_pBullets) b->Draw(pWindow);
}

void BulletManager::PushBack(Bullet* bullet)
{
	m_pBullets.push_back(bullet);
}


void BulletManager::Remove(size_t t)
{
	cout << "bullet removed\n";

	delete m_pBullets[t];
	m_pBullets[t] = nullptr;

	m_pBullets.erase(m_pBullets.begin() + t);
}
