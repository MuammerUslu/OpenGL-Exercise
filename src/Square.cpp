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

    // Karenin kenarlarını tanımla
    m_vertices[0] = -length * 0.5f;
    m_vertices[1] = length * 0.5f;
    m_vertices[2] = 0.0f;

    m_vertices[3] = -length * 0.5f;
    m_vertices[4] = -length * 0.5f;
    m_vertices[5] = 0.0f;

    m_vertices[6] = length * 0.5f;
    m_vertices[7] = -length * 0.5f;
    m_vertices[8] = 0.0f;

    m_vertices[9] = -length * 0.5f;
    m_vertices[10] = length * 0.5f;
    m_vertices[11] = 0.0f;

    m_vertices[12] = length * 0.5f;
    m_vertices[13] = -length * 0.5f;
    m_vertices[14] = 0.0f;

    m_vertices[15] = length * 0.5f;
    m_vertices[16] = length * 0.5f;
    m_vertices[17] = 0.0f;
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

const void *Square::getVertices() {
    return &m_vertices;
}

int Square::getSizeOfVertices() {
    return sizeof(m_vertices); //18 float her biri 4 byte => 72
}
