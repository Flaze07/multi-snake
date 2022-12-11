#ifndef APPLE_HPP_INCLUDED
#define APPLE_HPP_INCLUDED

#include <SFML/Graphics.hpp>

class Apple
{
private :
    sf::CircleShape shape;
    const int max_x;
    const int max_y;
    const int radius;
    sf::Color color;
public :
    Apple(unsigned int win_x, unsigned int win_y, unsigned int r);
    void reinit();
    void setColor(const sf::Color& color);
    sf::CircleShape& getShape();
};

#endif // APPLE_HPP_INCLUDED
