#ifndef OBSTACLE_H_INCLUDED
#define OBSTACLE_H_INCLUDED

#include <SFML/Graphics.hpp>

class Obstacle : public sf::Drawable, sf::Transformable
{
private :
    void draw(sf::RenderTarget& target,sf::RenderStates states ) const
    {
        target.draw(m_vertices, states);
    }
    sf::VertexArray m_vertices;
    int size;
public :
    Obstacle(int n_obs, int size, int win_x, int win_y);
    void reinit(int win_x, int win_y);
    int& getVertexSize();
    sf::VertexArray& getVertices();
};

#endif // OBSTACLE_H_INCLUDED
