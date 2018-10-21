// ImageTexture.h
#pragma once

#include "texture.h"

class Image;

class ImageTexture : public Texture
{
public:
    ImageTexture(const char* path);
    ~ImageTexture();
    rgb value(const Vector2& uv, const Vector3& p) const override;

private:
    Image* image;
};
