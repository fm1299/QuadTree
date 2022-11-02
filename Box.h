#ifndef BOX_H
#define BOX_H
#include "Point.h"
class Box
{
private:
	float x;
	float y;
	float width;
	float height;
	friend class Node;
public:
	Box();
	Box(float _x, float _y, float _w, float _h);
	bool containsPoint(Point p);
	float& getX();
	float& getY();
	float& getWidth();
	float& getHeight();
};
Box::Box()
{
	this->x = 0;
	this->y = 0;
	this->width = 0;
	this->height = 0;
}
Box::Box(float _x, float _y, float _w, float _h)
{
	this->x = _x;
	this->y = _y;
	this->width = _w;
	this->height = _h;
}
bool Box::containsPoint(Point p)
{
	return (p.x >= this->x && p.x < (this->x + this->width)) && (p.y >= this->y && p.y < (this->y + this->height));
}

float& Box::getX()
{
	return this->x;
}
float& Box::getY()
{
	return this->y;
}
float& Box::getWidth()
{
	return this->width;
}
float& Box::getHeight()
{
	return this->height;
}
#endif // !RECTANGLE_H