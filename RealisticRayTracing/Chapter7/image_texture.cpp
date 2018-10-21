// ImageTexture.cc

#include "image_texture.h"
#include "image.h"


ImageTexture::ImageTexture(const char* path)
{
    image = new Image();
    image->readPPM(path);
}

ImageTexture::~ImageTexture()
{
    delete image;
    image = nullptr;
}

rgb ImageTexture::value(const Vector2& uv, const Vector3& p) const 
{
    auto u = uv.x() - int(uv.x());
    auto v = uv.y() - int(uv.y());

    u *= (image->width () - 3);
    v *= (image->height() - 3);

    auto iu = int(u);
    auto iv = int(v);

    auto tu = u - iu;
    auto tv = v - iv;

    rgb c = image->getPixel(iu,     iv)     * (1 - u)  * (1 - tv)
          + image->getPixel(iu + 1, iv)     * tu       * (1 - tv)
          + image->getPixel(iu,     iv + 1) * (1 - tu) * tv
          + image->getPixel(iu + 1, iv + 1) * tu       * tv;

    return c;
}