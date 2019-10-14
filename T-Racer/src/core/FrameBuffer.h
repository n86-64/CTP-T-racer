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

#include "helpers/Math_Colour.h"

class T_racer_Texture2D;

// TODO - Add capability to save out buffer to file.

class T_racer_FrameBuffer {
public:
	T_racer_FrameBuffer(int width, int height);
	void write(T_racer_Math::Colour col, int x, int y);
	

	// Add any conversion code needed here. 
	// Used for writing out data for use in a perticular display. 

private:
	T_racer_Texture2D* fbTex = nullptr;
};