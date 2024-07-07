#pragma once
#include <iostream>

struct Color
{
	float r, g, b, a;

	Color() : r{ 0 }, g{ 0 }, b{ 0 }, a{ 0 } {}
	Color(float r, float g, float b, float a = 1) : r{ r }, g{ g }, b{ b }, a{ a } {}

	//static uint8_t ToInt(float c) { return static_cast<uint8_t>(Clamp(c, 0.0f, 1.0f) * 255); }
};