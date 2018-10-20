
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

    {
        Vector3 a(0.0f, 0.0f, 0.0f);
        Vector3 b(1.0f, 0.0f, 0.0f);
        Vector3 c(0.0f, 1.0f, 0.0f);

        auto r1 = a + b;
        auto r2 = a - b;
        auto r3 = b * 3.0f;

        std::cout << r1 << std::endl;
        std::cout << r2 << std::endl;
        std::cout << r3 << std::endl;

        r1 = b + c;
        r2 = b - c;
        r3 = c / 0.5f;

        std::cout << r1 << std::endl;
        std::cout << r2 << std::endl;
        std::cout << r3 << std::endl;

        printf_s("length a = %f\n", a.length());
        printf_s("length b = %f\n", b.length());
        printf_s("length c = %f\n", c.length());

    }

    return 0;
}