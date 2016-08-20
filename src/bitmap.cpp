#include <fstream>
#include <cstring>
#include <cstdlib>
#include <iostream>

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

struct BITMAPRGBDATA {
	/* Inverted RGB because bitmaps are stored upside down. */
	unsigned char b;
	unsigned char g;
	unsigned char r;
}__attribute__((packed));

bool Bitmap::createbmp(char* path, char* buffer) {
	int width = 128;
	int height = 128;
	unsigned int size = width * height * 3;
	BITMAPFILEHEADER bmfh;
	BITMAPINFOHEADER bmih;
	FILE* bitmap;

	bmfh.bfType = 0x4D42;
	bmfh.bfSize = size + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
	bmfh.bfReserved1 = 0x00;
	bmfh.bfReserved2 = 0x00;
	bmfh.bfOffBits = bmfh.bfSize - size;

	bmih.biSize = 0x28; // 40 bytes
	bmih.biWidth = width;
	bmih.biHeight = height;
	bmih.biPlanes = 0x01;
	bmih.biBitCount = 0x18;
	bmih.biCompression = 0x00;
	bmih.biSizeImage = 0x00;
	bmih.biXPelsPerMeter = 0x00;
	bmih.biYPelsPerMeter = 0x00;
	bmih.biClrUsed = 0x00;
	bmih.biClrImportant = 0x00;

	bitmap = fopen(path, "wb");

	BITMAPRGBDATA rgbbuffer[width][height];

	fwrite(&bmfh, 1, sizeof(BITMAPFILEHEADER), bitmap);
	fwrite(&bmih, 1, sizeof(BITMAPINFOHEADER), bitmap);

	memset(rgbbuffer, 0, sizeof(rgbbuffer));

	int cursor = 0;
	for(int i=0; i<width; i++) {
		for(int j=0; j<height; j++) {
			unsigned int c = buffer[cursor];
			rgbbuffer[i][j].r = c;
			rgbbuffer[i][j].g = c;
			rgbbuffer[i][j].b = c;

			cursor++;
		}
	}

	fwrite(&rgbbuffer, 1, size, bitmap);
	fclose(bitmap);
	return true;
}
