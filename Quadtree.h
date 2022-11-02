#ifndef QUADTREE_H
#define QUADTREE_H
#include "Node.h"
class Quadtree
{
private:
	Node* root;
public:
	Quadtree(float x, float y, float w, float h);
	void insert(Point p);
	void query();
	Node*& getRoot();
};
Quadtree::Quadtree(float x, float y, float w, float h)
{
	this->root = new Node(x, y, w, h);
}
void Quadtree::query()
{
	this->root->query_collision();
}
void Quadtree::insert(Point p)
{
	this->root->insert(p);
}
Node*& Quadtree::getRoot()
{
	return this->root;
}
#endif // !QUADTREE_H