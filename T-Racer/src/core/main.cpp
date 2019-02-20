#include <iostream>
#include <stdio.h>

#include "helpers/Math_Matrix.h"
#include "Window.h"
#include "PFMDisplay.h"
#include "TGADisplay.h"
#include "Scene.h"
#include "TextureManager.h"
#include "AABB.h"
#include "helpers/Math_Sampler.h"
#include "PathTracer.h"
#include "PointLight.h"
#include "AreaLight.h"


// The application entry point.
int main(int argc, char* argv[]) 
{
	// A SET OF TODOs:
	// 1. Add parameterisation to the renderer so that parameters can be set for the renderer.
	// 2. Add abstraction for objects such as the window for multiplatform movement.

	T_racer_Math::Vector testvec(1.0f, 1.0f, 1.0f, 1.0f);
	T_racer_Math::Matrix4X4  matTest;
	T_racer_Math::Matrix4X4  matTest2;

	T_racer_Math::Matrix4X4 testmat3
	(
		2, 5, -8, 1,
		1, 2, -3, 1,
		-3, -5, 2, 1,
		1, 1, 1, 1
	);

	T_racer_Math::getInverseMatrix(testmat3);

	Image test(800, 600, T_racer_Math::Colour(0.0f,0.0f,0.0f));
	Image test2; 

	test2 = test;

	T_racer_Display_Window  window;
	T_racer_Display_TGA  tga;
	T_racer_Display_PFM  pfm;
	T_racer_Camera  testCam;
	
	// lights
	T_racer_Light_Point*  light1 = new T_racer_Light_Point();
	T_racer_Light_Area*   aLight = new T_racer_Light_Area();
	
	T_racer_Vertex  a;
	a.position = T_racer_Math::Vector(1.015684, 2.612167, 1.082442);
	T_racer_Vertex  b;
	b.position = T_racer_Math::Vector(1.015684, 2.612167, 1.583131);
	T_racer_Vertex  c;
	c.position = T_racer_Math::Vector(1.635585, 2.612167, 1.082442);
	aLight->addTriangle(a, b, c);
	
	light1->setPosition(T_racer_Math::Vector(1.2f, 1.2f, 0.4f));

	window.init(512, 512);

	tga.init(1920, 1080);
	tga.setDisplayName("Test.tga");
	pfm.init(1920, 1080);
	pfm.setDisplayName("Test.pfm");

	T_racer_Renderer_PathTracer  trpt;

	T_racer_Scene testScene;
	testScene.setName("Cycles");
	testScene.setMainCamera(&testCam);

	testScene.addLight(aLight);
	testScene.loadModelAssimp("resources/Cycles.obj");

	trpt.setDisplay(&window);
	trpt.setScene(&testScene);
	trpt.Render();

	while (!window.shouldQuit())
	{
		window.update();
	}


	//pfm.init(1920, 1080);
	//pfm.setDisplayName("Test.pfm");
	//pfm.writeToDisplay(&test);

	
	return 0;
}