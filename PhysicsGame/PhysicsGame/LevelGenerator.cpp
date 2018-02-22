#include "stdafx.h"
#include "LevelGenerator.h"


LevelGenerator::LevelGenerator()
{
	InitGeneration();

	cout << "level generation scomplete\n";
	cout << "ROOM SIZE: " << m_Rooms.size() << endl;

	for(Room room : m_Rooms)
	{
		cout << "[" << room.rectangle.getPosition().x << "," << room.rectangle.getPosition().y << "]" << endl;
	}
}


LevelGenerator::~LevelGenerator()
{
}

void LevelGenerator::Draw(RenderWindow* pWindow)
{
	for(Room r : m_Rooms)
	{
		pWindow->draw(r.rectangle);
	}
}

void LevelGenerator::InitGeneration()
{
	//make first room
	//pos
	Vector2f pos = { 0.0f,0.0f };
	//size
	int width = rand() % (m_MaxSize - m_MinSize) + m_MinSize;
	int height = rand() % (m_MaxSize - m_MinSize) + m_MinSize;

	float realWidth = width * m_TileWidth;
	float realHeight = height * m_TileWidth;

	Vector2f size{ realWidth, realHeight };

	//rectangle
	RectangleShape rect;
	rect.setPosition(pos);
	rect.setSize(size);
	rect.setOrigin(size / 2.0f);

	//make room
	Room room(rect, false);

	m_Rooms.push_back(room);


	GenerateNewRoom(m_AmountOfRooms);

}

void LevelGenerator::GenerateNewRoom(int iterations)
{
	if(iterations > 0)
	{
		int newIteration = iterations - 1;


		//determine random other room
		int randomRoom = rand() % int(m_Rooms.size());
		//parents
		Room parent = m_Rooms[randomRoom];



		//rand direction
		int dir = rand() % 2;

		//get randomRoom
		RectangleShape newRect = GetRect();

		//determine direction
		if(parent.m_IsDirectionNorthSouth)
		{
			//make new room up or down
			if(dir == 0)
			{
				//go north if available
				if(!parent.m_IsDirection1Used)
				{
					//add north room
					//get new position
					float y = parent.rectangle.getSize().y / 2.0f + newRect.getSize().y / 2.0f + parent.rectangle.getPosition().y + m_RoomOffset;
					float x = parent.rectangle.getPosition().x;
					newRect.setPosition({ x,y });

					newRect.setFillColor(Color::Blue);

					Room newRoom(newRect, false);
					//newRoom.m_IsDirection1Used = true;
					
					parent.m_IsDirection1Used = true;

					m_Rooms.push_back(newRoom);

				}
				else if(!parent.m_IsDirection2Used)
				{
					//add south room
					float y = parent.rectangle.getPosition().y - parent.rectangle.getSize().y / 2.0f - newRect.getSize().y / 2.0f - m_RoomOffset;
					float x = parent.rectangle.getPosition().x;
					newRect.setPosition({ x,y });

					newRect.setFillColor(Color::Green);
					Room newRoom(newRect, false);
					
					//newRoom.m_IsDirection2Used = true;

					parent.m_IsDirection2Used = true;

					m_Rooms.push_back(newRoom);

				}
				else
				{
					GenerateNewRoom(iterations);;
					
				}
			}
			else
			{
				if(!parent.m_IsDirection2Used)
				{
					//add south room
					float y = parent.rectangle.getPosition().y - parent.rectangle.getSize().y / 2.0f - newRect.getSize().y / 2.0f - m_RoomOffset;
					float x = parent.rectangle.getPosition().x;
					newRect.setPosition({ x,y });
					newRect.setFillColor(Color::Green);
					Room newRoom(newRect, false);
					//newRoom.m_IsDirection2Used = true;

					parent.m_IsDirection2Used = true;

					m_Rooms.push_back(newRoom);

				}
				else if(!parent.m_IsDirection1Used)
				{
					//add north room
					float y = parent.rectangle.getSize().y / 2.0f + newRect.getSize().y / 2.0f + parent.rectangle.getPosition().y + m_RoomOffset;
					float x = parent.rectangle.getPosition().x;
					newRect.setPosition({ x,y });
					newRect.setFillColor(Color::Blue);

					Room newRoom(newRect, false);
					//newRoom.m_IsDirection1Used = true;

					parent.m_IsDirection1Used = true;

					m_Rooms.push_back(newRoom);

				}
				else
				{
					GenerateNewRoom(iterations);
					
				}
			}
		}
		else
		{
			//make new room right or left
			if (dir == 0)
			{
				//go right if available
				if (!parent.m_IsDirection1Used)
				{
					//add right room
					float x = parent.rectangle.getPosition().x + parent.rectangle.getSize().x / 2.0f + newRect.getSize().x / 2.0f + m_RoomOffset;
					float y = parent.rectangle.getPosition().y;
					newRect.setPosition(x, y);

					newRect.setFillColor(Color::Red);

					Room newRoom(newRect, true);
					//newRoom.m_IsDirection1Used = true;
					parent.m_IsDirection1Used = true;

					m_Rooms.push_back(newRoom);


				}
				else if(!parent.m_IsDirection2Used)
				{
					//add left room
					float x = parent.rectangle.getPosition().x - parent.rectangle.getSize().x / 2.0f - newRect.getSize().x / 2.0f - m_RoomOffset;
					float y = parent.rectangle.getPosition().y;
					newRect.setPosition(x, y);
					newRect.setFillColor(Color::Cyan);
					Room newRoom(newRect, true);
					//newRoom.m_IsDirection2Used = true;

					parent.m_IsDirection2Used = true;


					m_Rooms.push_back(newRoom);

				}
				else { GenerateNewRoom(iterations);; }
			}
			else
			{
				if (!parent.m_IsDirection2Used)
				{
					//add left room
					//add left room
					float x = parent.rectangle.getPosition().x - parent.rectangle.getSize().x / 2.0f - newRect.getSize().x / 2.0f - m_RoomOffset;
					float y = parent.rectangle.getPosition().y;
					newRect.setPosition(x, y);
					newRect.setFillColor(Color::Cyan);

					Room newRoom(newRect, true);
					//newRoom.m_IsDirection2Used = true;

					parent.m_IsDirection2Used = true;
					
					m_Rooms.push_back(newRoom);

				}
				else if(!parent.m_IsDirection1Used)
				{
					//add right room
					float x = parent.rectangle.getPosition().x + parent.rectangle.getSize().x / 2.0f + newRect.getSize().x / 2.0f + m_RoomOffset;
					float y = parent.rectangle.getPosition().y;
					newRect.setPosition(x, y);
					newRect.setFillColor(Color::Red);

					Room newRoom(newRect, true);
					//newRoom.m_IsDirection1Used = true;

					parent.m_IsDirection1Used = true;

					m_Rooms.push_back(newRoom);

				}
				else { GenerateNewRoom(iterations); }
			}

		}

		GenerateNewRoom(newIteration);
	}
}

RectangleShape LevelGenerator::GetRect()
{
	RectangleShape rs;

	int width = rand() % (m_MaxSize - m_MinSize) + m_MinSize;
	int height = rand() % (m_MaxSize - m_MinSize) + m_MinSize;

	float realWidth = width * m_TileWidth;
	float realHeight = height * m_TileWidth;

	Vector2f size{ realWidth, realHeight };

	rs.setSize(size);
	rs.setOrigin(size / 2.0f);

	return rs;

}
