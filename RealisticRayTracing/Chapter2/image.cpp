// Image.cc

#include "image.h"
#include <iostream>

Image::Image(int width, int height)
: nx(width)
, ny(height)
{
    // allocate memory for raster
    raster = new rgb* [nx];
    for(auto i=0; i<nx; ++i)
    { raster[i] = new rgb[ny]; }
}

Image::Image(int width, int height, rgb background)
: nx(width)
, ny(height)
{
    // allocate memory for raster
    raster = new rgb* [nx];
    for(auto i=0; i<nx; ++i)
    {
        raster[i] = new rgb[ny];
        // assign 'background& to each element
        for(auto j=0; j<ny; ++j)
        { raster[i][j] = background; }
    }
}

bool Image::set(int x, int y, const rgb& color)
{
    // check for out of bounds error
    if (0 > x || x > nx) return false;
    if (0 > y || y > ny) return false;

    raster[x][y] = color;
    return true;
}

void Image::gammaCorrect(float gamma)
{
    auto power = 1.0f / gamma;
    for(auto i=0; i<nx; ++i)
    {
        for(auto j=0; j<ny; ++j)
        {
            auto temp = raster[i][j];
            raster[i][j] = rgb(
                pow(temp.r(), power),
                pow(temp.g(), power),
                pow(temp.b(), power));
        }
    }
}

void Image::writePPM(std::ostream& out)
{
    // output header
    out << "P3\n";
    out << nx << ' ' << ny << '\n';
    out << "255\n";

    for(auto i=ny-1; i>=0; i--)
    {
        for(auto j=0; j<nx; ++j)
        {
            auto r = static_cast<unsigned int>(256 * raster[j][i].r());
            auto g = static_cast<unsigned int>(256 * raster[j][i].g());
            auto b = static_cast<unsigned int>(256 * raster[j][i].b());

            if (r > 255) r = 255;
            if (g > 255) g = 255;
            if (b > 255) b = 255;

            out << r << " " << g << " " << b << " ";
        }
    }
}

bool Image::writePPM(const char* path)
{
    // open stream to file.
    std::ofstream out;
    out.open(path);
    if (!out.is_open())
    {
        std::cerr << "ERROR -- Couldn't open file \'" << path << "\'.\n";
        return false;
    }

    writePPM(out);
    out.close();
    return true;
}

bool Image::readPPM(const char* path)
{
    // open stream to file
    std::ifstream in;
    in.open(path);
    if (!in.is_open())
    {
        std::cerr << "ERROR -- Couldn't open file \'" << path << "\'.\n";
        return false;
    }

    char ch, type;
    char r, g, b;
    int  cols, rows, count;

    // read in header info
    in.get(ch);
    in.get(type);
    in >> cols >> rows >> count;

    nx = cols;
    ny = rows;

    // allocate raster
    raster = new rgb* [nx];
    for(auto i=0; i<nx; ++i)
    { raster[i] = new rgb[ny]; }

    // clean up newlines
    in.get(ch);

    // store PPM pixel values in raster
    for(auto i=ny-1; i>=0; i--)
    {
        for(auto j=0; j<nx; ++j)
        {
            in.get(r);
            in.get(g);
            in.get(b);

            raster[j][i] = rgb(
                float(unsigned char(r) / 255.0),
                float(unsigned char(g) / 255.0),
                float(unsigned char(b) / 255.0));
        }
    }

    return true;
}
