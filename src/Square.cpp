//
// Created by Muammer Uslu on 24.03.2024.
//

#include "Square.hpp"
#include <cstdlib>

Square::Square(float x, float y, float length)
{
    m_Position = glm::vec3 (x,y,0.0);

    m_Color.r = ((10+std::rand()) % 25) * 0.04f;
    m_Color.g = ((10+std::rand()) % 25) * 0.04f;
    m_Color.b = ((10+std::rand()) % 25) * 0.04f;

    m_length = length;

    m_Direction = DIR_RIGHT;
}


void Square::setDirection(Square::DIRECTION direction)
{
    m_Direction = direction;
}


glm::vec3 Square::getPosition()
{
    return m_Position;
}

glm::vec4 Square::getColor()
{
    return m_Color;
}

void Square::move() {

    switch (m_Direction)
    {
        case DIR_RIGHT:
            m_Position+= glm::vec3(m_length,0.0f,0.0f);
            break;
        case DIR_LEFT:
            m_Position+= glm::vec3(-m_length,0.0f,0.0f);
            break;
        case DIR_UP:
            m_Position+= glm::vec3(0.0f,m_length,0.0f);
            break;
        case DIR_DOWN:
            m_Position+= glm::vec3(0.0f,-m_length,0.0f);
            break;
    }
}
