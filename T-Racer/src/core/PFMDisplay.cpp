#include "PFMDisplay.h"

void T_racer_Display_PFM::init(float resolutionX, float resolutionY)
{
	resX = resolutionX;
	resY = resolutionY;
}

void T_racer_Display_PFM::update()
{
	return;
}

void T_racer_Display_PFM::writeToDisplay(Image& imageBuffer)
{
	FILE *file;
	file = fopen(displayName.c_str(), "wb");

	if (file != NULL && imageBuffer.colour_values)
	{
		// Header (showing colour image)
		fputc('P', file);
		fputc('F', file);
		fputc(0x0a, file);

		// Width and Height
		fprintf(file, "%d %d", imageBuffer.width, imageBuffer.height);
		fputc(0x0a, file);

		// Flag (indicating endian and scale)
		fprintf(file, "%f", -1.0f);
		fputc(0x0a, file);

		for (int y = 0; y < imageBuffer.height; y++)
		{
			for (int x = 0; x < imageBuffer.width; x++)
			{
				float val[3];
				val[0] = imageBuffer(x, y).colour.X;
				val[1] = imageBuffer(x, y).colour.Y;
				val[2] = imageBuffer(x, y).colour.Z;
				fwrite(&val, sizeof(float), 3, file);
			}
		}

		fclose(file);
	}
	else
	{
		perror(displayName.c_str());
	}
}
