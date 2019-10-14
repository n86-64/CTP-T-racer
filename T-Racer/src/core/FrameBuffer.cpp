#include "FrameBuffer.h"

#include "core/Texture.h"

T_racer_FrameBuffer::T_racer_FrameBuffer(int width, int height)
{
	fbTex = new T_racer_Texture2D(width, height); 
}

void T_racer_FrameBuffer::write(T_racer_Math::Colour col, int x, int y)
{
	fbTex->copyPixelValues(x, y, col);
}
