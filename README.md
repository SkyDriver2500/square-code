# SCode
SCode convert text files to bitmap squares and with lossless image compression techniques hope to turn text files into much smaller image file. Compressing the text file gradually into the smallest file without loss of data.

## Examples
A text about programming taken from [*Wikipedia*](https://en.wikipedia.org/wiki/Computer_programming):

![Programming.bmp](examples/programming.bmp)

## Download
You can download the released (or pre-released) version of this software [here](https://github.com/SkyDriver2500/square-code/releases/download/v0.1/scode-0.1.tar.gz).

## Preparing the development version
This project uses autotools to generate the building files.
```
~$ aclocal
~$ autoconf
~$ automake --add-missing
```

## Installing the dist version
To install the dist version run:
```
~$ ./configure
~$ make
~$ make install
```
**Note:** Make sure you have permissions to run `make install`.

## Running SCode
```
Usage:
  scode sourcefile destination.bmp
```
**Note:** Files are saved under the users home directory.

# About bitmaps
For this project these tables are a useful reference if you are planning on editing the bitmap generation. Even if you are here just to try and learn more about bitmaps and understand what's behind them this section might be helpful to you.

## File Header

| Position | Name | Size | Standard Value | Description |
| ---:| --- | --- |:---:| --- |
| 1 | bfType | 2 Bytes | 0x4D42 | Most of the time is set to 'BM' (0x4D42 in hex) to declare it is a .bmp bitmap file. |
| 3 | bfSize | 4 Bytes | ---- | Size of the file in Bytes |
| 7 | bfReserved1 | 2 Bytes | 0 | Reserved. |
| 9 | bfReserved2 | 2 Bytes | 0 | Reserved. |
| 11 | bfOffBits | 4 Bytes | ---- | Offset from the beginnning of the file to the bitmap data. bfSize minus the size of the data. (**Palettes are considered headers, not bitmap data**).  |

## Information Header

| Position | Name | Size | Standard Value | Description |
| ---:| --- | --- |:---:| --- |
| 15 | biSize | 4 Bytes | 40 | Size of the Information Header in bytes. |
| 19 | biWidth | 4 Bytes | ---- | Width of the image in pixels. |
| 23 | biHeight | 4 Bytes | ---- | Height of the image in pixels. |
| 27 | biPlanes | 2 Bytes | ---- | Number of planes of the target device. |
| 29 | biBitCount | 2 Bytes | ---- | Number of bits per pixel. |
| 31 | biCompression | 4 Bytes | 0 | Type of compression, set to 0 for no compression. |
| 35 | biSizeImage | 4 Bytes | 0 | Size of the image in bytes, can be set to 0. |
| 39 | biXPelsPerMeter | 4 Bytes | 0 | Number of horizontal pixels per meter on the target device. Usually set to 0. |
| 43 | biYPelsPerMeter | 4 Bytes | 0 | Number of vertical pixels per meter on the target device. Usually set to 0. |
| 47 | biClrUsed | 4 Bytes | 0 | Number of colors used in the bitmap. Set to 0 for it to be calculated using biBitCount. |
| 51 | biClrImportant | 4 Bytes | 0 | Number of colors that are "important" for the bitmap. Set to 0 for all colors to be "important". |

## RGB Data
For bitmaps with more than 8 Bits per pixel (16, 24...). Don't need a color palette as each byte will be assigned to red, green and blue.

| Position | Name | Size | Range | Description |
| ---:| --- | --- |:---:| --- |
| Offset + 1 | b | 1 Byte | 0x00 - 0xff | Blue |
| Offset + 2 | g | 1 Byte | 0x00 - 0xff | Green |
| Offset + 3 | r | 1 Byte | 0x00 - 0xff | Red |

## 8 Bit Bitmaps
1 Bit, 4 Bit and 8 Bit bitmaps need to have a palette of colors between the *Information Header* and the *Data*. These palettes are the combinations of red, green and blue that will form the color you want in that *index*.

**Note:** For 8 Bit there are 256 indexes (0-255), for 4 Bit there are 16 indexes (0-15) and for 1 Bit there are 2 indexes (0-1).

Imagine I want a 8 Bit grayscale bitmap. I would use the following structures:

### Palette

Palletes are stored between Information Header and the Bitmap data.

| Name | Size | Range | Description |
| --- | --- |:---:| --- |
| r | 1 Byte | 0x00 - 0xff | Red |
| g | 1 Byte | 0x00 - 0xff | Green |
| b | 1 Byte | 0x00 - 0xff | Blue |
| reserved | 1 Byte | 0x00 | Reserved |

**Note:** In a palette, r, g and b are stored in the correct order unlike the RGB Data (RGB Data is used to draw the bitmap, and a bitmap is drawn inverted in position)

Then I would loop through each index and assign it the same value to r, g and b and increment that value by 1. At the end I would have 256 shades of gray stored in the palette.

### Bitmap Data
Like RGB Data this contains what will be drawn to the bitmap. "Unlike" RGB Data this will contain the *index* pointing to a color in the palette.

| Position | Name | Size | Index | Description |
| ---:| --- | --- |:---:| --- |
| Offset + 1 | gray | 1 Byte | 0x00 - 0xff | Gray Scale |

You will get a much smaller grayscale file than you would by using RGB Data and just assingning the same value to r, g and b because you would be writing 3 bytes for each pixel instead of 1.

# License
Check LICENSE file for more information.
