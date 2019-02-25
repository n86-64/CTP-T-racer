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

#include "helpers/JSONFileParser.h"


// The application entry point.
int main(int argc, char* argv[]) 
{
	// A SET OF TODOs:
	// 1. Add parameterisation to the renderer so that parameters can be set for the renderer.
	// 2. Add abstraction for objects such as the window for multiplatform movement.

	std::cout << "T-Racer Rendering System. UWE dissertation project. \n" << 
		"Copyright Nathan Butt 2019 \n"
		<< "Starting Render." << std::endl;

	// TODO - Add a command line parameter to load a file. 
	JSONFileReader  file;
	file.setFilePath("resources/cornell 2.trs");

	//T_racer_Display_Window  window;
	T_racer_Display_TGA  tga;
	T_racer_Display_PFM  pfm;
//	T_racer_Camera  testCam;
	
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
	
	//light1->setPosition();

	tga.init(1920, 1080);
	tga.setDisplayName("Test");
	pfm.init(1920, 1080);
	pfm.setDisplayName("Test");

	T_racer_Renderer_PathTracer  trpt;

	T_racer_Scene testScene;
	testScene.loadScene(file);
//	testScene.setMainCamera(&testCam);

//	testScene.addLight(light1);

	trpt.setDisplay(file);
	trpt.setScene(&testScene);
	trpt.Render();
	trpt.postDisplayUpdate();

	return 0;
}