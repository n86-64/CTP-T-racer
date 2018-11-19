#include "TGADisplay.h"

void T_racer_Display_TGA::init(float resolutionX, float resolutionY)
{
	resX = resolutionX;
	resY = resolutionY;
	return;
}

void T_racer_Display_TGA::writeToDisplay(Image* imageBuffer)
{
	FILE *pFile;               // The file pointer.
	unsigned char uselessChar; // used for useless char.
	short int uselessInt;      // used for useless int.
	unsigned char imageType;   // Type of image we are saving.
	unsigned char bits;    // Bit depth.
	long Size;                 // Size of the picture.
	int colorMode;

	// Open file for output.
	pFile = fopen(displayName.c_str(), "wb");

	// Check if the file opened or not.
	if (pFile == NULL && !imageBuffer->colour_values)
	{
		perror(displayName.c_str());
		return;
	}

	// Set the image type, the color mode, and the bit depth.
	imageType = 2; colorMode = 3; bits = 24;

	// Set these two to 0.
	uselessChar = 0; uselessInt = 0;

	// Write useless data.
	fwrite(&uselessChar, sizeof(unsigned char), 1, pFile);
	fwrite(&uselessChar, sizeof(unsigned char), 1, pFile);

	// Now image type.
	fwrite(&imageType, sizeof(unsigned char), 1, pFile);

	// Write useless data.
	fwrite(&uselessInt, sizeof(short int), 1, pFile);
	fwrite(&uselessInt, sizeof(short int), 1, pFile);
	fwrite(&uselessChar, sizeof(unsigned char), 1, pFile);
	fwrite(&uselessInt, sizeof(short int), 1, pFile);
	fwrite(&uselessInt, sizeof(short int), 1, pFile);

	// Write the size that you want.
	fwrite(&(imageBuffer->width), sizeof(short int), 1, pFile);
	fwrite(&(imageBuffer->height), sizeof(short int), 1, pFile);
	fwrite(&bits, sizeof(unsigned char), 1, pFile);

	// Write useless data.
	fwrite(&uselessChar, sizeof(unsigned char), 1, pFile);

	// Get image size.
	Size = imageBuffer->getSize() * colorMode;

	for (int y = 0; y < imageBuffer->height; y++)
	{
		for (int x = 0; x < imageBuffer->width; x++)
		{
			int i = (x + imageBuffer->width * (imageBuffer->height - y - 1)) * 3;

			uint8_t c[3];
			c[2] = (*imageBuffer)(x, y).getTonemappedColour(1.0f).Z;
			c[1] = (*imageBuffer)(x, y).getTonemappedColour(1.0f).Y;
			c[0] = (*imageBuffer)(x, y).getTonemappedColour(1.0f).X;

			fwrite(&c[0], sizeof(uint8_t), 3, pFile);
		}
	}

	fprintf(stderr, "Saved TGA: %dx%d\n", imageBuffer->width, imageBuffer->height);

	// close the file.
	fclose(pFile);
}

void T_racer_Display_TGA::setDisplayName(std::string name)
{
	displayName = name;
}
