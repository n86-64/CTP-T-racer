#include <iostream>
#include <stdio.h>

#include "Triangle.h"

// The application entry point.
int main(int argc, char* argv[]) 
{
	printf("Hello world, Today Im going to calculate a vector. \n");
	
	T_racer_Vertex v0, v1, v2;
	v0.position = T_racer_Math::Vector3(0, 0, 0);
	v1.position = T_racer_Math::Vector3(0, 0, 1);
	v2.position = T_racer_Math::Vector3(1, 0, 0);

	Triangle test(v0, v1, v2);
	T_racer_Math::Ray      testRay;
	testRay.setPosition(T_racer_Math::Vector3(0, 1, 0));
	testRay.setDirection(T_racer_Math::Vector3(0, -1, 0));

	T_racer_TriangleIntersection isIntersecting = test.isIntersecting(testRay);

	if (isIntersecting.intersection) 
	{
		printf("An intersection has occured lol.");
		
	}

	getchar();


	return 0;
}