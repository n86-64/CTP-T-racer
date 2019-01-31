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
	T_racer_Light_Point* light1 = new T_racer_Light_Point();
	light1->setPosition(T_racer_Math::Vector(0.0f, 0.0f, -2.0f));


	window.init(800, 600);
//	window.writeToDisplay(&test);

	T_racer_Renderer_PathTracer  trpt;

	T_racer_Scene testScene;
	testScene.setName("Cubey");
	testScene.setMainCamera(&testCam);

	testScene.addLight(light1);
	testScene.loadModel("resources/bunny.obj");

	trpt.setDisplay(&window);
	trpt.setScene(&testScene);
	trpt.Render();

	//testScene.setDisplay(&window);
	//testScene.Render();

	while (!window.shouldQuit())
	{
		window.update();
	}

	//tga.init(1920, 1080);
	//tga.setDisplayName("Test.tga");
	//testScene.setDisplay(&tga);
	//testScene.Render();

	//pfm.init(1920, 1080);
	//pfm.setDisplayName("Test.pfm");
	//pfm.writeToDisplay(&test);

	
	return 0;
}