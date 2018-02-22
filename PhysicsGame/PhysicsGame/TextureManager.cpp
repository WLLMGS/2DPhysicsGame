#include "stdafx.h"
#include "TextureManager.h"

TextureManager* TextureManager::m_pInstance = nullptr;


TextureManager* TextureManager::GetInstance()
{
	if (m_pInstance == nullptr) CreateInstance();
	else return m_pInstance;
}

Texture* TextureManager::GetTexture(const TextureType& type)
{
	return m_pTextures[type];
}

TextureManager::TextureManager()
{
	AddTexture(HERO_0, "Resources/Hero_MachineGun.png");
	AddTexture(BULLET_0, "Resources/Bullet0.png");
	AddTexture(TILES, "Resources/Level.png");
}


TextureManager::~TextureManager()
{
	//delete all textures
	delete m_pInstance;
	m_pInstance = nullptr;
}

void TextureManager::CreateInstance()
{
	m_pInstance = new TextureManager();
}

void TextureManager::AddTexture(const TextureType& type, string path)
{
	Texture* texture = new Texture();
	if (!texture->loadFromFile(path)) cout << "could not instantiate texture: " << path << endl;

	texture->setRepeated(true);

	m_pTextures[type] = texture;
}
