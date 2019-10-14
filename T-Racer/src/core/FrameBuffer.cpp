#include "FrameBuffer.h"

#include "core/Texture.h"

#ifdef _WIN32
#pragma warning(disable : 4996)
#endif

T_racer_FrameBuffer::T_racer_FrameBuffer(float width, float height)
	:w(width),
	h(height)
{
	fbTex = new T_racer_Texture2D(width, height); 
	size = w * h * sizeof(float) * 3;
}

void T_racer_FrameBuffer::write(T_racer_Math::Colour col, int x, int y)
{
	fbTex->copyPixelValues(x, y, col);
}

void T_racer_FrameBuffer::writeToDiskTGA(std::string name)
{
	FILE* pFile;               // The file pointer.
	unsigned char uselessChar; // used for useless char.
	short int uselessInt;      // used for useless int.
	unsigned char imageType;   // Type of image we are saving.
	unsigned char bits;    // Bit depth.
	long Size;                 // Size of the picture.
	int colorMode;
	int width = w;
	int height = h;

	// Open file for output.
	pFile = fopen(name.c_str(), "wb");

	// Check if the file opened or not.
	if (pFile == NULL && !fbTex)
	{
		perror(name.c_str());
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
	fwrite(&(width), sizeof(short int), 1, pFile);
	fwrite(&(height), sizeof(short int), 1, pFile);
	fwrite(&bits, sizeof(unsigned char), 1, pFile);

	// Write useless data.
	fwrite(&uselessChar, sizeof(unsigned char), 1, pFile);

	// Get image size.
	Size = width * height * colorMode;

	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			int i = (x + width * (y - 1)) * 3;

			uint8_t c[3];
			c[2] = fbTex->getPixelValue(x, height - y - 1).getTonemappedColour(1.0f).X;
			c[1] = fbTex->getPixelValue(x, height - y - 1).getTonemappedColour(1.0f).Y;
			c[0] = fbTex->getPixelValue(x, height - y - 1).getTonemappedColour(1.0f).Z;

			fwrite(&c[0], sizeof(uint8_t), 3, pFile);
		}
	}

	fprintf(stderr, "Saved TGA: %dx%d\n", width, height);

	// close the file.
	fclose(pFile);
}

void T_racer_FrameBuffer::writeToDiskPFM(std::string name)
{
	FILE* file;
	file = fopen(name.c_str(), "wb");

	if (file != NULL && fbTex)
	{
		// Header (showing colour image)
		fputc('P', file);
		fputc('F', file);
		fputc(0x0a, file);

		// Width and Height
		fprintf(file, "%d %d", w, h);
		fputc(0x0a, file);

		// Flag (indicating endian and scale)
		fprintf(file, "%f", -1.0f);
		fputc(0x0a, file);

		for (int y = 0; y < h; y++)
		{
			for (int x = 0; x < w; x++)
			{
				float val[3];
				val[0] = fbTex->getPixelValue(x, h - y).colour.X;
				val[1] = fbTex->getPixelValue(x, h - y).colour.Y;
				val[2] = fbTex->getPixelValue(x, h - y).colour.Z;
				fwrite(&val, sizeof(float), 3, file);
			}
		}


		fclose(file);
		printf("Saved PFM.");
	}
	else
	{
		perror(std::string("ERROR File " + name + " failed to save.").c_str());
	}
}
