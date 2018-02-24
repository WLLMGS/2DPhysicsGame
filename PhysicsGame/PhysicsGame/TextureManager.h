#pragma once
#include <map>

enum TextureType
{
	HERO_0 = 0,
	BULLET_0 = 1,
	TILES = 2,
	FLOORTILE_1 = 3,
	WALLTILE_1 = 4

};

class TextureManager
{
public:
	static TextureManager* GetInstance();
	Texture* GetTexture(const TextureType& type);
	~TextureManager();

private:
	TextureManager();
	
	static void CreateInstance();

	static TextureManager* m_pInstance;

	void AddTexture(const TextureType& type, string path);

	map<TextureType, Texture*> m_pTextures;

};

