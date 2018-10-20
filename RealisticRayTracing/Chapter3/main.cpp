// main.cc

#include <vector>
#include <iostream>
#include "vector3.h"
#include "rgb.h"
#include "image.h"
#include "shape.h"
#include "triangle.h"
#include "sphere.h"


int main(int argc, char** argv)
{
    HitRecord   rec = {};
    bool        is_hit = false;
    float       tmax;             // max valid t parameter
    Vector3     dir(0, 0, -1);    // direction of viewing rays

    // geometry
    std::vector<Shape*> shapes;
    shapes.push_back(new Sphere(Vector3(250.0f, 250.0f, -1000.0f), 150, rgb(0.2f, 0.2f, 0.8f)));
    shapes.push_back(new Triangle(
                        Vector3(300.0f, 600.0f,  -800.0f),
                        Vector3(  0.0f, 100.0f, -1000.0f),
                        Vector3(450.0f,  20.0f, -1000.0f),
                        rgb(0.8f, 0.2f, 0.2f)));

    Image im(500, 500);

    // loop over pixels
    for(auto i=0; i<500; ++i)
    {
        for(auto j=0; j<500; ++j)
        {
            tmax = 100000.0f;
            is_hit = false;

            Ray r(Vector3(i, j, 0), dir);

            // loop over list of shapes
            for(auto k=0u; k<shapes.size(); ++k)
            {
                if (shapes[k]->hit(r, 0.00001f, tmax, 0.0f, rec))
                {
                    tmax = rec.t;
                    is_hit = true;
                }
            }

            if (is_hit)
            {
                im.set(i, j, rec.color);
            }
            else
            {
                im.set(i, j, rgb(0.2f, 0.2f, 0.2f));
            }
        }
    }

    im.writePPM("result.ppm");

    for(auto i=0u; i<shapes.size(); ++i)
    {
        auto ptr = shapes[i];
        delete ptr;
        shapes[i] = nullptr;
    }
    shapes.clear();
    shapes.shrink_to_fit();

    return 0;
}