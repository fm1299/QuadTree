#ifndef POINT_H
#define POINT_H
#include <math.h>
#include <iostream>
class Point
{
private:
	float x;
	float y;
	float radius;
	bool highlighted;
	friend class Quadtree;
	friend class Box;
	friend class Node;
public:
	Point();
	Point(float axisX, float axixY);
	float& getX();
	float& getY();
	float& getR();
	bool getHighlighted();
	float distance(Point p);
	bool intersected(Point p);
};
Point::Point()
{
	this->x = 0;
	this->y = 0;
	this->radius = 4;
	this->highlighted = false;
}
Point::Point(float axisX, float axisY)
{
	this->x = axisX;
	this->y = axisY;
	this->radius = 4;
	this->highlighted = false;
}
float& Point::getX()
{
	return this->x;
}
float& Point::getY()
{
	return this->y;
}
float& Point::getR()
{
	return this->radius;
}
bool Point::getHighlighted()
{
	return this->highlighted;
}
float Point::distance(Point p)
{
	float d = 0.0f;
	float x1 = this->x;
	float y1 = this->y;
	float x2 = p.x;
	float y2 = p.y;
	d = ((pow((x2 - x1), 2)) + (pow((y2 - y1), 2)));
	return d;
}
bool Point::intersected(Point p)
{
	float distance = sqrt(this->distance(p));
	float diameter = (this->radius) * 2;
	return distance <= diameter;
}
#endif // !POINT_H