#ifndef NODE_H
#define NODE_H
#include <vector>
#include "Box.h"
#include "Point.h"
class Node
{
private:
	friend class Quadtree;
	int capacity;
	Node *NW;
	Node *NE;
	Node *SW;
	Node *SE;
	int count;
	Box *bounds;
	void split();
public:
	Node(float _x, float _y, float _w, float _h)
	{
		this->capacity = 1;
		this->count = 0;
		this->bounds = new Box(_x, _y, _w, _h);
		this->NW = nullptr;
		this->NE = nullptr;
		this->SW = nullptr;
		this->SE = nullptr;
		this->data = new Point[capacity];
	}
	int getCapacity();
	Node*& getNW();
	Node*& getNE();
	Node*& getSW();
	Node*& getSE();
	bool insert(Point p);
	bool isLeaf();
	void query_collision();
	Box*& getBounds();
	Point* data;
};

int Node::getCapacity()
{
	return this->capacity;
}
Node*& Node::getNW()
{
	return this->NW;
}
Node*& Node::getNE()
{
	return this->NE;
}
Node*& Node::getSW()
{
	return this->SW;
}
Node*& Node::getSE()
{
	return this->SE;
}
Box*& Node::getBounds()
{
	return this->bounds;
}
bool Node::isLeaf()
{
	return this->NW == nullptr;
}

bool Node::insert(Point p)
{
	if (!this->bounds->containsPoint(p))
	{
		return false;
	}
	if (this->isLeaf())
	{
		if (count < this->capacity)
		{
			this->data[count] = p;
			std::cout << "Adding point: " << this->data[count].x << "," << this->data[count].y << std::endl;
			this->count++;
			return true;
		}
		this->split();
	}
	if (this->NW->insert(p))
	{
		std::cout << "Inserted NW" << std::endl;
		return true;
	}
	if (this->NE->insert(p))
	{
		std::cout << "Inserted NE" << std::endl;
		return true;
	}
	if (this->SW->insert(p))
	{
		std::cout << "Inserted SW" << std::endl;
		return true;
	}
	if (this->SE->insert(p))
	{
		std::cout << "Inserted SE" << std::endl;
		return true;
	}

	std::cout << "Duplicated point" << std::endl;
	return false;
}

void Node::split()
{
	float x = this->bounds->x;
	float y = this->bounds->y;
	float w = this->bounds->width;
	float h = this->bounds->height;

	this->NW = new Node(x, y, w / 2.0f, h / 2.0f);
	this->NE = new Node(x + w / 2.0f, y, w / 2.0f, h / 2.0f);
	this->SW = new Node(x, y + h / 2.0f, w / 2.0f, h / 2.0f);
	this->SE = new Node(x + w / 2.0f, y + h / 2.0f, w / 2.0f, h / 2.0f);

	for (int i = 0; i < count; i++)
	{
		if (this->NW->insert(this->data[i]))
		{
			std::cout << "Trying NW" << std::endl;
			continue;
		}
		if (this->NE->insert(this->data[i]))
		{
			std::cout << "Trying NE" << std::endl;
			continue;
		}
		if (this->SW->insert(this->data[i]))
		{
			std::cout << "Trying SW" << std::endl;
			continue;
		}
		if (this->SE->insert(this->data[i]))
		{
			std::cout << "Trying SE" << std::endl;
			continue;
		}
		std::cerr << "Failed to place existing point after subdivide procedure" << std::endl;
	}
}

void Node::query_collision()
{
	if (!this->isLeaf())
	{
		this->NW->query_collision();
		this->NE->query_collision();
		this->SW->query_collision();
		this->SE->query_collision();
	}
	else
	{
		for (int i = 0; i < count; i++)
		{
			for (int j = 0; j < count; j++)
			{
				if (this->data[i].intersected(this->data[j]) && this->data[j].x != this->data[i].x && this->data[j].y != this->data[i].y)
				{
					std::cout << "El punto: (" << this->data[i].x << "," << this->data[i].y << ") con radio:" << this->data[i].radius << "colisiona" << std::endl;
					std::cout << "con el punto: (" << this->data[j].x << "," << this->data[j].y << ") con radio:" << this->data[j].radius << "colisiona" << std::endl;
					this->data[j].highlighted = true;
				}
			}
		}
	}
}
#endif // !NODE_H