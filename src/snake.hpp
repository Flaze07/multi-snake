#ifndef SNAKE_HPP_INCLUDED
#define SNAKE_HPP_INCLUDED

#include <string>
#include <SFML/Graphics.hpp>
#include "apple.hpp"
#include "obstacle.hpp"

class Snake : public sf::Drawable
{
private :
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    enum class Direction {up, down, left, right};
    enum class Condition {win, lose, draw, none};
    sf::Time delay;
    int starting_x;
    int starting_y;
    int size;
    int init_length;
    sf::Color head_color;
    sf::Color body_color;
    sf::VertexArray m_vertices;
    uint32_t snake_length;
    sf::Time speed;
    sf::Time init_speed;
    Direction direction;
    Condition condition;
public :
    Snake(unsigned int win_x, unsigned int win_y, int snake_size, int snake_length, sf::Color snake_color, sf::Color general_color, sf::Time speed);
    void reinit();
    void update(sf::Time ElapsedTime);
    void action(sf::Keyboard::Key up, sf::Keyboard::Key down, sf::Keyboard::Key left, sf::Keyboard::Key right);
    void collision_self();
    void collision_apple(Apple& apple);
    void wall_collision();
    void collision_other(Snake &snake);
    void collision_obs(Obstacle& obstacle);
    void collision(Apple& apple, Snake &snake, Obstacle& obstacle, bool isMulti);
    void reset();
    //setting var
    void setCondition(Condition condition);
    //getting var
    sf::VertexArray& getVertex();
    uint32_t& getLength();
    std::string getCondition();
};

#endif // SNAKE_HPP_INCLUDED
