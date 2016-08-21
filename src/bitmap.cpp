#include <fstream>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <math.h>

#include "bitmap.hpp"

using namespace std;

struct BITMAPFILEHEADER {
	unsigned short bfType;	// 2 bytes
	unsigned int bfSize;	// 4 bytes
	unsigned short bfReserved1;	// 2 bytes
	unsigned short bfReserved2;	// 2 bytes
	unsigned int bfOffBits;	// 4 bytes
}__attribute__((packed));	// Search how to do this without packed.

struct BITMAPINFOHEADER {
	unsigned int biSize;	// 4 bytes
	int biWidth;	// 4 bytes
	int biHeight;	// 4 bytes
	unsigned short biPlanes;	// 2 bytes
	unsigned short biBitCount;	// 2 bytes
	unsigned int biCompression;	// 4 bytes
	unsigned int biSizeImage;	// 4 bytes
	int biXPelsPerMeter;	// 4 bytes
	int biYPelsPerMeter;	// 4 bytes
	unsigned int biClrUsed;	// 4 bytes
	unsigned int biClrImportant;	// 4 bytes
}__attribute__((packed));

struct BITMAPDATA {
	unsigned char gray;
}__attribute__((packed));

struct PALETTE {
	unsigned char r;
	unsigned char g;
	unsigned char b;
	unsigned char reserved;
}__attribute__((packed));

bool Bitmap::createbmp(char* path, char* buffer) {
	int dimension = ceil(sqrt(strlen(buffer)));
	unsigned int size = pow(dimension, 2);
	BITMAPFILEHEADER bmfh;
	BITMAPINFOHEADER bmih;
	PALETTE palette[256];	// In this case a grayscale palette.
	FILE* bitmap;

	/* Fill the palette with grayscale */
	for(int i=0; i<256; i++) {
		palette[i].r = i;
		palette[i].g = i;
		palette[i].b = i;
		palette[i].reserved = 0x00;
	}

	bmfh.bfType = 0x4D42;
	bmfh.bfSize = size + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + sizeof(palette);
	bmfh.bfReserved1 = 0x00;
	bmfh.bfReserved2 = 0x00;
	bmfh.bfOffBits = bmfh.bfSize - size;

	bmih.biSize = 0x28; // 40 bytes
	bmih.biWidth = dimension;
	bmih.biHeight = dimension;
	bmih.biPlanes = 0x01;
	bmih.biBitCount = 0x08;
	bmih.biCompression = 0x00;
	bmih.biSizeImage = 0x00;
	bmih.biXPelsPerMeter = 0x00;
	bmih.biYPelsPerMeter = 0x00;
	bmih.biClrUsed = 256;
	bmih.biClrImportant = 0x00;

	bitmap = fopen(path, "wb");

	BITMAPDATA graybuffer[dimension][dimension];

	fwrite(&bmfh, 1, sizeof(BITMAPFILEHEADER), bitmap);
	fwrite(&bmih, 1, sizeof(BITMAPINFOHEADER), bitmap);
	for(int i=0; i<256; i++) {
		fwrite(&palette[i], 1, sizeof(PALETTE), bitmap);
	}
	memset(graybuffer, 0, sizeof(graybuffer));

	int cursor = 0;
	for(int i=0; i<dimension; i++) {
		for(int j=0; j<dimension; j++) {
			unsigned int c = buffer[cursor];
			graybuffer[i][j].gray = c;

			cursor++;
		}
	}

	fwrite(&graybuffer, 1, size, bitmap);
	fclose(bitmap);
	return true;
}
