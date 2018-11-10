#include <iostream>
#include <stdio.h>

#include "Triangle.h"
#include "AABB.h"
#include "helpers/FileReader.h"


// The application entry point.
int main(int argc, char* argv[]) 
{
	printf("Hello world, Today Im going to calculate a vector. \n");
	
	T_racer_Vertex v0, v1, v2;
	v0.position = T_racer_Math::Vector3(1.0f, 1.0f, 1.0f);
	v1.position = T_racer_Math::Vector3(0, 0.0f, 10.0f);
	v2.position = T_racer_Math::Vector3(10.0f, 0.0f, 0.0f);

	Triangle test(v0, v1, v2);
	T_racer_Math::Ray      testRay;
	testRay.setPosition(T_racer_Math::Vector3(0.0f, 0.0f, -1.0f));
	testRay.setDirection(T_racer_Math::Vector3(0, -1.0f, 0.0f));
	testRay.setMagnitude(100.0f);

	AABB  bb(T_racer_Math::Vector3(5.0f, 0.0f, 0.0f), T_racer_Math::Vector3(15.0f, 2.0f, 0.0f));
	bb.enlargeBox(T_racer_Math::Vector3(1.0f, 1.0f, 1.0f));
	//testRay.setMagnitude(10.0f);
	
	T_racer_TriangleIntersection isIntersecting = test.isIntersecting(testRay);
	
	if (bb.isIntersected(testRay)) 
	{
		printf("An box intersection has occured lol.");
	}

	if (isIntersecting.intersection) 
	{
		printf("An intersection has occured lol.");
		
	}

	//T_racer_FileBuffer  buffer("test.txt");
	//if (buffer.readFile()) 
	//{
	//	printf("The file was read."); 
	//
	//	std::string test;
	//	buffer.extractData(test, 0, buffer.getBufferSize());
	//}


	getchar();


	return 0;
}