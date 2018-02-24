#pragma once
#include "TextureManager.h"

class Room
{
public:

	Room(const RectangleShape& rs, b2World* pWorld) : m_Rectangle(rs), m_pWorld(pWorld)
	{
		Texture* t = TextureManager::GetInstance()->GetTexture(FLOORTILE_1);
		t->setRepeated(true);
		t->setSmooth(false);

		Vector2f size = m_Rectangle.getSize();

		//divide size of room bij (tilesize / texture size = 64 / 16 = 4.0f)
		float width = size.x / 4.0f;
		float height = size.y / 4.0f;

		IntRect textureRect(0, 0, width, height);

		m_Rectangle.setTexture(t);
		m_Rectangle.setTextureRect(textureRect);

		GenerateRoomBorders();
	}
	
	void Draw(RenderWindow* pWindow)
	{
		pWindow->draw(m_Rectangle);

		//draw walls
		for(RectangleShape& rs : m_Walls)
		{
			pWindow->draw(rs);
		}
	}

private:
	RectangleShape m_Rectangle;
	const float m_TileSize = 64.0f;
	b2World* m_pWorld;
	vector<RectangleShape> m_Walls;
private:
	void GenerateRoomBorders()
	{
		Texture* t = TextureManager::GetInstance()->GetTexture(WALLTILE_1);
		t->setRepeated(true);

		float tSizeX = (m_Rectangle.getSize().x + (m_TileSize)) / 4.0f;
		float tSizeY = m_TileSize / 4.0f;

		IntRect textureRectHorz = IntRect(0, 0, tSizeX, tSizeY);
		IntRect textureRectVert = IntRect(0, 0, tSizeY, tSizeX);

		float width = m_Rectangle.getSize().x / m_TileSize;
		float height = m_Rectangle.getSize().y / m_TileSize;

		float minHeight = m_Rectangle.getPosition().y /*- (m_Rectangle.getSize().y / 2.0f)*/;
		float maxHeight = m_Rectangle.getPosition().y + (m_Rectangle.getSize().y / 2.0f);

		float minWidth = m_Rectangle.getPosition().x - (m_Rectangle.getSize().x / 2.0f);
		float maxWidth = m_Rectangle.getPosition().x + (m_Rectangle.getSize().x / 2.0f);

		Vector2f wallSizeVert = Vector2f(m_TileSize, m_Rectangle.getSize().y);
		Vector2f wallSizeHorz = Vector2f(m_Rectangle.getSize().x, m_TileSize);
		//west = minHeight - max height on x = 0.0f and width = tilesize

		//vert walls (redo these)
		RectangleShape west;
		west.setPosition(minWidth, minHeight);
		west.setSize(wallSizeVert);
		west.setOrigin(wallSizeVert / 2.0f);

		west.setTexture(t);
		west.setTextureRect(textureRectVert);

		m_Walls.push_back(west);
		
		RectangleShape east;
		east.setPosition(maxWidth, minHeight);
		east.setSize(wallSizeVert);
		east.setOrigin(wallSizeVert / 2.0f);

		east.setTexture(t);
		east.setTextureRect(textureRectVert);

		
		m_Walls.push_back(east);

		//horz walls
		RectangleShape north;
		north.setPosition(m_Rectangle.getPosition().x, m_Rectangle.getPosition().y + m_Rectangle.getSize().y / 2.0f);
		north.setSize(Vector2f(m_Rectangle.getSize().x + (m_TileSize), m_TileSize));
		north.setOrigin(north.getSize() / 2.0f);
		
		//settexture test
		north.setTexture(t);
		north.setTextureRect(textureRectHorz);

		m_Walls.push_back(north);

		RectangleShape south;
		south.setPosition(m_Rectangle.getPosition().x, m_Rectangle.getPosition().y - m_Rectangle.getSize().y / 2.0f);
		south.setSize(Vector2f(m_Rectangle.getSize().x + (m_TileSize), m_TileSize));
		south.setOrigin(north.getSize() / 2.0f);
	
		south.setTexture(t);
		south.setTextureRect(textureRectHorz);

		m_Walls.push_back(south);

	}
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
	LevelGeneratorV2(b2World* pWorld);
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

	//physics world
	b2World* m_pWorld;

};

