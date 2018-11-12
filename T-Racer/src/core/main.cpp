#include <iostream>
#include <stdio.h>

#include "Window.h"

#include "Triangle.h"
#include "AABB.h"

// The application entry point.
int main(int argc, char* argv[]) 
{
	//printf("Hello world, Today Im going to calculate a vector. \n");
	//
	//T_racer_Vertex v0, v1, v2;
	//v0.position = T_racer_Math::Vector3(1.0f, 1.0f, 1.0f);
	//v1.position = T_racer_Math::Vector3(0, 0.0f, 10.0f);
	//v2.position = T_racer_Math::Vector3(10.0f, 0.0f, 0.0f);

	//Triangle test(v0, v1, v2);
	//T_racer_Math::Ray      testRay;
	//testRay.setPosition(T_racer_Math::Vector3(0.0f, 0.0f, -1.0f));
	//testRay.setDirection(T_racer_Math::Vector3(0, -1.0f, 0.0f));
	//testRay.setMagnitude(100.0f);

	//AABB  bb(T_racer_Math::Vector3(5.0f, 0.0f, 0.0f), T_racer_Math::Vector3(15.0f, 2.0f, 0.0f));
	//bb.enlargeBox(T_racer_Math::Vector3(1.0f, 1.0f, 1.0f));
	////testRay.setMagnitude(10.0f);
	//
	//T_racer_TriangleIntersection isIntersecting = test.isIntersecting(testRay);
	//
	//if (bb.isIntersected(testRay)) 
	//{
	//	printf("An box intersection has occured lol.");
	//}

	//if (isIntersecting.intersection) 
	//{
	//	printf("An intersection has occured lol.");
	//	
	//}

	//getchar();
	

	// A SET OF TODOs:
	// 1. Add parameterisation to the renderer so that parameters can be set for the renderer.
	// 2. Add abstraction for objects such as the window for multiplatform movement.

	//bool quit = false;
	//sf::RenderWindow  window(sf::VideoMode(800,600),"T-racer");
	//sf::Event   winEvent;


	//while (!quit) 
	//{
	//	while (window.pollEvent(winEvent)) 
	//	{
	//		switch (winEvent.type) 
	//		{
	//		case sf::Event::Closed:
	//			quit = true;
	//			break;
	//		}
	//	}

	//	window.clear(sf::Color(255,0,0)); // Clear the screen.
	//	window.display();
	//}

	T_racer_Display_Window  window;
	window.init(1920, 1080);
	
	while (!window.shouldQuit()) 
	{
		window.update();
	}

	
	return 0;
}