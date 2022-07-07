#pragma once
#include "Base.h"

class Vector2D : public CBase {
public:
	float x;
	float y;

	Vector2D() : x(0.f), y(0.f) {}
	Vector2D(float InX, float InY) : x(InX), y(InY) {}
	Vector2D(int InX, int InY) : x((float)InX), y((float)InY) {}

	Vector2D operator* (float InValue) const { return Vector2D(x * InValue, y * InValue); }

	// º¤ÅÍÀÇ ³»Àû ( ½ºÄ®¶ó °ö )
	float operator* (const Vector2D& InValue) const { return (x * InValue.x) + (y * InValue.y); }

	Vector2D operator- (const Vector2D& InValue) const { return Vector2D(x - InValue.x, y - InValue.y); }

	void operator+= (const Vector2D& InValue) {
		x = x + InValue.x;
		y = y + InValue.y;
	}
};