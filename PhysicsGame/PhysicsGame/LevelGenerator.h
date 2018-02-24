#pragma once

struct Room
{
	Room(const RectangleShape& rect, bool northSouth) :
	m_Rectangle(rect),
	m_IsDirectionNorthSouth(northSouth),
	m_IsDirection1Used(false),
	m_IsDirection2Used(false)
	{}

	RectangleShape m_Rectangle;
	bool m_IsDirectionNorthSouth;
	bool m_IsDirection1Used;
	bool m_IsDirection2Used;
};


class LevelGenerator
{
public:
	LevelGenerator();
	~LevelGenerator();
	void Draw(RenderWindow* pWindow);
	void InitGeneration();
private:
	
	const int m_MinSize = 10;
	const int m_MaxSize = 16;

	const float m_TileWidth = 64.0f;
	const float m_RoomOffset = m_TileWidth * 5.0f;


	vector<Room> m_Rooms;


	const int m_AmountOfRooms = 5;

private:
	void GenerateNewRoom(int iterations);
	RectangleShape GetRect();

};

