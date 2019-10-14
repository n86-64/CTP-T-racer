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

	JSONFileReader  file;

	if (argc > 1) 
	{
		file.setFilePath(argv[1]);
	}
	else 
	{
		std::cout << "ERROR - File path not specified. Exiting \n";
		getchar();
		return 1;
	}


	//T_racer_Display_Window  window;
	T_racer_Display_TGA  tga;
	T_racer_Display_PFM  pfm;

	tga.init(1920, 1080);
	tga.setDisplayName("Test");
	pfm.init(1920, 1080);
	pfm.setDisplayName("Test");

	T_racer_Renderer_PathTracer  trpt;

	T_racer_FrameBuffer* fb = new T_racer_FrameBuffer(512, 512); // Test object
	
	T_racer_Scene testScene;
	testScene.loadScene(file);
	
	trpt.setDisplay(file);
	trpt.setFramebuffer(fb);
	trpt.setScene(&testScene);
	trpt.Render();
	trpt.postDisplayUpdate();

	fb->writeToDiskTGA("test.tga");

	return 0;
}