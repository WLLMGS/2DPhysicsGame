#include "stdafx.h"

//// PhysicsGame.cpp : Defines the entry point for the console application.
////
//
//#include "stdafx.h"
//#include <SFML/Graphics.hpp>
//#include <Box2D/Box2D.h>
//#include <iostream>
//#include <string>
//
//using namespace std;
//
//int main()
//{
//	//initialize
//	sf::RenderWindow window(sf::VideoMode(800, 800), "physics!!");
//
//	window.setVerticalSyncEnabled(true);
//	
//	sf::Clock clock;
//	int fps{};
//	float elapsedSeconds{};
//	
//	
//	//physics world
//	b2Vec2 gravity(0.0f, 9.81f);
//	
//	b2World world(gravity);
//
//	//ground box
//	b2BodyDef* groundBodyDef;
//	groundBodyDef->position.Set(0.0f, -10.0f);
//	
//	//create body using body definition
//	b2Body* groundBody = world.CreateBody(groundBodyDef);
//
//	//set body shape
//	b2PolygonShape groundBox;
//	groundBox.SetAsBox(50.0f, 10.0f);
//
//	//create fixture
//	groundBody->CreateFixture(&groundBox, 0.0f);
//
//
//	while (window.isOpen())
//	{
//		sf::Event event;
//
//		while(window.pollEvent(event))
//		{
//			if (event.type == sf::Event::Closed) window.close();
//		}
//
//		sf::Time elapsed = clock.restart();
//		
//		elapsedSeconds += elapsed.asSeconds();
//		++fps;
//
//		if(elapsedSeconds > 1.0f)
//		{
//			elapsedSeconds -= 1.0f;
//			cout << "fps: " << fps << endl;
//			fps = 0;
//		}
//
//		
//
//		window.clear();
//
//		//draw something
//		
//		window.display();
//	}
//
//    return 0;
//}
//
