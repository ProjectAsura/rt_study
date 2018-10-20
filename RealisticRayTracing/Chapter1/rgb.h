// rgb.h
#pragma once

#include <iostream>

class rgb
{
public:
    float _r = 0.0f;
    float _g = 0.0f;
    float _b = 0.0f;

    rgb() 
    { /* DO_NOTHING */ }

    rgb(float r, float g, float b)
    : _r(r), _g(g), _b(b)
    { /* DO_NOTHING */ }

    rgb(const rgb& value)
    { *this = value; }

    void setRed  (float r) { _r = r; }
    void setGreen(float g) { _g = g; }
    void setBlue (float b) { _b = b; }

    // these operators perform no clamping
    rgb& operator =  (const rgb& value) { _r  = value._r; _g  = value._g; _b  = value._b; return *this; }
    rgb& operator += (const rgb& value) { _r += value._r; _g += value._g; _b += value._b; return *this; }
    rgb& operator *= (const rgb& value) { _r *= value._r; _g *= value._g; _b *= value._b; return *this; }
    rgb& operator /= (const rgb& value) { _r /= value._r; _g /= value._g; _b /= value._b; return *this; }
    rgb& operator *= (float value) { _r *= value; _g *= value; _b *= value; return *this; }
    rgb& operator /= (float value) { _r /= value; _g /= value; _b /= value; return *this; }

    rgb operator + () const { return *this; }
    rgb operator - () const { return rgb(-_r, -_g, -_b); }

    float r() const { return _r; }
    float g() const { return _g; }
    float b() const { return _b; }

    void clamp()
    {
        _r = (_r > 1.0f) ? 1.0f : ((_r < 0.0f) ? 0.0f : _r); 
        _g = (_g > 1.0f) ? 1.0f : ((_g < 0.0f) ? 0.0f : _g);
        _b = (_b > 1.0f) ? 1.0f : ((_b < 0.0f) ? 0.0f : _b);
    }

    friend std::ostream& operator << (std::ostream& out, const rgb& value);
    friend rgb operator * (const rgb& lhs, float rhs);
    friend rgb operator * (float lhs, const rgb& rhs);
    friend rgb operator / (const rgb& lhs, float rhs);
    friend rgb operator * (const rgb& lhs, const rgb& rhs);
    friend rgb operator / (const rgb& lhs, const rgb& rhs);
    friend rgb operator + (const rgb& lhs, const rgb& rhs);
};

inline std::ostream& operator << (std::ostream& out, const rgb& value)
{
    out << value._r << ' '
        << value._g << ' '
        << value._b << ' ';
    return out;
}

inline rgb operator * (const rgb& lhs, float rhs)
{ return rgb(lhs._r * rhs, lhs._g * rhs, lhs._b * rhs); }

inline rgb operator * (float lhs, const rgb& rhs)
{ return rgb(lhs * rhs._r, lhs * rhs._g, lhs * rhs._b); }

inline rgb operator / (const rgb& lhs, float rhs)
{ return rgb(lhs._r / rhs, lhs._g / rhs, lhs._b / rhs); }

inline rgb operator * (const rgb& lhs, const rgb& rhs)
{ return rgb(lhs._r * rhs._r, lhs._g * rhs._g, lhs._b * rhs._b); }

inline rgb operator / (const rgb& lhs, const rgb& rhs)
{ return rgb(lhs._r / rhs._r, lhs._g / rhs._g, lhs._b / rhs._b); }

inline rgb operator + (const rgb& lhs, const rgb& rhs)
{ return rgb(lhs._r + rhs._r, lhs._g + rhs._g, lhs._b + rhs._b); }

