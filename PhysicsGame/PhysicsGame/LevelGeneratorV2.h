#pragma once
#include "TextureManager.h"

class Room
{
public:

	Room(const RectangleShape& rs) : rectangle(rs)
	{
		Texture* t = TextureManager::GetInstance()->GetTexture(TILES);
		
		
		IntRect textureRect(0, 0, 16, 16);
		
		rectangle.setTexture(t);
		rectangle.setTextureRect(textureRect);

		float tilesW = rs.getSize().x / TileSize;
		float tileV = rs.getSize().y / TileSize;

		Vector2f startPos;
		startPos.x = rs.getPosition().x - rs.getSize().x / 2.0f;
		startPos.y = rs.getPosition().y - rs.getSize().y / 2.0f;

		for(int x{}; x < tilesW; ++x)
		{
			for(int y{}; y < tileV; ++y)
			{
				RectangleShape* rs = new RectangleShape();

				rs->setSize(Vector2f(TileSize, TileSize));
				rs->setOrigin(Vector2f(TileSize, TileSize) / 2.0f);
				rs->setPosition(Vector2f(startPos.x + (TileSize * x), startPos.y + (TileSize * y)));
				rs->setTexture(t);
				rs->setTextureRect(textureRect);
				rectangles.push_back(rs);
			}
		}
	}
	
	void Draw(RenderWindow* pWindow)
	{
		for(int i{}; i < rectangles.size(); ++i)
		{
			pWindow->draw(*rectangles[i]);
		}
	}

	RectangleShape rectangle;
	const float TileSize = 64.0f;
	
	vector<RectangleShape*> rectangles;
	
};


enum RoomDirection
{
	North = 1,
	South = 2,
	East = 3,
	West = 4
};


class LevelGeneratorV2
{
public:
	LevelGeneratorV2();
	~LevelGeneratorV2();

	void Draw(RenderWindow* pWindow);

	void DetermineFirstRoom();
	void DetermineOtherRooms(int iterations);
	void GenerateRooms();

	vector<int> CheckSurroundingRooms(int x, int y);
	bool IsRoomEmpty(int x, int y);

	Vector2f GetPlayerSpawn() const;

	vector<Room> m_Rooms;
private:
	const static int m_Width = 15;
	const static int m_Height = 15;
	int m_RoomMap[m_Width][m_Height];

	int m_StartX = 0;
	int m_StartY = 0;

	vector<pair<int, int>> m_RoomLocations;

	int m_AmountOfRooms = 10;

	const float m_TileSize = 64.0f;
	const int m_GridSize = 24;
	const int m_MinRoomSize = 15;
	const int m_MaxRoomSize = 19;

	

};

