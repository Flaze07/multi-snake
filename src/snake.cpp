#include <iostream>
#include "snake.hpp"

void Snake::draw(sf::RenderTarget& target,sf::RenderStates states ) const
{
    target.draw(m_vertices, states);
}

Snake::Snake(unsigned int max_x, unsigned int max_y, int snake_size, int snake_length, sf::Color snake_color, sf::Color general_color, sf::Time speed) :
    starting_x(max_x),
    starting_y(max_y),
    size(snake_size),
    init_length(snake_length),
    head_color(snake_color),
    body_color(general_color),
    speed(speed),
    init_speed(speed),
    direction(Direction::up),
    condition(Condition::none)
{
    Snake::m_vertices.setPrimitiveType(sf::PrimitiveType::Quads);
    reinit();
}

void Snake::reinit()
{
    snake_length = init_length;
    m_vertices.clear();
    m_vertices.resize(init_length * 4);
    for (int i = 0; i < init_length ; ++i)
    {
        //the upper left
        m_vertices[(i * 4)].position = sf::Vector2f{static_cast<float>(starting_x), static_cast<float>((starting_y - (size * (init_length - i) ) ))};
        //the upper right
        m_vertices[(i * 4) + 1].position = sf::Vector2f{static_cast<float>(starting_x + size), static_cast<float>((starting_y - (size * (init_length - i) ) ))};
        //the lower right
        m_vertices[(i * 4) + 2].position = sf::Vector2f{static_cast<float>(starting_x + size), static_cast<float>((starting_y - (size * (init_length - i) ) ) + size)};
        //the lower left
        m_vertices[(i * 4) + 3].position = sf::Vector2f{static_cast<float>(starting_x), static_cast<float>((starting_y - (size * (init_length - i) ) ) + size)};
        if (i == 0)
        {
            m_vertices[0].color = head_color;
            m_vertices[1].color = head_color;
            m_vertices[2].color = head_color;
            m_vertices[3].color = head_color;
        }
        else
        {
            m_vertices[(i * 4)].color = body_color;
            m_vertices[(i * 4) + 1].color = body_color;
            m_vertices[(i * 4) + 2].color = body_color;
            m_vertices[(i * 4) + 3].color = body_color;
        }
    }
    condition = Condition::none;
    direction = Direction::up;
}

void Snake::update(sf::Time elapsedTime)
{
    speed -= elapsedTime;
    if (speed <= sf::milliseconds(0))
    {
        for (int i = snake_length - 1; i >= 1; --i)
        {
            if (i == 1)
            {
                m_vertices[(i * 4)].position = m_vertices[(i - 1) * 4].position;
                m_vertices[(i * 4) + 1].position = m_vertices[((i - 1) * 4) + 1].position;
                m_vertices[(i * 4) + 2].position = m_vertices[((i - 1) * 4) + 2].position;
                m_vertices[(i * 4) + 3].position = m_vertices[((i - 1) * 4) + 3].position;
                continue;
            }
            m_vertices[(i * 4)] = m_vertices[(i - 1) * 4];
            m_vertices[(i * 4) + 1] = m_vertices[((i - 1) * 4) + 1];
            m_vertices[(i * 4) + 2] = m_vertices[((i - 1) * 4) + 2];
            m_vertices[(i * 4) + 3] = m_vertices[((i - 1) * 4) + 3];
        }
        if (direction == Direction::up)
        {
            for (int i = 0; i < 4; ++i) m_vertices[i].position.y -= 10;
        }
        else if (direction == Direction::down)
        {
            for (int i = 0; i < 4; ++i) m_vertices[i].position.y += 10;
        }
        else if (direction == Direction::left)
        {
            for (int i = 0; i < 4; ++i) m_vertices[i].position.x -= 10;
        }
        else if (direction == Direction::right)
        {
            for (int i = 0; i < 4; ++i) m_vertices[i].position.x += 10;
        }
        speed = init_speed;
    }
}

void Snake::action(sf::Keyboard::Key up, sf::Keyboard::Key down, sf::Keyboard::Key left, sf::Keyboard::Key right)
{
    if ( (sf::Keyboard::isKeyPressed(up)) && (direction != Direction::down) )
    {
        direction = Direction::up;
    }
    else if ( (sf::Keyboard::isKeyPressed(down)) && (direction != Direction::up))
    {
        direction = Direction::down;
    }
    else if ( (sf::Keyboard::isKeyPressed(left)) && (direction != Direction::right))
    {
        direction = Direction::left;
    }
    else if ( (sf::Keyboard::isKeyPressed(right)) && (direction != Direction::left))
    {
        direction = Direction::right;
    }
}

void Snake::collision_self()
{
    sf::Vector2f head = {m_vertices[0].position};
    for (unsigned int i = 0; i < snake_length; ++i)
    {
        sf::Vector2f current = {m_vertices[i * 4].position};
        if (head == current)
        {
            m_vertices.resize(i * 4);
        }
    }
}

void Snake::collision_apple(Apple& apple)
{
    sf::Vector2f apple_pos = apple.getShape().getPosition();
    sf::Vector2f snake_pos = m_vertices[0].position;
    if (apple_pos == snake_pos)
    {
        ++snake_length;
        apple.reinit();
        for (int i = 0; i < 4; ++i)
        {
            m_vertices.append(sf::Vertex{});
        }
    }
}

void Snake::wall_collision()
{
    sf::Vector2f snake_pos = m_vertices[0].position;
    if (snake_pos.x == -10)
    {
        m_vertices[0].position = sf::Vector2f{600-size, m_vertices[0].position.y};
        m_vertices[1].position = sf::Vector2f{600, m_vertices[1].position.y};
        m_vertices[2].position = sf::Vector2f{600, m_vertices[2].position.y};
        m_vertices[3].position = sf::Vector2f{600-size, m_vertices[3].position.y};
    }
    else if (snake_pos.x == 600)
    {
        m_vertices[0].position = sf::Vector2f{0, m_vertices[0].position.y};
        m_vertices[1].position = sf::Vector2f{0+size, m_vertices[1].position.y};
        m_vertices[2].position = sf::Vector2f{0+size, m_vertices[2].position.y};
        m_vertices[3].position = sf::Vector2f{0, m_vertices[3].position.y};
    }
    if (snake_pos.y == -10)
    {
        m_vertices[0].position = sf::Vector2f{m_vertices[0].position.x, 400-size};
        m_vertices[1].position = sf::Vector2f{m_vertices[1].position.x, 400-size};
        m_vertices[2].position = sf::Vector2f{m_vertices[2].position.x, 400};
        m_vertices[3].position = sf::Vector2f{m_vertices[3].position.x, 400};
    }
    else if (snake_pos.y == 400)
    {
        m_vertices[0].position = sf::Vector2f{m_vertices[0].position.x, 0};
        m_vertices[1].position = sf::Vector2f{m_vertices[1].position.x, 0};
        m_vertices[2].position = sf::Vector2f{m_vertices[2].position.x, 0+size};
        m_vertices[3].position = sf::Vector2f{m_vertices[3].position.x, 0+size};
    }
}

void Snake::collision_other(Snake &snake)
{
    if (m_vertices[0].position == snake.getVertex()[0].position)
    {
        setCondition(Condition::draw);
        snake.setCondition(Condition::draw);
        return;
    }
    for (int i = 1; i < snake.getLength(); ++i)
    {
        if (m_vertices[0].position == snake.getVertex()[i * 4].position)
        {
            setCondition(Condition::lose);
            snake.setCondition(Condition::win);
        }
    }
}

void Snake::collision_obs(Obstacle& obstacle)
{
    for (int i = 0; i < (obstacle.getVertexCount() / 4); ++i)
    {
        if (this->m_vertices[(i * 4)].position == obstacle.getVertices()[(i * 4)].position)
        {
            this->setCondition(Condition::lose);
        }
    }
}

void Snake::collision(Apple& apple, Snake &snake, Obstacle& obstacle, bool isMulti)
{
    collision_apple(apple);
    wall_collision();
    collision_obs(obstacle);
    if (isMulti) collision_other(snake);
}

void Snake::setCondition(Condition condition)
{
    this->condition = condition;
}


sf::VertexArray& Snake::getVertex()
{
    return m_vertices;
}

uint32_t& Snake::getLength()
{
    return snake_length;
}

std::string Snake::getCondition()
{
    if(condition == Condition::none) return std::string{"none"};
    else if (condition == Condition::win) return std::string{"win"};
    else if (condition == Condition::lose) return std::string{"lose"};
    else if (condition == Condition::draw) return std::string{"draw"};
}
