/** @file Framebuffer.h
*  @brief The destination of rendering data for an integrator.
*
*  This class is used by integrators to render the results on screen.
*  The framebuffer is used by displays to display the frame to the user.
*
*  @author Nathan Butt (n86-64)
*  @bug No known bugs.
*/

#pragma once

#include <iostream>

#include "helpers/Math_Colour.h"

class T_racer_Texture2D;

// TODO - Add capability to save out buffer to file.

class T_racer_FrameBuffer {
public:
	T_racer_FrameBuffer(float width, float height);
	void write(T_racer_Math::Colour col, int x, int y);

	// Save out the framebuffer to disk. 
	// Use determined in render settings. 
	void writeToDiskTGA(std::string name);
	void writeToDiskPFM(std::string name);

private:
	T_racer_Texture2D* fbTex = nullptr;
	float w = 0, h = 0;
	int size = 0;
};