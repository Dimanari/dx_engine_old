#pragma once
#include "Graphics.h"

class Object
{
	float x,vx, y,vy ,size;
public:
	enum Direction
	{
		UP,DOWN,LEFT,RIGHT
	};
	Object();
	void Move(Direction dir, float value);
	void SetVelocity(Direction dir, float value);
	void Update(long deltaTime);
	void Draw(Graphics *gfx);
};