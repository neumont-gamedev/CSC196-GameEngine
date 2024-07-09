#pragma once
#define NOMINMAX
#include "core.h"
#include <iostream>

struct Color
{
	float r, g, b;

	Color() : r{ 0 }, g{ 0 }, b{ 0 } {}
	Color(float r, float g, float b) : r{ r }, g{ g }, b{ b } {}
	Color(DWORD rgb) // DWORD( x | b | g | r )
	{
		r = (rgb & 0xff) / 255.0f;			// 0 - 255 -> 0 - 1
		g = ((rgb >> 8) & 0xff) / 255.0f;	// 0 - 255 -> 0 - 1
		b = ((rgb >> 16) & 0xff) / 255.0f;	// 0 - 255 -> 0 - 1
	}

	float  operator [] (size_t index) const { return (&r)[index]; }
	float& operator [] (size_t index) { return (&r)[index]; }

	void Set(float r, float g, float b) { this->r = r; this->g = g; this->b = b; }

	Color operator + (const Color& color) const { return { r + color.r, g + color.g, b + color.b }; }
	Color operator - (const Color& color) const { return { r - color.r, g - color.g, b - color.b }; }
	Color operator * (const Color& color) const { return { r * color.r, g * color.g, b * color.b }; }
	Color operator / (const Color& color) const { return { r / color.r, g / color.g, b / color.b }; }

	Color operator + (float s) const { return { r + s, g + s, b + s }; }
	Color operator - (float s) const { return { r - s, g - s, b - s }; }
	Color operator * (float s) const { return { r * s, g * s, b * s }; }
	Color operator / (float s) const { return { r / s, g / s, b / s }; }

	Color& operator += (const Color& color) { r += color.r; g += color.g; b += color.b; return *this; }
	Color& operator -= (const Color& color) { r -= color.r; g -= color.g; b -= color.b; return *this; }
	Color& operator *= (const Color& color) { r *= color.r; g *= color.g; b *= color.b; return *this; }
	Color& operator /= (const Color& color) { r /= color.r; g /= color.g; b /= color.b; return *this; }

	Color& operator += (float s) { r += s; g += s; b += s; return *this; }
	Color& operator -= (float s) { r -= s; g -= s; b -= s; return *this; }
	Color& operator *= (float s) { r *= s; g *= s; b *= s; return *this; }
	Color& operator /= (float s) { r /= s; g /= s; b /= s; return *this; }

	bool operator == (const Color& color) { return r == color.r && g == color.g && b == color.b; }
	bool operator != (const Color& color) { return r != color.r || g != color.g || b != color.b; }

	operator DWORD() const { return ToRGB(); }

	DWORD ToRGB() const
	{
		BYTE red = static_cast<BYTE>(r * 255);		// 0 - 1 -> 0 - 255
		BYTE green = static_cast<BYTE>(g * 255);	// 0 - 1 -> 0 - 255
		BYTE blue = static_cast<BYTE>(b * 255);		// 0 - 1 -> 0 - 255

		return (red | green << 8 | blue << 16);
	}

	static Color HSVToRGB(float h, float s, float v);
	static void  RGBToHSV(const Color& color, float& h, float& s, float& v);

	friend std::istream& operator >> (std::istream& stream, Color& color);

	static const Color white;
	static const Color red;
	static const Color green;
	static const Color blue;
	static const Color purple;
	static const Color cyan;
	static const Color orange;
	static const Color yellow;
	static const Color black;
};
