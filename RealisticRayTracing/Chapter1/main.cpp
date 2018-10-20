
#include "image.h"
#include "vector3.h"
#include "onb.h"
#include "rgb.h"
#include "rng.h"
#include "dynarray.h"
#include <cassert>

int main(int argc, char** argv)
{
    {
        DynArray<int> test;
        test.append(1);
        test.append(2);
        test.append(3);

        assert(test.length() == 3);

        for(auto i=0; i<test.length(); ++i)
        {
            printf_s("%d\n", test[i]);
        }
        assert(test[0] == 1);
        assert(test[1] == 2);
        assert(test[2] == 3);
        //assert(test.arraySize == 4);

        test.append(4);
        test.append(5);

        assert(test[3] == 4);
        assert(test[4] == 5);
        //assert(test.arraySize == 8);

        test.truncate();
        assert(test[0] == 1);
        assert(test[1] == 2);
        assert(test[2] == 3);
        assert(test[3] == 4);
        assert(test[4] == 5);
        //assert(test.arraySize == 5);
        //assert(test.nData == 5);
    }

    {
        Image image(512, 256, rgb(1.0f, 0.0f, 0.0f));
        image.writePPM("test.ppm");
    }

    return 0;
}