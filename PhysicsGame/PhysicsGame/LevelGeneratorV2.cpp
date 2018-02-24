#include "stdafx.h"
#include "LevelGeneratorV2.h"
#include <stdlib.h>


LevelGeneratorV2::LevelGeneratorV2(b2World* pWorld) :
m_pWorld(pWorld)
{
	DetermineFirstRoom();
	DetermineOtherRooms(m_AmountOfRooms);
	GenerateRooms();
}


LevelGeneratorV2::~LevelGeneratorV2()
{}

void LevelGeneratorV2::Draw(RenderWindow* pWindow)
{
	for(int i{}; i < m_Rooms.size(); ++i)
	{
		m_Rooms[i].Draw(pWindow);
	}

}

void LevelGeneratorV2::DetermineFirstRoom()
{
	m_StartX = rand() % m_Width;
	m_StartY = rand() % m_Height;

	m_RoomMap[m_StartX][m_StartY] = 1;

	m_RoomLocations.push_back(make_pair(m_StartX, m_StartY));
}

void LevelGeneratorV2::DetermineOtherRooms(int iterations)
{
	if(iterations > 0)
	{
		int newIteration = iterations - 1;


		int randIndex = rand() % int(m_RoomLocations.size());
		int x = m_RoomLocations[randIndex].first;
		int y = m_RoomLocations[randIndex].second;


		//check if any surrounding rooms available
		vector<int> surroundings = CheckSurroundingRooms(x, y);

		//if no room available
		if(surroundings.empty())
		{
			DetermineOtherRooms(iterations);
		}
		else
		{
			int randRoom = surroundings[rand() % surroundings.size()];

			switch (randRoom)
			{
			case North:
				m_RoomMap[x][y + 1] = 1;
				m_RoomLocations.push_back(make_pair(x, y + 1));
				break;
			case South:
				m_RoomMap[x][y - 1] = 1;
				m_RoomLocations.push_back(make_pair(x, y - 1));
				break;
			case East:
				m_RoomMap[x+1][y ] = 1;
				m_RoomLocations.push_back(make_pair(x + 1, y));
				break;
			case West:
				m_RoomMap[x - 1][y] = 1;
				m_RoomLocations.push_back(make_pair(x - 1, y));
				break;
			}
			//continue
			DetermineOtherRooms(newIteration);
		}
		;
	}
}

void LevelGeneratorV2::GenerateRooms()
{
	for(pair<int, int>& p : m_RoomLocations)
	{
		int x = p.first;
		int y = p.second;

		//m_Rectangle
		RectangleShape rectRoom;

		//step 1: determine random size
		int randWidth = rand() % (m_MaxRoomSize - m_MinRoomSize) + m_MinRoomSize;
		int randHeight = rand() % (m_MaxRoomSize - m_MinRoomSize) + m_MinRoomSize;
		
		float xSize = randWidth * m_TileSize;
		float ySize = randHeight * m_TileSize;

		//step 2: determine position
		float xPos = x * m_GridSize * m_TileSize + (m_GridSize * m_TileSize) / 2.0f;
		float yPos = y * m_GridSize * m_TileSize + (m_GridSize * m_TileSize) / 2.0f;

		rectRoom.setPosition(Vector2f(xPos, yPos));
		rectRoom.setSize(Vector2f(xSize, ySize));
		rectRoom.setOrigin(Vector2f(xSize, ySize) / 2.0f);

		Room room = Room(rectRoom, m_pWorld);

		m_Rooms.push_back(room);
		
	}
}

vector<int> LevelGeneratorV2::CheckSurroundingRooms(int x, int y)
{
	vector<int> result;
	//north = 1
	//sout = 2
	//east = 3
	//west = 4

	//check north
	if(y < m_Height-2 && IsRoomEmpty(x, y + 1))
	{
		result.push_back(North);
	}
	//check south
	if(y > 1 && IsRoomEmpty(x, y - 1))
	{
		result.push_back(South);
	}
	//check east
	if(x < m_Width - 2 && IsRoomEmpty(x + 1, y))
	{
		result.push_back(East);
	}
	//check west
	if(x > 1 && IsRoomEmpty(x - 1, y))
	{
		result.push_back(West);
	}

	return result;
}

bool LevelGeneratorV2::IsRoomEmpty(int x, int y)
{
	if (m_RoomMap[x][y] == 0) return true;

	return false;
}

Vector2f LevelGeneratorV2::GetPlayerSpawn() const
{
	float startX = m_StartX * m_GridSize * m_TileSize + (m_GridSize * m_TileSize) / 2.0f;
	float startY = m_StartY * m_GridSize * m_TileSize + (m_GridSize * m_TileSize) / 2.0f;

	return Vector2f(startX, startY);
}

