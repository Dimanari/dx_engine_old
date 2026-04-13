#include "Object.h"

Object::Object()
{
	x = 40; y = 40; size = 20; vx = vy = 0;
}

void Object::Move(Direction dir, float value)
{
	switch (dir)
	{
	case UP:
		y -= value;
		if (y < size)
			y = size;
		break;
	case DOWN:
		y += value;
		if (y > 600-size)
			y = 600-size;
		break;
	case LEFT:
		x -= value;
		if (x < size)
			x = size;
		break;
	case RIGHT:
		x += value;
		if (x > 800 - size)
			x = 800 - size;
		break;
	}
}

void Object::SetVelocity(Direction dir, float value)
{
	static constexpr float maxSpeed = 0.05;
	if (value == 0)
	{
		switch (dir)
		{
		case UP:
		case DOWN:
			vy = 0;
			break;
		case LEFT:
		case RIGHT:
			vx = 0;
			break;
		}
	}
	switch (dir)
	{
	case UP:
		vy -= value;
		if (vy*vy > maxSpeed*maxSpeed)
		{
			vy = -maxSpeed;
		}
		break;
	case DOWN:
		vy += value;
		if (vy*vy > maxSpeed*maxSpeed)
		{
			vy = maxSpeed;
		}
		break;
	case LEFT:
		vx -= value;
		if (vx*vx > maxSpeed*maxSpeed)
		{
			vx = -maxSpeed;
		}
		break;
	case RIGHT:
		vx += value;
		if (vx*vx > maxSpeed*maxSpeed)
		{
			vx = maxSpeed;
		}
		break;
	}
}

void Object::Update(long deltaTime)
{
	if (deltaTime == 0)
		return;
	if(vx!=0)
		this->Move(RIGHT, deltaTime*vx);
	if (vy != 0)
		this->Move(DOWN, vy*deltaTime);
}

void Object::Draw(Graphics * gfx)
{
	gfx->DrawRect(x - size, y - size, size * 2, size * 2, 0.7, 0.7, 0);
}
