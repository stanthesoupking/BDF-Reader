# BDF Reader
Reads Adobe's Glyph Bitmap Distribution Format (BDF)

## Usage
This project is currently in its very early development stage so no usage patterns have been created yet. See the `src/main.cpp` file for an example of how this library may be used.

## Compiling
The easiest way to include this library in your project is to include it in your `CMakeLists.txt`.

## Limitations
Due to the internal data structure used for storing bitmap data, only fonts with a width of 8 or less pixels are supported. This may be expanded upon in the future depending on demand.