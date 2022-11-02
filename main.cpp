#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include "Quadtree.h"
#define WIDTH 800
#define HEIGHT 800
Quadtree* tree;
void renderPoints(sf::RenderTarget* window,float centerX,float centerY,float radius, bool mark)
{
    /*float diameter = (radius * 2);
    float x = (radius - 1);
    float y = 0;
    float tx = 1;
    float ty = 1;
    float error = (tx - diameter);*/
    /*while (x >= y)
    {*/
        /*if (mark)
        {
            sf::CircleShape point1(radius);
            point1.setPosition(centerX, centerY);
            point1.setOutlineThickness(5.0f);
            point1.setOutlineColor(sf::Color::White);
            point1.setFillColor(sf::Color::Transparent);
            window->draw(point1);
        }*/
        /*else
        {*/
            sf::CircleShape point1(radius);
            point1.setPosition(centerX, centerY);
            point1.setOutlineThickness(5.0f);
            point1.setOutlineColor(sf::Color::Red);
            point1.setFillColor(sf::Color::Transparent);
            window->draw(point1);
        // }
        /*if (error <= 0)
        {
            ++y;
            error += ty;
            ty += 2;
        }
        if (error > 0)
        {
            --x;
            tx += 2;
            error += (tx - diameter);
        }*/
    //}
}
void renderNode(Node* root, sf::RenderTarget* window)
{
    sf::RectangleShape rect({ root->getBounds()->getWidth(),root->getBounds()->getHeight() });
    rect.setPosition(root->getBounds()->getX(), root->getBounds()->getY());
    rect.setFillColor(sf::Color::Black);
    rect.setOutlineThickness(5.0f);
    rect.setOutlineColor(sf::Color::Blue);
    window->draw(rect);
    if (!root->isLeaf())
    {
        renderNode(root->getNW(),window);
        renderNode(root->getNE(), window);
        renderNode(root->getSW(), window);
        renderNode(root->getSE(), window);
    }
    else
    {
        for (int i = 0; i < root->getCapacity(); i++)
        {
            if (root->data[i].getHighlighted())
            {
                renderPoints(window, root->data[i].getX(), root->data[i].getY(), root->data[i].getR(), true);
            }
            else
            {
                renderPoints(window, root->data[i].getX(), root->data[i].getY(), root->data[i].getR(), false);
            }
        }
    }
}
void eventHandler(sf::RenderWindow &window)
{
    sf::Event event;
    while (window.pollEvent(event));
    {
        switch (event.type)
        {
        case sf::Event::Closed:
            window.close();
            break;
        case sf::Event::MouseButtonPressed:
            tree->getRoot()->insert(Point(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y));
            break;
        }
    }
}
int main()
{
    tree = new Quadtree(0, 0, WIDTH, HEIGHT);
    sf::RenderWindow window;
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    window.create(sf::VideoMode(WIDTH, HEIGHT, desktop.bitsPerPixel), "Quadtree");
    while (window.isOpen())
    {
        tree->query();
        eventHandler(window);
        window.clear(sf::Color::Black);
        renderNode(tree->getRoot(), &window);
        window.display();
    }
	return 0;
}