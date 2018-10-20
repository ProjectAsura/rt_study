﻿// Image.h
#pragma once

#include <cmath>
#include <string>
#include <fstream>
#include "rgb.h"


class Image
{
public:
    Image() = default;

    // initializes raster to default rgb color
    Image(int width, int heihgt);

    // initializes raster to 'background' 
    Image(int width, int height, rgb background);

    // returns false if x or y are out of bounds, else true
    bool set(int x, int y, const rgb& color);

    void gammaCorrect(float gamma);

    // outputs PPM image to 'out'
    void writePPM(std::ostream& out);

    bool writePPM(const char* path);

    bool readPPM(const char* path);

private:
    rgb**   raster;
    int     nx = 0;
    int     ny = 0;
};
