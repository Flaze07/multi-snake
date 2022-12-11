#include <cstdlib>
#include <ctime>
#include "obstacle.hpp"

Obstacle::Obstacle(int n_obs, int size, int win_x, int win_y) :
    size(size)
{
    this->m_vertices.setPrimitiveType(sf::PrimitiveType::Quads);
    this->m_vertices.resize(n_obs * 4);
    this->reinit(win_x, win_y);
}

void Obstacle::reinit(int win_x, int win_y)
{
    srand(time(0));
    for (int i = 0; i < (this->m_vertices.getVertexCount() / 4 ); ++i)
    {
        int x = size * (rand()% ((win_x - this->size) / size));
        rand();
        int y = size * (rand()% ((win_y - this->size) / size));
        this->m_vertices[(i * 4)].position = sf::Vector2f{x, y};
        this->m_vertices[(i * 4) + 1].position = sf::Vector2f{x + size, y};
        this->m_vertices[(i * 4) + 2].position = sf::Vector2f{x + size, y + size};
        this->m_vertices[(i * 4) + 3].position = sf::Vector2f{x, y + size};
    }
}

void Obstacle::setNumber(uint32_t nObs)
{
    this->m_vertices.resize(nObs * 4);
}

size_t Obstacle::getVertexCount()
{
    return m_vertices.getVertexCount();
}

sf::VertexArray& Obstacle::getVertices()
{
    return m_vertices;
}
