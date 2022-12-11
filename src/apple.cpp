#include <cstdio>
#include <ctime>
#include "apple.hpp"

Apple::Apple(unsigned int win_x, unsigned int win_y, unsigned int r) :
    max_x(win_x),
    max_y(win_y),
    radius(r)
{
    shape.setRadius(r);
    shape.setFillColor(color);
    reinit();
}

void Apple::reinit()
{
    srand(time(0));
    int x = ( rand()% ( (max_x / (radius * 2)) - 1) ) * radius * 2;
    int y = ( rand()% ( (max_y / (radius * 2)) - 1) ) * radius * 2;
    shape.setPosition(x, y);
}

void Apple::setColor(const sf::Color& color)
{
    this->color = color;
    shape.setFillColor(color);
}

sf::CircleShape& Apple::getShape()
{
    return shape;
}
